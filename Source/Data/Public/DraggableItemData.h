// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include <Engine/DataTable.h>
#include "DraggableItemData.generated.h"

USTRUCT(BlueprintType)
struct DATA_API FGridPair : public FTableRowBase
{
	GENERATED_BODY()

	FGridPair() : X(0), Y(0) {}
	FGridPair(int32 InX, int32 InY) : X(InX), Y(InY) {}

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 X;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 Y;

	friend uint32 GetTypeHash(const FGridPair& x)
	{
		return HashCombine(GetTypeHash(x.X), GetTypeHash(x.Y));
	}
	bool operator == (const FGridPair& x) const
	{
		return X == x.X && Y == x.Y;
	}
};

USTRUCT(BlueprintType)
struct DATA_API FDraggableItemData : public FTableRowBase
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 SizeX = 1;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 SizeY = 1;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString ItemName = TEXT("ITEM NAME");

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<class UTexture2D> ItemTexture;
};

UCLASS(Blueprintable, BlueprintType)
class DATA_API UDraggableItemContainer : public UObject
{
	GENERATED_BODY()

	TMap<FGridPair, FDraggableItemData> Items;
	TMap<FGridPair, FDraggableItemData> UsingCells;

public:
	UFUNCTION(BlueprintCallable)
	bool CanPlaceAt(const FGridPair& InIndex, int32 InSizeX, int32 InSizeY) const;

	UFUNCTION(BlueprintCallable)
	bool GetItem(const FGridPair& InIndex, FDraggableItemData& OutItemData) const;

	UFUNCTION(BlueprintCallable)
	bool SetItem(const FGridPair& InIndex, const FDraggableItemData& InItemData);

	UFUNCTION(BlueprintCallable)
	bool RemoveItem(const FGridPair& InIndex, FDraggableItemData& OutItemData);

	UFUNCTION(BlueprintCallable)
	void ClearItems();

	UFUNCTION(BlueprintCallable)
	int32 Num() const { return Items.Num(); }

	UFUNCTION(BlueprintCallable)
	FGridPair AtKey(int32 InIndex) const;

	UFUNCTION(BlueprintCallable)
	const FDraggableItemData& AtValue(int32 InIndex) const;

	UFUNCTION(BlueprintCallable)
	const TMap<FGridPair, FDraggableItemData>& GetItems() const { return Items; }

	UFUNCTION(BlueprintCallable)
	bool Sort(int32 InSizeX, int32 InSizeY);

	UFUNCTION(BlueprintCallable)
	static UDraggableItemContainer* CreateProperContainer(const TArray<FDraggableItemData>& InItems, const FGridPair& InSize);
};
