// Fill out your copyright notice in the Description page of Project Settings.


#include "UWItemList.h"
#include <Components/ScrollBox.h>
#include "UWItemSlot.h"
#include <Blueprint/WidgetTree.h>

void UUWItemList::NativeConstruct()
{
	Super::NativeConstruct();
}

void UUWItemList::NativePreConstruct()
{
	Super::NativePreConstruct();

	UpdateItemList();
	UpdateEquippedState();
	UpdateSelectedState();
}

void UUWItemList::OnItemSlotClicked(UUWItemSlot* ItemSlot)
{
	if (HasValidSelectedItemData())
	{
		if (UUWItemSlot* PrevSlot = Cast<UUWItemSlot>(SB_ItemList->GetChildAt(Select)))
			PrevSlot->SetSelectState(false);
	}

	Select = SB_ItemList->GetChildIndex(ItemSlot);
	ItemSlot->SetSelectState(true);

	OnItemSlotSelected.Broadcast();
}

UUWItemSlot* UUWItemList::GetItemSlotByIndex(int32 Index) const
{
	if (Index < 0 || Index >= SB_ItemList->GetChildrenCount())
		return nullptr;
	UWidget* widget = SB_ItemList->GetChildAt(Index);
	return Cast<UUWItemSlot>(widget);
}

void UUWItemList::AddItemSlot(const FItemData& ItemData, bool IsNewItem, bool IsLocked)
{
	int32 currentIndex = SB_ItemList->GetChildrenCount();
	UUWItemSlot* element = CreateWidget<UUWItemSlot>(SB_ItemList, ElementTemplate);

	if (!element)
	{
		FString Position = (FString(__FUNCTION__) + FString(TEXT(": ")) + FString::FromInt(__LINE__));
		UE_LOG(LogTemp, Error, TEXT("Type missmatch %s"), *Position);
		return;
	}

	element->OnClicked.AddDynamic(this, &UUWItemList::OnItemSlotClicked);

	// Create CanvasPanelSlot of ItemSlot
	SB_ItemList->AddChild(element);

	// Init Item Slot After Created CanvasPanelSlot
	element->SetItemData(ItemData);
	element->SetIsNewItem(IsNewItem);
	element->SetIsLocked(IsLocked);
	element->SetSelectState(currentIndex == Select);
	element->SetEquipState(ItemData == EquippedItem);
}

void UUWItemList::UpdateItemList()
{
	SB_ItemList->ClearChildren();
	for (const FItemData& listData : ItemList)
	{
		bool IsNewItem = true;
		bool IsLocked = OwnedItems.Find(listData) == INDEX_NONE;
		AddItemSlot(listData, IsNewItem, IsLocked);
	}
}

void UUWItemList::UpdateEquippedState()
{
	TArray<UWidget*> Children = SB_ItemList->GetAllChildren();
	for (int32 i = 0; i < Children.Num(); ++i)
	{
		if (UUWItemSlot* ItemSlot = Cast<UUWItemSlot>(Children[i]))
		{
			ItemSlot->SetEquipState(EquippedItem == ItemSlot->GetItemData());
		}
	}
}

void UUWItemList::UpdateSelectedState()
{
	TArray<UWidget*> Children = SB_ItemList->GetAllChildren();
	for (int32 i = 0; i < Children.Num(); ++i)
	{
		if (UUWItemSlot* ItemSlot = Cast<UUWItemSlot>(Children[i]))
		{
			ItemSlot->SetSelectState(i == Select);
		}
	}
}

void UUWItemList::ResetEquippedItem()
{
	EquippedItem = FItemData();
}

bool UUWItemList::HasValidSelectedItemData() const
{
	return Select >= 0 && Select < SB_ItemList->GetChildrenCount();
}

FItemData UUWItemList::GetSelectedItemData() const
{
	if (!HasValidSelectedItemData())
		return FItemData::Invalid();
	if (UUWItemSlot* SelectedSlot = Cast<UUWItemSlot>(SB_ItemList->GetChildAt(Select)))
		return SelectedSlot->GetItemData();
	return FItemData::Invalid();
}

void UUWItemList::SetItemList(const TArray<FItemData>& InItemList)
{
	ItemList = InItemList;
	UpdateItemList();
}

void UUWItemList::MoveItemList(TArray<FItemData>&& InItemList)
{
	ItemList = std::move(InItemList);
	UpdateItemList();
}

void UUWItemList::SetOwnedItems(const TArray<FItemData>& InOwnedItems)
{
	OwnedItems = InOwnedItems;
	UpdateItemList();
}

void UUWItemList::MoveOwnedItems(TArray<FItemData>&& InOwnedItems)
{
	OwnedItems = std::move(InOwnedItems);
	UpdateItemList();
}

void UUWItemList::SetEquippedItem(const FItemData& InEquippedItem)
{
	EquippedItem = InEquippedItem;
	UpdateEquippedState();
}

void UUWItemList::SetSelect(int32 InSelect)
{
	Select = InSelect;
	UpdateSelectedState();
}
