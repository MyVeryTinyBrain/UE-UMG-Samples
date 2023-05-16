// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include <Engine/DataTable.h>
#include <HeroData.h>
#include <UserData.h>
#include "Blueprint/UserWidget.h"
#include "HeroGalleryWidget.generated.h"

USTRUCT(BlueprintType)
struct USERINTERFACE_API FHeroGalleryWidgetSubData
{
	GENERATED_BODY()

	FHeroGalleryWidgetSubData() : HeroType(EHeroType::None), HeroName(), ItemMapDataTable(nullptr), SkillMapDataTable(nullptr) {}

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	EHeroType HeroType;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString HeroName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UDataTable* HeroDescriptionsTable;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UDataTable* ItemMapDataTable;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UDataTable* SkillMapDataTable;
};

UCLASS()
class USERINTERFACE_API UHeroGalleryWidget : public UUserWidget
{
	GENERATED_BODY()

protected:
	UPROPERTY()
	TObjectPtr<UUserData> UserData = nullptr;

	UPROPERTY()
	FHeroGalleryWidgetSubData SubData;

public:
	void Setup(class UUserData* InUserData, const FHeroGalleryWidgetSubData& InSubData);

protected:
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void OnHeroGalleryWidgetSetup(); // Blueprint Only
	virtual void OnHeroGalleryWidgetSetup_Implementation() {}; // C++ Only

	virtual void NativeOnHeroGalleryWidgetSetup() {}
};
