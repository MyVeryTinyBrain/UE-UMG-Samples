// Fill out your copyright notice in the Description page of Project Settings.


#include "UWDraggableItemZone.h"
#include "UWDraggableItem.h"
#include <Components/PanelWidget.h>
#include <Blueprint/WidgetLayoutLibrary.h>
#include <Blueprint/SlateBlueprintLibrary.h>
#include <Components/CanvasPanelSlot.h>
#include <Components/CanvasPanel.h>
#include "UWItemGrid.h"
#include "UWItemStorage.h"
#include <Components/Image.h>
#include "UWItemGridCell.h"
#include "UserInterfaceLibrary.h"
#include "UWTrashCan.h"

void UUWDraggableItemZone::NativePreConstruct()
{
	Super::NativePreConstruct();
}

void UUWDraggableItemZone::NativeConstruct()
{
	Super::NativeConstruct();
	for (int32 i = 0; i < ItemStorages.Num(); ++i)
	{
		if (!ItemStorages[i])
			continue;

		ItemStorages[i]->OnClickedSlot.AddDynamic(this, &UUWDraggableItemZone::Internal_OnClickedSlot);
	}
	
	if (UCanvasPanelSlot* ClickAreaCanvasPanelSlot = Cast<UCanvasPanelSlot>(Img_ClickArea->Slot))
	{
		ClickAreaCanvasPanelSlot->SetZOrder(100000);
	}
	Img_ClickArea->SetVisibility(ESlateVisibility::Collapsed);
}

