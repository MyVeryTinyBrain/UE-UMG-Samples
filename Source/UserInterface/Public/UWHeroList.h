// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include <Components/WrapBox.h>
#include <HeroData.h>
#include "Blueprint/UserWidget.h"
#include "UWHeroList.generated.h"

class UUWHeroButton;
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnHeroButtonClickedEventA, const FHeroDesc&, HeroDesc);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnHeroButtonClickedEventB, UUWHeroButton*, HeroButton);

/**
 * 
 */
UCLASS()
class USERINTERFACE_API UUWHeroList : public UUserWidget
{
	GENERATED_BODY()
	
	UPROPERTY(meta = (BindWidget))
	class UImage* Img_BG;

	UPROPERTY(meta = (BindWidget))
	class UWrapBox* WB_WrapBox;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = true))
	TSubclassOf<class UUWHeroButton> ElementTemplate;

private:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, BlueprintGetter = "GetHeroDescriptions", BlueprintSetter = "SetHeroDescriptions", meta = (AllowPrivateAccess))
	TArray<FHeroDesc> HeroDescriptions;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, BlueprintGetter = "GetBackgroundColor", BlueprintSetter = "SetBackgroundColor", meta = (AllowPrivateAccess))
	FLinearColor BackgroundColor;

public:

	UPROPERTY(BlueprintAssignable, Category = "Button|Event")
	FOnHeroButtonClickedEventA OnHeroButtonClickedA;

	UPROPERTY(BlueprintAssignable, Category = "Button|Event")
	FOnHeroButtonClickedEventB OnHeroButtonClickedB;

protected:
	virtual void NativeConstruct() override;
	virtual void NativePreConstruct() override;

	UFUNCTION()
	virtual void OnHeroButtonClicked(class UUWHeroButton* HeroButton);

private:
	void UpdateHeroList();
	void UpdateVisual();

public:
	UFUNCTION(BlueprintCallable)
	const TArray<FHeroDesc>& GetHeroDescriptions() const { return HeroDescriptions; }
	
	UFUNCTION(BlueprintCallable)
	void SetHeroDescriptions(const TArray<FHeroDesc>& InHeroDescriptions);

	UFUNCTION(BlueprintCallable)
	const FLinearColor& GetBackgroundColor() const { return BackgroundColor; }

	UFUNCTION(BlueprintCallable)
	void SetBackgroundColor(const FLinearColor& InBackgroundColor);
};
