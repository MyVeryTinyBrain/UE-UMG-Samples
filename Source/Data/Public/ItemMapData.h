// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ItemData.h"
#include <Engine/DataTable.h>
#include "ItemMapData.generated.h"

USTRUCT(BlueprintType)
struct DATA_API FItemMapData : public FTableRowBase
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	EHeroType HeroType = EHeroType::None;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	EItemType ItemType = EItemType::None;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UDataTable* ItemDataTable = nullptr;

	static class UDataTable* FindItemDataTable(class UDataTable* ItemMapDataTable, EHeroType HeroType, EItemType ItemType);
};