void UUWDraggableItemZone::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);

	if (CurrentDraggingItem)
	{
		// Drag
		if (UCanvasPanelSlot* ItemPanelSlot = Cast<UCanvasPanelSlot>(CurrentDraggingItem->Slot))
		{
			FVector2D MouseInLocal = UUserInterfaceLibrary::GetMousePositionOnLocal(CurrentDraggingItem->GetParent());
			ItemPanelSlot->SetPosition(MouseInLocal + DragOffsetInLocal);
		}

		// Show And Calculated Overlapped Cells
		float MostOverlappedGridArea = 0;
		OverlappedItemStorage = nullptr;
		bCanPlace = true;
		for (int32 i = 0; i < ItemStorages.Num(); ++i)
		{
			UUWItemGrid* Grid = ItemStorages[i]->GetItemGrid();
			Grid->ResetCellsMode(EItemGridCellMode::Deactive);

			float OverlappedGridArea = UUserInterfaceLibrary::WidgetOverlapAreaOnAbsolute(Grid, CurrentDraggingItem);
			if (OverlappedGridArea > MostOverlappedGridArea)
			{
				MostOverlappedGridArea = OverlappedGridArea;
				OverlappedItemStorage = ItemStorages[i];
			}

			if (OverlappedGridArea > 0)
			{
				for (int32 Y = 0; Y < CurrentDraggingItem->GetItemData().SizeY; ++Y)
				{
					for (int32 X = 0; X < CurrentDraggingItem->GetItemData().SizeX; ++X)
					{
						FVector2D DragItemCellCenterInAbsolute = UUWDraggableItem::GetCellCenterInAbsolute(CurrentDraggingItem, FGridPair(X, Y));
						FGridPair BaseGridCellIndex = Grid->AbsolutePositionToIndex(DragItemCellCenterInAbsolute);

						if (X == 0 && Y == 0)
						{
							OverlappedLeftTopIndex = BaseGridCellIndex;
						}

						FVector2D DragItemCellSizeInAbsolute = UUWDraggableItem::GetCellSizeInAbsolute(CurrentDraggingItem);
						FVector2D DragItemCellLTInAbsolute = DragItemCellCenterInAbsolute - DragItemCellSizeInAbsolute * 0.5f;
						FVector2D DragItemCellRBInAbsolute = DragItemCellCenterInAbsolute + DragItemCellSizeInAbsolute * 0.5f;
						FWidgetRect DragItemRect = FWidgetRect(DragItemCellLTInAbsolute.X, DragItemCellRBInAbsolute.X, DragItemCellLTInAbsolute.Y, DragItemCellRBInAbsolute.Y);

						UUWItemGridCell* MostOverlappedGridCell = nullptr;
						float MostOverlappedCellArea = 0;
						FGridPair MostOverlappedGridCellIndex;

						for (int32 YOffset = -1; YOffset <= +1; ++YOffset)
						{
							for (int32 XOffset = -1; XOffset <= +1; ++XOffset)
							{
								FGridPair GridCellIndex = FGridPair(BaseGridCellIndex.X + XOffset, BaseGridCellIndex.Y + YOffset);

								if (UUWItemGridCell* GridCell = Grid->GetCell(GridCellIndex))
								{
									FWidgetRect GridCellRect = UUserInterfaceLibrary::GetWidgetRectOnAbsolute(GridCell);

									float OverlappedCellArea = DragItemRect.OverlapArea(GridCellRect);
									if (OverlappedCellArea > MostOverlappedCellArea)
									{
										MostOverlappedCellArea = OverlappedCellArea;
										MostOverlappedGridCell = GridCell;
										MostOverlappedGridCellIndex = GridCellIndex;
									}
								}
							}
						}

						if (MostOverlappedGridCell)
						{
							if (Grid->CanPlaceAt(MostOverlappedGridCellIndex, 1, 1))
							{
								MostOverlappedGridCell->SetItemGridCellMode(EItemGridCellMode::Active);
							}
							else
							{
								MostOverlappedGridCell->SetItemGridCellMode(EItemGridCellMode::Invalid);
								bCanPlace = false;
							}
						}
					}
				}
			}
		}
	}

	// Update Trash Can Hover State
	if (CurrentDraggingItem && TrashCan && OverlapTrashCanWithDraggingItem())
	{
		TrashCan->SetHoverState(true);
	}
	else
	{
		TrashCan->SetHoverState(false);
	}

	// Throwing Item Animation
	TArray<int32> CompletedThrowingItemIndices;
	for (int32 i = 0; i < ThrowingItems.Num(); ++i)
	{
		FThrowingItem& ThrowingItem = ThrowingItems[i];

		ThrowingItem.AccumulatedTime += InDeltaTime;
		float Ratio = 1;
		if (ThrowingItem.Duration > 0)
		{
			Ratio = ThrowingItem.AccumulatedTime / ThrowingItem.Duration;
		}
		Ratio = FMath::Clamp(Ratio, 0, 1);
		
		// 크기가 0이 되는 속도보다 두 배 빠르게 목표의 중심으로 이동합니다.
		float PositionRatio = FMath::Clamp(Ratio * 2, 0, 1);
		// 그래프 파형 적용
		PositionRatio = FMath::Pow(PositionRatio, 0.5f);

		FVector2D ItemSizeInAbsolute = UUserInterfaceLibrary::GetWidgetSizeOnAbsolute(ThrowingItem.ThrowingItemWidget);
		FVector2D TargetInAbsolute = 
			UUserInterfaceLibrary::GetAbsolutePosition(ThrowingItem.TargetWidget) + 
			UUserInterfaceLibrary::GetWidgetSizeOnAbsolute(ThrowingItem.TargetWidget) * 0.5f; // This is offset for move to center of Target Widget
		FVector2D AbsolutePosition = FMath::Lerp(ThrowingItem.StartPositionInAbsolute, TargetInAbsolute, PositionRatio);
		FVector2D LocalPosition = UUserInterfaceLibrary::AbsoluteToLocal(ThrowingItem.ThrowingItemWidget->GetParent(), AbsolutePosition);
		FVector2D Alignment = FMath::Lerp(ThrowingItem.StartAlignment, FVector2D(0.5f, 0.5f), PositionRatio);
		float Scale = FMath::Lerp(ThrowingItem.StartScale, ThrowingItem.EndScale, Ratio);

		if (UCanvasPanelSlot* ThrowingItemPanelSlot = Cast<UCanvasPanelSlot>(ThrowingItem.ThrowingItemWidget->Slot))
		{
			ThrowingItemPanelSlot->SetAlignment(Alignment);
			ThrowingItemPanelSlot->SetPosition(LocalPosition);
		}
		FWidgetTransform ThrowingItemTransform = ThrowingItem.ThrowingItemWidget->GetRenderTransform();
		ThrowingItemTransform.Scale = FVector2D::One() * Scale;
		ThrowingItem.ThrowingItemWidget->SetRenderTransform(ThrowingItemTransform);

		if (Ratio == 1)
		{
			CompletedThrowingItemIndices.Add(i);
		}
	}

	// Remove Completed Throwing Items
	int32 IndexOffset = 0;
	for (int32 CompletedThrowingItemIndex : CompletedThrowingItemIndices)
	{
		int32 Index = CompletedThrowingItemIndex - IndexOffset;
		const FThrowingItem& ThrowingItem = ThrowingItems[Index];

		Canv_Root->RemoveChild(ThrowingItem.ThrowingItemWidget);

		ThrowingItems.RemoveAt(Index);
		IndexOffset--;
	}

	// Get Mouse Input
	if (GetOwningPlayer()->WasInputKeyJustPressed(EKeys::LeftMouseButton))
	{
		Internal_OnMouseButtonDown_AtViewport();
	}
}

