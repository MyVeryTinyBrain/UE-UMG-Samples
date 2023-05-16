// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "HeroData.h"
#include <Engine/DataTable.h>
#include "ItemData.generated.h"

UENUM(BlueprintType)
enum class EItemType : uint8
{
	None UMETA(DisplayName = "None"),
	Skin UMETA(DisplayName = "Skin"),
};

USTRUCT(BlueprintType)
struct DATA_API FItemData : public FTableRowBase
{
	GENERATED_BODY()

	FItemData() :
		ItemType(EItemType::None), Grade(0), Cost(999999), ItemName(TEXT("ITEM NAME"))
	{}

	FItemData(EItemType itemType, int grade, int cost, const FString& itemName) :
		ItemType(itemType), Grade(grade), Cost(cost), ItemName(itemName)
	{}

	static FItemData Invalid();

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	EItemType ItemType;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (UIMin = 0, UIMax = 4, ClampMin = 0, ClampMax = 4))
	int Grade;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int Cost;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString ItemName;

	FLinearColor GetColorOfGrade() const;

	bool operator == (const FItemData& x) const;
	bool operator != (const FItemData& x) const;
};

USTRUCT(BlueprintType)
struct DATA_API FItemsArray
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<FItemData> Array;
};

USTRUCT(BlueprintType)
struct DATA_API FItemsByItemType
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TMap<EItemType, FItemsArray> Map;

	void Add(const FItemData& ItemData);
	bool Contains(FItemData ItemData) const;
	int32 Num(EItemType ItemType) const;
	TArray<FItemData>* FindItemsByItemType(EItemType ItemType);
	const TArray<FItemData>* FindItemsByItemType(EItemType ItemType) const;
};

USTRUCT(BlueprintType)
struct DATA_API FItemsByHeroType
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TMap<EHeroType, FItemsByItemType> Map;

	void Add(EHeroType HeroType, const FItemData& ItemData);
	bool Contains(EHeroType HeroType, FItemData ItemData) const;
	int32 Num(EHeroType HeroType, EItemType ItemType) const;
	TArray<FItemData>* FindItems(EHeroType HeroType, EItemType ItemType);
	const TArray<FItemData>* FindItems(EHeroType HeroType, EItemType ItemType) const;
};
