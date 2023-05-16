// Fill out your copyright notice in the Description page of Project Settings.


#include "UWItemGallery.h"
#include "UWUserName.h"
#include "UWUserCash.h"
#include "UWItemTypeSelector.h"
#include "UWItemCount.h"
#include "UWItemList.h"
#include "UWButton.h"
#include <UserData.h>
#include <ItemMapData.h>

void UUWItemGallery::NativeOnHeroGalleryWidgetSetup()
{
	Super::NativeOnHeroGalleryWidgetSetup();
	Update();
}

void UUWItemGallery::NativePreConstruct()
{
	Super::NativePreConstruct();
	Update();
}

void UUWItemGallery::NativeConstruct()
{
	Super::NativeConstruct();

	WBITS_ItemTypeSelector->OnClicked.AddDynamic(this, &UUWItemGallery::OnSelectorButtonClicked);
	WBIL_ItemList->OnItemSlotSelected.AddDynamic(this, &UUWItemGallery::OnItemSlotSelected);
	WBB_Equip->OnClicked.AddDynamic(this, &UUWItemGallery::OnEquipClicked);
	WBB_Unlock->OnClicked.AddDynamic(this, &UUWItemGallery::OnUnlockClicked);
}

void UUWItemGallery::OnSelectorButtonClicked(int Direction)
{
	int32 n = StaticEnum<EItemType>()->NumEnums() - 1;
	int32 e = (int32)ItemType + Direction;
	int32 sign = e >= 0 ? +1 : -1;
	e = (FMath::Abs(e) % n) * sign;
	if (e < 0)
		e = n + e;

	ItemType = (EItemType)e;
	Update();
}

void UUWItemGallery::OnItemSlotSelected()
{
	UpdateClickable();
}

void UUWItemGallery::OnEquipClicked()
{
	if (!WBIL_ItemList->HasValidSelectedItemData())
		return;
	if (!UserData)
		return;

	FItemData ItemData = WBIL_ItemList->GetSelectedItemData();
	if (!UserData->OwnedItems.Contains(SubData.HeroType, ItemData))
		return;

	UserData->EquippedItems.Add(FItemKey(SubData.HeroType, ItemData.ItemType), ItemData);
	Update();
}

void UUWItemGallery::OnUnlockClicked()
{
	if (!WBIL_ItemList->HasValidSelectedItemData())
		return;
	if (!UserData)
		return;
	if (!SubData.ItemMapDataTable)
		return;

	FItemData ItemData = WBIL_ItemList->GetSelectedItemData();
	if (ItemData.Cost > UserData->Cash)
		return;
	if (UserData->OwnedItems.Contains(SubData.HeroType, ItemData))
		return;

	UserData->Cash -= ItemData.Cost;
	UserData->OwnedItems.Add(SubData.HeroType, ItemData);
	Update();
}

FString UUWItemGallery::GetCurrentItemTypeName() const
{
	return StaticEnum<EItemType>()->GetNameStringByValue((int64)ItemType);
}

void UUWItemGallery::Update()
{
	WBIL_ItemList->ResetEquippedItem();

	WBIC_ItemCount->SetTitle(SubData.HeroName + TEXT(" : ") + GetCurrentItemTypeName());

	if (UserData != nullptr)
	{
		WBUN_UserName->UserName = FText::FromName(UserData->HeroName);

		WBUC_UserCash->SetCash(UserData->Cash);

		int32 ItemCount = UserData->OwnedItems.Num(SubData.HeroType, ItemType);
		WBIC_ItemCount->SetItemCount(ItemCount);

		TArray<FItemData>* ItemDataArray = UserData->OwnedItems.FindItems(SubData.HeroType, ItemType);
		TArray<FItemData> OwnedItems;
		if (ItemDataArray != nullptr)
		{
			for (FItemData& ItemData : *ItemDataArray)
				OwnedItems.Add(ItemData);
		}
		WBIL_ItemList->MoveOwnedItems(std::move(OwnedItems));

		FItemData* pEquippedItem = UserData->EquippedItems.Find(FItemKey(SubData.HeroType, ItemType));
		WBIL_ItemList->SetEquippedItem(pEquippedItem ? *pEquippedItem : FItemData());
	}

	if (SubData.ItemMapDataTable != nullptr)
	{
		UDataTable* ItemDataTable = FItemMapData::FindItemDataTable(SubData.ItemMapDataTable, SubData.HeroType, ItemType);

		if (ItemDataTable != nullptr)
		{
			TArray<FItemData*> ItemDataPointers;
			ItemDataTable->GetAllRows(TEXT("GetAllRows"), ItemDataPointers);

			TArray<FItemData> ItemDatas;
			for (FItemData* ItemDataPointer : ItemDataPointers)
				ItemDatas.Push(*ItemDataPointer);

			WBIC_ItemCount->SetMaxItemCount(ItemDatas.Num());

			WBIL_ItemList->MoveItemList(std::move(ItemDatas));
		}
	}

	WBITS_ItemTypeSelector->SetTitle(GetCurrentItemTypeName());

	UpdateClickable();
}

void UUWItemGallery::UpdateClickable()
{
	WBB_Equip->SetButtonEnable(false);
	WBB_Unlock->SetButtonEnable(false);

	if (UserData && WBIL_ItemList->HasValidSelectedItemData())
	{
		FItemData Selected = WBIL_ItemList->GetSelectedItemData();
		FItemData* Equipped = UserData->EquippedItems.Find(FItemKey(SubData.HeroType, ItemType));
		bool HasThisItem = UserData->OwnedItems.Contains(SubData.HeroType, Selected);

		if (!HasThisItem)
		{
			WBB_Unlock->SetButtonEnable(true);
		}
		else if (!Equipped || (*Equipped) != Selected)
		{
			WBB_Equip->SetButtonEnable(true);
		}
	}
}

