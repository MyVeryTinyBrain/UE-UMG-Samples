// Fill out your copyright notice in the Description page of Project Settings.


#include "UWItemGrid.h"
#include <Components/CanvasPanelSlot.h>
#include <Components/CanvasPanel.h>
#include <Blueprint/WidgetLayoutLibrary.h>
#include <Blueprint/SlateBlueprintLibrary.h>
#include "UWDraggableItem.h"
#include "UWItemGridCell.h"
#include "UserInterfaceLibrary.h"
#include <UserData.h>

void UUWItemGrid::NativePreConstruct()
{
	Super::NativePreConstruct();
}

void UUWItemGrid::Internal_OnChanged()
{
	OnChanged.Broadcast(this);
}

void UUWItemGrid::Internal_OnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
	GenerateMouseButtonDownEvent();
}

FReply UUWItemGrid::NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
	FReply Result = Super::NativeOnMouseButtonDown(InGeometry, InMouseEvent);
	Internal_OnMouseButtonDown(InGeometry, InMouseEvent);
	return Result;
}

FReply UUWItemGrid::NativeOnMouseButtonDoubleClick(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
	FReply Result = Super::NativeOnMouseButtonDoubleClick(InGeometry, InMouseEvent);
	Internal_OnMouseButtonDown(InGeometry, InMouseEvent);
	return Result;
}

void UUWItemGrid::OnPressedDraggableItem(UUWDraggableItem* InItem)
{
	GenerateMouseButtonDownEvent();
}

void UUWItemGrid::NativeConstruct()
{
	Super::NativeConstruct();
}

void UUWItemGrid::ReplaceElements()
{
	if (!CellTemplate)
		return;

	UCanvasPanelSlot* SlotAreaCanvasPanelSlot = Cast<UCanvasPanelSlot>(Canv_SlotArea->Slot);
	if (!SlotAreaCanvasPanelSlot)
		return;

	SlotAreaCanvasPanelSlot->SetAnchors(FAnchors(0, 0, 1, 1));
	SlotAreaCanvasPanelSlot->SetOffsets(FMargin(0, 0, 0, 0));

	for (UUserWidget* Cell : Cells)
		Canv_SlotArea->RemoveChild(Cell);
	Cells.Empty();

	if (CountX == 0 || CountY == 0)
		return;

	FVector2D CellSize = GetCellSize();
	for (int32 i = 0; i < CountY; ++i)
	{
		for (int32 j = 0; j < CountX; ++j)
		{
			UUWItemGridCell* Cell = CreateWidget<UUWItemGridCell>(Canv_SlotArea, CellTemplate);
			Canv_SlotArea->AddChild(Cell);
			Cells.Add(Cell);

			Cell->SetItemGridCellMode(EItemGridCellMode::Deactive);

			UCanvasPanelSlot* CellCanvasPanelSlot = Cast<UCanvasPanelSlot>(Cell->Slot);
			CellCanvasPanelSlot->SetSize(CellSize);
			FVector2D ElementPosition = IndexToLocalPosition(FGridPair(j, i));
			CellCanvasPanelSlot->SetPosition(ElementPosition);
		}
	}
}

void UUWItemGrid::Internal_SetItem(const FGridPair& InIndex, UUWDraggableItem* InItem, bool bGenerateChangedNotify)
{
	FVector2D LocalPosition = IndexToLocalPosition(InIndex);
	FVector2D CellSize = GetCellSize();
	FIntVector2 ItemCount = FIntVector2(InItem->GetItemData().SizeX, InItem->GetItemData().SizeY);
	FVector2D ItemSize = FVector2D(CellSize.X * ItemCount.X, CellSize.Y * ItemCount.Y);

	Canv_SlotArea->AddChild(InItem);
	if (UCanvasPanelSlot* CanvasPanelSlot = Cast<UCanvasPanelSlot>(InItem->Slot))
	{
		CanvasPanelSlot->SetPosition(LocalPosition);
		CanvasPanelSlot->SetSize(ItemSize);
	}

	Items.Add(InIndex, InItem);

	for (int32 Y = InIndex.Y; Y < InIndex.Y + ItemCount.Y; ++Y)
	{
		for (int32 X = InIndex.X; X < InIndex.X + ItemCount.X; ++X)
		{
			UsingCells.Add(FGridPair(X, Y), InItem);
		}
	}

	InItem->OnPressed.AddDynamic(this, &UUWItemGrid::OnPressedDraggableItem);

	if (bGenerateChangedNotify)
	{
		Internal_OnChanged();
	}
}

