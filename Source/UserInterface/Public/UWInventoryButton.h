// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "UWInventoryButton.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnInventoryButtonClickedEvent);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnInventoryButtonPressedEvent);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnInventoryButtonReleasedEvent);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnInventoryButtonHoverEvent);

/**
 * 
 */
UCLASS()
class USERINTERFACE_API UUWInventoryButton : public UUserWidget
{
	GENERATED_BODY()
	
	UPROPERTY(meta = (BindWidget))
	class UImage* Img_Icon;
	
	UPROPERTY(meta = (BindWidget))
	class UButton* Button;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess))
	TObjectPtr<class UTexture2D> IconTexture;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess))
	bool bButtonEnable = true;

public:
	FOnInventoryButtonClickedEvent OnInventoryButtonClicked;
	FOnInventoryButtonPressedEvent OnInventoryButtonPressed;
	FOnInventoryButtonReleasedEvent OnInventoryButtonReleased;
	FOnInventoryButtonHoverEvent OnInventoryButtonHover;
	FOnInventoryButtonHoverEvent OnInventoryButtonUnhover;

protected:
	virtual void NativePreConstruct() override;
	virtual void NativeConstruct() override;

	UFUNCTION()
	virtual void Internal_OnInventoryButtonClicked();
	
	UFUNCTION()
	virtual void Internal_OnInventoryButtonPressed();
	
	UFUNCTION()
	virtual void Internal_OnInventoryButtonReleased();
	
	UFUNCTION()
	virtual void Internal_OnInventoryButtonHover();
	
	UFUNCTION()
	virtual void Internal_OnInventoryButtonUnhover();

private:
	void UpdateIcon();
	void UpdateButton();

public:
	UFUNCTION(BlueprintCallable)
	void SetButtonEnable(bool InButtonEnable);
	
	UFUNCTION(BlueprintCallable)
	bool GetButtonEnable() const { return bButtonEnable; }
};
