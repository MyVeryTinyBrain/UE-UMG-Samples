// Fill out your copyright notice in the Description page of Project Settings.


#include "UWItemLoot.h"
#include "UWInventoryButton.h"
#include "UWItemStorage.h"
#include "UWItemGrid.h"
#include "UWDraggableItemZone.h"
#include <UserData.h>

void UUWItemLoot::NativeConstruct()
{
	Super::NativeConstruct();

	WBDZ_DraggableItemZone->OnStartDrag.AddDynamic(this, &UUWItemLoot::OnStartDrag);
	WBDZ_DraggableItemZone->OnEndDrag.AddDynamic(this, &UUWItemLoot::OnEndDrag);

	WBIS_UserItemStorage->OnChanged.AddDynamic(this, &UUWItemLoot::Internal_OnChanged);
	WBIS_LootItemStorage->OnChanged.AddDynamic(this, &UUWItemLoot::Internal_OnChanged);

	WBRB_UserItemSortButton->OnInventoryButtonClicked.AddDynamic(this, &UUWItemLoot::OnUserItemSortButtonClicked);
	WBRB_LootItemSortButton->OnInventoryButtonClicked.AddDynamic(this, &UUWItemLoot::OnLootSortButtonClicked);
	WBRB_LootItemRefreshButton->OnInventoryButtonClicked.AddDynamic(this, &UUWItemLoot::OnLootRefreshButtonClicked);

	SetupLootItems();
}

void UUWItemLoot::NativeOnUserDataWidgetSetup()
{
	Super::NativeOnUserDataWidgetSetup();

	WBIS_UserItemStorage->GetItemGrid()->LoadFromUserData(UserData, false);
}

void UUWItemLoot::OnUserItemSortButtonClicked()
{
	WBIS_UserItemStorage->GetItemGrid()->Sort();
}

void UUWItemLoot::OnLootSortButtonClicked()
{
	WBIS_LootItemStorage->GetItemGrid()->Sort();
}

void UUWItemLoot::OnLootRefreshButtonClicked()
{
	SetupLootItems();
}

void UUWItemLoot::OnStartDrag()
{
	WBRB_UserItemSortButton->SetButtonEnable(false);
	WBRB_LootItemSortButton->SetButtonEnable(false);
	WBRB_LootItemRefreshButton->SetButtonEnable(false);
}

void UUWItemLoot::OnEndDrag()
{
	WBRB_UserItemSortButton->SetButtonEnable(true);
	WBRB_LootItemSortButton->SetButtonEnable(true);
	WBRB_LootItemRefreshButton->SetButtonEnable(true);
}

void UUWItemLoot::Internal_OnChanged(UUWItemStorage* InItemStorage)
{
	if (InItemStorage == WBIS_UserItemStorage)
	{
		// StoreToUserData
		if (UserData)
		{
			WBIS_UserItemStorage->GetItemGrid()->StoreToUserData(UserData);
		}
	}
}

void UUWItemLoot::SetupLootItems()
{
	if (DraggableItemDataTable)
	{
		TArray<FDraggableItemData*> Pointers;
		DraggableItemDataTable->GetAllRows(TEXT("GetAllRows"), Pointers);

		int32 Sx = WBIS_UserItemStorage->GetCountX();
		int32 Sy = WBIS_UserItemStorage->GetCountY();
		int32 NumMaxItems = FMath::Clamp((Sx * Sy) / 2, 1, INT32_MAX);
		if (Sx == 1)
		{
			NumMaxItems = FMath::Clamp(Sy / 2, 1, INT32_MAX);
		}
		else if (Sy == 1)
		{
			NumMaxItems = FMath::Clamp(Sx / 2, 1, INT32_MAX);
		}

		int32 NumItems = FMath::RandRange(1, NumMaxItems);
		TArray<FDraggableItemData> Items;
		for (int32 i = 0; i < NumItems; ++i)
		{
			int32 ItemIdx = FMath::RandRange(0, Pointers.Num() - 1);
			Items.Add(*Pointers[ItemIdx]);
		}

		UDraggableItemContainer* Container = UDraggableItemContainer::CreateProperContainer(Items, FGridPair(Sx, Sy));
		WBIS_LootItemStorage->GetItemGrid()->LoadFromContainer(Container);
	}
}