void UUWDraggableItemZone::Internal_OnMouseButtonDown_AtViewport()
{
	// Drop Item
	if (CurrentDraggingItem && OverlappedItemStorage)
	{
		int32 ItemCountX = CurrentDraggingItem->GetItemData().SizeX;
		int32 ItemCountY = CurrentDraggingItem->GetItemData().SizeY;
		int32 GridCountX = OverlappedItemStorage->GetItemGrid()->GetCountX();
		int32 GridCountY = OverlappedItemStorage->GetItemGrid()->GetCountY();
		if (OverlappedLeftTopIndex.X >= 0 &&
			OverlappedLeftTopIndex.Y >= 0 &&
			OverlappedLeftTopIndex.X + ItemCountX <= GridCountX &&
			OverlappedLeftTopIndex.Y + ItemCountY <= GridCountY &&
			bCanPlace)
		{
			OverlappedItemStorage->GetItemGrid()->CreateAndSetItem(OverlappedLeftTopIndex, CurrentDraggingItem->GetItemData());
			StopDrag();
		}
	}

	// Throw Item into Trash Can
	if (OverlapTrashCanWithDraggingItem())
	{
		UUWDraggableItem* ThrowingItemWidget = StopDrag(false);
		FVector2D ThrowingWidgetInAbsolute = UUserInterfaceLibrary::GetAbsolutePosition(ThrowingItemWidget);
		FVector2D ThrowingWidgetAlignment = FVector2D(0, 0);
		if (UCanvasPanelSlot* ThrowingItemPanelSlot = Cast<UCanvasPanelSlot>(ThrowingItemWidget->Slot))
		{
			ThrowingWidgetAlignment = ThrowingItemPanelSlot->GetAlignment();
		}
		FThrowingItem ThrowingItem(ThrowingItemWidget, 0.4f, ThrowingWidgetInAbsolute, TrashCan, ThrowingWidgetAlignment, 1, 0);
		ThrowingItems.Add(ThrowingItem);
	}
}

void UUWDraggableItemZone::Internal_OnClickedSlot(UUWItemStorage* InItemStorage, const FGridPair& InIndex)
{
	if (CurrentDraggingItem)
	{
		return;
	}

	if (UUWItemGrid* Grid = InItemStorage->GetItemGrid())
	{
		if (UUWDraggableItem* Item = Grid->GetItem(InIndex))
		{
			UUWDraggableItem* NewItem = UUWDraggableItem::Copy(ItemTemplate, Item, Item->GetItemData(), Canv_Root);
			NewItem->SetButtonEnable(false);

			StartDrag(NewItem, Item->GetCachedGeometry(), true);
			Grid->RemoveItem(Item);
		}
	}
}

void UUWDraggableItemZone::StartDrag(UUWDraggableItem* InItem, const FGeometry& InItemGeometry, bool UseOffset)
{
	CurrentDraggingItem = InItem;
	if (UseOffset)
	{
		FVector2D MouseInLocal = UUserInterfaceLibrary::GetMousePositionOnLocal(Canv_Root);
		FVector2D ItemInAbsolute = InItemGeometry.GetAbsolutePosition();
		FVector2D ItemInLocal = Canv_Root->GetCachedGeometry().AbsoluteToLocal(ItemInAbsolute);
		DragOffsetInLocal = ItemInLocal - MouseInLocal;
	}
	else
	{
		DragOffsetInLocal = FVector2D::ZeroVector;
	}

	Img_ClickArea->SetVisibility(ESlateVisibility::Visible);

	OnStartDrag.Broadcast();
}

bool UUWDraggableItemZone::OverlapTrashCanWithDraggingItem() const
{
	if (CurrentDraggingItem && TrashCan)
	{
		FWidgetRect ItemRect = UUserInterfaceLibrary::GetWidgetRectOnAbsolute(CurrentDraggingItem);
		FWidgetRect TrashCanRect = UUserInterfaceLibrary::GetWidgetRectOnAbsolute(TrashCan);
		return ItemRect.Overlap(TrashCanRect);
	}
	return false;
}

UUWDraggableItem* UUWDraggableItemZone::StopDrag(bool bRemoveDraggingItem)
{
	UUWDraggableItem* Temp = CurrentDraggingItem;
	if (bRemoveDraggingItem)
	{
		Canv_Root->RemoveChild(CurrentDraggingItem);
	}
	CurrentDraggingItem = nullptr;

	for (int32 i = 0; i < ItemStorages.Num(); ++i)
	{
		UUWItemGrid* Grid = ItemStorages[i]->GetItemGrid();
		Grid->ResetCellsMode(EItemGridCellMode::Deactive);
	}

	Img_ClickArea->SetVisibility(ESlateVisibility::Collapsed);

	if (Temp)
	{
		OnEndDrag.Broadcast();
	}

	return Temp;
}

void UUWDraggableItemZone::AddItemStorage(UUWItemStorage* InItemStorage)
{
	InItemStorage->OnClickedSlot.AddDynamic(this, &UUWDraggableItemZone::Internal_OnClickedSlot);
	ItemStorages.Add(InItemStorage);
}
