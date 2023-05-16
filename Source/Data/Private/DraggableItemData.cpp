// Fill out your copyright notice in the Description page of Project Settings.


#include "DraggableItemData.h"
#include <queue>
#include <vector>
#include <algorithm>

bool UDraggableItemContainer::CanPlaceAt(const FGridPair& InIndex, int32 InSizeX, int32 InSizeY) const
{
	for (int32 Y = InIndex.Y; Y < InIndex.Y + InSizeY; ++Y)
	{
		for (int32 X = InIndex.X; X < InIndex.X + InSizeX; ++X)
		{
			if (UsingCells.Contains(FGridPair(X, Y)))
				return false;
		}
	}
	return true;
}

bool UDraggableItemContainer::GetItem(const FGridPair& InIndex, FDraggableItemData& OutItemData) const
{
	const FDraggableItemData* pItemData = UsingCells.Find(InIndex);
	if (!pItemData)
	{
		return false;
	}

	OutItemData = *pItemData;
	return true;
}

bool UDraggableItemContainer::SetItem(const FGridPair& InIndex, const FDraggableItemData& InItemData)
{
	FIntVector2 ItemCount = FIntVector2(InItemData.SizeX, InItemData.SizeY);
	if (!CanPlaceAt(InIndex, ItemCount.X, ItemCount.Y))
	{
		return false;
	}

	Items.Add(InIndex, InItemData);

	for (int32 Y = InIndex.Y; Y < InIndex.Y + ItemCount.Y; ++Y)
	{
		for (int32 X = InIndex.X; X < InIndex.X + ItemCount.X; ++X)
		{
			UsingCells.Add(FGridPair(X, Y), InItemData);
		}
	}

	return true;
}

bool UDraggableItemContainer::RemoveItem(const FGridPair& InIndex, FDraggableItemData& OutItemData)
{
	if (!GetItem(InIndex, OutItemData))
	{
		return false;
	}

	Items.Remove(InIndex);

	FIntVector2 ItemCount = FIntVector2(OutItemData.SizeX, OutItemData.SizeY);
	for (int32 Y = InIndex.Y; Y < InIndex.Y + ItemCount.Y; ++Y)
	{
		for (int32 X = InIndex.X; X < InIndex.X + ItemCount.X; ++X)
		{
			UsingCells.Remove(FGridPair(X, Y));
		}
	}
	return true;
}

void UDraggableItemContainer::ClearItems()
{
	Items.Empty();
	UsingCells.Empty();
}

FGridPair UDraggableItemContainer::AtKey(int32 InIndex) const
{
	TMap<FGridPair, FDraggableItemData>::TConstIterator Iterator = Items.CreateConstIterator();
	for (int32 i = 0; i < InIndex; ++i)
	{
		++Iterator;
	}

	return Iterator->Key;
}

const FDraggableItemData& UDraggableItemContainer::AtValue(int32 InIndex) const
{
	TMap<FGridPair, FDraggableItemData>::TConstIterator Iterator = Items.CreateConstIterator();
	for (int32 i = 0; i < InIndex; ++i)
	{
		++Iterator;
	}

	return Iterator->Value;
}