void UUWItemGrid::GenerateMouseButtonDownEvent()
{
	FVector2D MouseInAbsolute = UUserInterfaceLibrary::GetMousePositionOnAbsolute(GetWorld());
	FGridPair Index = AbsolutePositionToIndex(MouseInAbsolute);
	OnClickedSlot.Broadcast(this, Index);
}

void UUWItemGrid::SetCount(int32 InCountX, int32 InCountY)
{
	CountX = InCountX;
	CountY = InCountY;

	ReplaceElements();
}

void UUWItemGrid::SetCountX(int32 InCountX)
{
	SetCount(InCountX, CountY);
}

void UUWItemGrid::SetCountY(int32 InCountY)
{
	SetCount(CountX, InCountY);
}

FGridPair UUWItemGrid::LocalPositionToIndex(const FVector2D& InLocalPosition) const
{
	FVector2D FloatIndex = InLocalPosition / SlotAreaCanvasSize;
	FGridPair Index = FGridPair(FMath::Floor(FloatIndex.X * CountX), FMath::Floor(FloatIndex.Y * CountY));
	return Index;
}

FGridPair UUWItemGrid::AbsolutePositionToIndex(const FVector2D& InAbsolutePosition) const
{
	FVector2D InAbsolute = InAbsolutePosition;
	FVector2D InLocal = UUserInterfaceLibrary::AbsoluteToLocal(Canv_SlotArea, InAbsolute);
	return LocalPositionToIndex(InLocal);
}

FVector2D UUWItemGrid::IndexToLocalPosition(const FGridPair& InIndex) const
{
	FVector2D Index = FVector2D(InIndex.X, InIndex.Y);
	FVector2D PanelSize = SlotAreaCanvasSize - FVector2D(Padding.Left + Padding.Right, Padding.Top + Padding.Bottom);
	return (Index / FVector2D(CountX, CountY)) * PanelSize;
}

FVector2D UUWItemGrid::IndexToAbsolutePosition(const FGridPair& InIndex) const
{
	FVector2D InLocal = IndexToLocalPosition(InIndex);
	return UUserInterfaceLibrary::LocalToAbsolute(Canv_SlotArea, InLocal);
}

FVector2D UUWItemGrid::GetCellSize() const
{
	FVector2D PanelSize = SlotAreaCanvasSize - FVector2D(Padding.Left + Padding.Right, Padding.Top + Padding.Bottom);
	FVector2D CellSize = FVector2D(PanelSize.X / float(CountX), PanelSize.Y / float(CountY));
	return CellSize;
}

bool UUWItemGrid::CanPlaceAt(const FGridPair& InIndex, int32 SizeX, int32 SizeY) const
{
	if (InIndex.X < 0 || InIndex.Y < 0 || InIndex.X + SizeX > CountX || InIndex.Y + SizeY > CountY)
	{
		return false;
	}

	for (int32 Y = InIndex.Y; Y < InIndex.Y + SizeY; ++Y)
	{
		for (int32 X = InIndex.X; X < InIndex.X + SizeX; ++X)
		{
			if (UsingCells.Contains(FGridPair(X, Y)))
				return false;
		}
	}
	return true;
}

bool UUWItemGrid::CreateAndSetItem(const FGridPair& InIndex, const FDraggableItemData& InItemData, bool bGenerateChangedNotify)
{
	if (!CanPlaceAt(InIndex, InItemData.SizeX, InItemData.SizeY))
		return false;

	if (!ItemTemplate)
		return false;

	UUWDraggableItem* Item = CreateWidget<UUWDraggableItem>(Canv_SlotArea, ItemTemplate);
	Item->SetItemData(InItemData);

	Internal_SetItem(InIndex, Item, bGenerateChangedNotify);

	return true;
}

bool UUWItemGrid::SetItem(const FGridPair& InIndex, UUWDraggableItem* InItem, bool bGenerateChangedNotify)
{
	if (!CanPlaceAt(InIndex, InItem->GetItemData().SizeX, InItem->GetItemData().SizeY))
		return false;

	Internal_SetItem(InIndex, InItem, bGenerateChangedNotify);

	return true;
}

UUWDraggableItem* UUWItemGrid::GetItem(const FGridPair& InIndex) const
{
	const TObjectPtr<UUWDraggableItem>* ppItem = UsingCells.Find(InIndex);
	if (!ppItem)
		return nullptr;

	const TObjectPtr<UUWDraggableItem> pItem = *ppItem;
	if (pItem)
		return pItem.Get();
	
	return nullptr;
}

