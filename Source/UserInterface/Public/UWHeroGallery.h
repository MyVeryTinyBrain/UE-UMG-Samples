// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include <HeroData.h>
#include "UserDataWidget.h"
#include "UWHeroGallery.generated.h"

/**
 * 
 */
UCLASS()
class USERINTERFACE_API UUWHeroGallery : public UUserDataWidget
{
	GENERATED_BODY()

	UPROPERTY(meta = (BindWidget))
	class UCanvasPanel* Canv_Root;

	UPROPERTY(meta = (BindWidget))
	class UCanvasPanel* Canv_HeroGallery;

	UPROPERTY(meta = (BindWidget))
	class UUWHeroList* WBHL_HeroList;

	UPROPERTY()
	TObjectPtr<class UHeroGalleryWidget> CurrentHeroGalleryWidget;

	UPROPERTY()
	TObjectPtr<UWidget> CurrentWidget = nullptr;
	
	UPROPERTY()
	TObjectPtr<UWidget> NextWidget = nullptr;

private:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess))
	TObjectPtr<class UDataTable> HeroDescriptionsTable = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess))
	TObjectPtr<class UDataTable> ItemMapDataTable = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess))
	TObjectPtr<class UDataTable> SkillMapDataTable = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess))
	TSubclassOf<class UHeroGalleryWidget> HeroGalleryWidgetTemplate;

protected:
	virtual void NativePreConstruct() override;
	virtual void NativeConstruct() override;

	UFUNCTION()
	virtual void OnHeroButtonClicked(const FHeroDesc& HeroDesc);

	UFUNCTION()
	virtual void OnEscapeButtonClicked();

	UFUNCTION()
	void OnFadeInEnded();

public:
	UFUNCTION(BlueprintCallable)
	void Update();
};