bool UDraggableItemContainer::Sort(int32 InSizeX, int32 InSizeY)
{
	// 길이가 긴 순서대로 내림차순 정렬된 아이템이 담길 곳입니다.
	std::vector<FDraggableItemData> SortedDatas;
	for (auto ItemPair : Items)
	{
		SortedDatas.push_back(ItemPair.Value);
	}

	// 길이가 긴 순서대로 내림차순 정렬합니다.
	std::sort(SortedDatas.begin(), SortedDatas.end(), [](const FDraggableItemData& Left, const FDraggableItemData& Right) {
		// 각 아이템의 길이는 X크기, Y크기 중 큰 것으로 정의합니다.
		int32 LeftSz = FMath::Max(Left.SizeX, Left.SizeY);
		int32 RightSz = FMath::Max(Right.SizeX, Right.SizeY);
		
		// 길이가 긴 것이 우선입니다.
		return LeftSz > RightSz;
	});

	TSet<FGridPair> PlacedPositions;
	TMap<FGridPair, FDraggableItemData> ReplacedItems;
	for (const FDraggableItemData& ItemData : SortedDatas)
	{
		bool Placed = false;
		for (int32 StartY = 0; StartY <= InSizeY - ItemData.SizeY && !Placed; ++StartY)
		{
			for (int32 StartX = 0; StartX <= InSizeX - ItemData.SizeX && !Placed; ++StartX)
			{
				bool ValidPos = true;
				for (int32 Y = StartY; Y < StartY + ItemData.SizeY && ValidPos; ++Y)
				{
					for (int32 X = StartX; X < StartX + ItemData.SizeX && ValidPos; ++X)
					{
						if (PlacedPositions.Contains(FGridPair(X, Y)))
						{
							ValidPos = false;
						}
					}
				}

				if (ValidPos)
				{
					for (int32 Y = StartY; Y < StartY + ItemData.SizeY && ValidPos; ++Y)
					{
						for (int32 X = StartX; X < StartX + ItemData.SizeX && ValidPos; ++X)
						{
							PlacedPositions.Add(FGridPair(X, Y));
						}
					}

					ReplacedItems.Add(FGridPair(StartX, StartY), ItemData);
					Placed = true;
				}
			}
		}
	}

	// 재배열된 아이템들로 설정합니다.
	ClearItems();
	for (const auto& ReplacedItemPair : ReplacedItems)
	{
		SetItem(ReplacedItemPair.Key, ReplacedItemPair.Value);
	}

	return true;
}

UDraggableItemContainer* UDraggableItemContainer::CreateProperContainer(const TArray<FDraggableItemData>& InItems, const FGridPair& InSize)
{	
	UDraggableItemContainer* Container = NewObject<UDraggableItemContainer>();
	
	// 길이가 긴 순서대로 내림차순 정렬된 아이템이 담길 곳입니다.
	std::vector<FDraggableItemData> SortedDatas;
	for (auto Item : InItems)
	{
		SortedDatas.push_back(Item);
	}

	// 길이가 긴 순서대로 내림차순 정렬합니다.
	std::sort(SortedDatas.begin(), SortedDatas.end(), [](const FDraggableItemData& Left, const FDraggableItemData& Right) {
		// 각 아이템의 길이는 X크기, Y크기 중 큰 것으로 정의합니다.
		int32 LeftSz = FMath::Max(Left.SizeX, Left.SizeY);
		int32 RightSz = FMath::Max(Right.SizeX, Right.SizeY);

		// 길이가 긴 것이 우선입니다.
		return LeftSz > RightSz;
	});

	TSet<FGridPair> PlacedPositions;
	TMap<FGridPair, FDraggableItemData> ReplacedItems;
	for (const FDraggableItemData& ItemData : SortedDatas)
	{
		bool Placed = false;
		for (int32 StartY = 0; StartY <= InSize.Y - ItemData.SizeY && !Placed; ++StartY)
		{
			for (int32 StartX = 0; StartX <= InSize.X - ItemData.SizeX && !Placed; ++StartX)
			{
				bool ValidPos = true;
				for (int32 Y = StartY; Y < StartY + ItemData.SizeY && ValidPos; ++Y)
				{
					for (int32 X = StartX; X < StartX + ItemData.SizeX && ValidPos; ++X)
					{
						if (PlacedPositions.Contains(FGridPair(X, Y)))
						{
							ValidPos = false;
						}
					}
				}

				if (ValidPos)
				{
					for (int32 Y = StartY; Y < StartY + ItemData.SizeY && ValidPos; ++Y)
					{
						for (int32 X = StartX; X < StartX + ItemData.SizeX && ValidPos; ++X)
						{
							PlacedPositions.Add(FGridPair(X, Y));
						}
					}

					ReplacedItems.Add(FGridPair(StartX, StartY), ItemData);
					Placed = true;
				}
			}
		}
	}

	for (const auto& ReplacedItemPair : ReplacedItems)
	{
		Container->SetItem(ReplacedItemPair.Key, ReplacedItemPair.Value);
	}

	return Container;
}
