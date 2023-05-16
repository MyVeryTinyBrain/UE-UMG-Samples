// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include <Engine/DataTable.h>
#include "HeroData.generated.h"

UENUM(BlueprintType)
enum class EHeroType : uint8
{
	None UMETA(DisplayName = "None"),
	Knight UMETA(DisplayName = "Knight"),
};

USTRUCT(BlueprintType)
struct FHeroDesc : public FTableRowBase
{
	GENERATED_BODY()

	FHeroDesc() : 
		HeroType(EHeroType::None), DefaultHeroTexture(nullptr), HeroName(TEXT("HERO NAME"))
	{}

	FHeroDesc(EHeroType heroType, class UTexture2D* heroTexture, FString heroName) :
		HeroType(heroType), DefaultHeroTexture(heroTexture), HeroName(heroName)
	{}

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	EHeroType HeroType = EHeroType::None;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<class UTexture2D> DefaultHeroTexture;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString HeroName = TEXT("HERO NAME");

	static TArray<FHeroDesc> ExtractTable(UDataTable* HeroDescTable)
	{
		TArray<FHeroDesc*> Pointers;
		HeroDescTable->GetAllRows(TEXT("GetAllRows"), Pointers);

		TArray<FHeroDesc> Result;
		for (FHeroDesc* Pointer : Pointers)
			Result.Add(*Pointer);

		return Result;
	}
};