bool UUWItemGrid::GetItemIndex(UUWDraggableItem* InItem, FGridPair& OutIndex) const
{
	const FGridPair* pIndex = Items.FindKey(InItem);
	if (!pIndex)
	{
		return false;
	}

	OutIndex = *pIndex;
	return true;
}

bool UUWItemGrid::RemoveItem(class UUWDraggableItem* InItem, bool bGenerateChangedNotify)
{
	FGridPair Index;
	if (!GetItemIndex(InItem, Index))
	{
		return false;
	}
	
	Items.Remove(Index);
	
	FIntVector2 ItemSize = FIntVector2(InItem->GetItemData().SizeX, InItem->GetItemData().SizeY);
	for (int32 Y = Index.Y; Y < Index.Y + ItemSize.Y; ++Y)
	{
		for (int32 X = Index.X; X < Index.X + ItemSize.X; ++X)
		{
			UsingCells.Remove(FGridPair(X, Y));
		}
	}

	Canv_SlotArea->RemoveChild(InItem);

	if (bGenerateChangedNotify)
	{
		Internal_OnChanged();
	}

	return true;
}

void UUWItemGrid::ClearItems(bool bGenerateChangedNotify)
{
	for (auto Item : Items)
	{
		Canv_SlotArea->RemoveChild(Item.Value);
	}

	Items.Empty();
	UsingCells.Empty();

	if (bGenerateChangedNotify)
	{
		Internal_OnChanged();
	}
}

UUWItemGridCell* UUWItemGrid::GetCell(const FGridPair& InIndex) const
{
	if (InIndex.X < 0 || InIndex.Y < 0 || InIndex.X >= CountX || InIndex.Y >= CountY)
		return nullptr;

	int32 LinearIndex = InIndex.Y * CountX + InIndex.X;
	return Cells[LinearIndex];
}

void UUWItemGrid::ResetCellsMode(EItemGridCellMode InMode)
{
	for (int32 i = 0; i < Cells.Num(); ++i)
	{
		Cells[i]->SetItemGridCellMode(InMode);
	}
}

void UUWItemGrid::LoadFromContainer(UDraggableItemContainer* InContainer, bool bGenerateChangedNotify)
{
	ClearItems(false);

	for (auto ItemDataPair : InContainer->GetItems())
	{
		const FGridPair& Index = ItemDataPair.Key;
		const FDraggableItemData& ItemData = ItemDataPair.Value;
		CreateAndSetItem(Index, ItemData, false);
	}

	if (bGenerateChangedNotify)
	{
		Internal_OnChanged();
	}
}

void UUWItemGrid::LoadFromUserData(UUserData* InUserData, bool bGenerateChangedNotify)
{
	if (InUserData)
	{
		LoadFromContainer(InUserData->DraggableItems, bGenerateChangedNotify);
	}
}

void UUWItemGrid::StoreToUserData(UUserData* InUserData) const
{
	InUserData->DraggableItems->ClearItems();

	for (auto ItemWidgetPair : Items)
	{
		const FGridPair& Index = ItemWidgetPair.Key;
		const FDraggableItemData& ItemData = ItemWidgetPair.Value->GetItemData();
		InUserData->DraggableItems->SetItem(Index, ItemData);
	}
}

bool UUWItemGrid::Sort(bool bGenerateChangedNotify)
{
	TObjectPtr<UDraggableItemContainer> Container = NewObject<UDraggableItemContainer>();
	for (auto ItemWidgetPair : Items)
	{
		const FGridPair& Index = ItemWidgetPair.Key;
		const FDraggableItemData& ItemData = ItemWidgetPair.Value->GetItemData();
		Container->SetItem(Index, ItemData);
	}

	if (!Container->Sort(CountX, CountY))
	{
		return false;
	}

	ClearItems(false);

	for (auto ItemDataPair : Container->GetItems())
	{
		const FGridPair& Index = ItemDataPair.Key;
		const FDraggableItemData& ItemData = ItemDataPair.Value;
		CreateAndSetItem(Index, ItemData, false);
	}

	if (bGenerateChangedNotify)
	{
		Internal_OnChanged();
	}

	return true;
}

void UUWItemGrid::InitializeItemGrid(UUWItemGrid* InItemGrid, const FVector2D& InGridSize)
{
	FVector2D AbsoluteRootCanvasSize = InGridSize;
	FVector2D LocalSlotAreaCanvasSize = UUserInterfaceLibrary::AbsoluteToLocal(InItemGrid->Canv_SlotArea->GetParent(), AbsoluteRootCanvasSize);
	InItemGrid->SlotAreaCanvasSize = LocalSlotAreaCanvasSize;
	InItemGrid->ReplaceElements();
}
