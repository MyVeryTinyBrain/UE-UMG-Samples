// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ItemData.h"
#include "SkillData.h"
#include "DraggableItemData.h"
#include "UserData.generated.h"

USTRUCT(BlueprintType)
struct DATA_API FItemKey
{
	GENERATED_BODY()

	FItemKey() : HeroType(), ItemType() {}
	FItemKey(EHeroType heroType, EItemType itemType) : HeroType(heroType), ItemType(itemType) {}

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	EHeroType HeroType;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	EItemType ItemType;

	friend uint32 GetTypeHash(const FItemKey& x)
	{
		return HashCombine(GetTypeHash(x.HeroType), GetTypeHash(x.ItemType));
	}
	bool operator == (const FItemKey& x) const
	{
		return HeroType == x.HeroType && ItemType == x.ItemType;
	}
};

UCLASS(Blueprintable, BlueprintType)
class DATA_API UUserData : public UObject
{
	GENERATED_BODY()

public:
	UUserData();

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FName HeroName = TEXT("UserName");
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 Cash = 9999999;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FItemsByHeroType OwnedItems;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TMap<FItemKey, FItemData> EquippedItems;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TMap<EHeroType, FSkillArray> UnlockedSkills;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<UDraggableItemContainer> DraggableItems;
};