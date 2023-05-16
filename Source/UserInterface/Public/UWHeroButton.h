// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include <Components/Button.h>
#include <HeroData.h>
#include "Blueprint/UserWidget.h"
#include "UWHeroButton.generated.h"

class UUWHeroButton;
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnHeroButtonClickedEvent, UUWHeroButton*, HeroButton);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnHeroButtonPressedEvent, UUWHeroButton*, HeroButton);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnHeroButtonReleasedEvent, UUWHeroButton*, HeroButton);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnHeroButtonHoverEvent, UUWHeroButton*, HeroButton);

/**
 * 
 */
UCLASS()
class USERINTERFACE_API UUWHeroButton : public UUserWidget
{
	GENERATED_BODY()

	UPROPERTY(meta = (BindWidget))
	class UButton* Button;
	
	UPROPERTY(meta = (BindWidget))
	class UImage* Img_Hero;
	
	UPROPERTY(meta = (BindWidget))
	class UTextBlock* Txt_HeroName;
	
private:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, BlueprintGetter = "GetDefaultHeroTexture", BlueprintSetter = "SetDefaultHeroTexture", meta = (AllowPrivateAccess))
	TObjectPtr<class UTexture2D> DefaultHeroTexture;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, BlueprintGetter = "GetHeroDesc", BlueprintSetter = "SetHeroDesc", meta = (AllowPrivateAccess))
	FHeroDesc HeroDesc;

public:
	/** Called when the button is clicked */
	UPROPERTY(BlueprintAssignable, Category = "Button|Event")
	FOnHeroButtonClickedEvent OnClicked;

	/** Called when the button is pressed */
	UPROPERTY(BlueprintAssignable, Category = "Button|Event")
	FOnHeroButtonPressedEvent OnPressed;

	/** Called when the button is released */
	UPROPERTY(BlueprintAssignable, Category = "Button|Event")
	FOnHeroButtonReleasedEvent OnReleased;

	UPROPERTY(BlueprintAssignable, Category = "Button|Event")
	FOnHeroButtonHoverEvent OnHovered;

	UPROPERTY(BlueprintAssignable, Category = "Button|Event")
	FOnHeroButtonHoverEvent OnUnhovered;

protected:
	virtual void NativeConstruct() override;
	virtual void NativePreConstruct() override;

	UFUNCTION()
	virtual void Internal_OnClicked();

	UFUNCTION()
	virtual void Internal_OnPressed();

	UFUNCTION()
	virtual void Internal_OnReleased();

	UFUNCTION()
	virtual void Internal_OnHovered();

	UFUNCTION()
	virtual void Internal_OnUnhovered();

private:
	void Update();

public:
	UFUNCTION(BlueprintCallable)
	const class UTexture2D* GetDefaultHeroTexture() const { return DefaultHeroTexture; };

	UFUNCTION(BlueprintCallable)
	void SetDefaultHeroTexture(class UTexture2D* InDefaultHeroTexture);

	UFUNCTION(BlueprintCallable)
	FHeroDesc GetHeroDesc() const { return HeroDesc; }

	UFUNCTION(BlueprintCallable)
	void SetHeroDesc(FHeroDesc InHeroDesc);
};
