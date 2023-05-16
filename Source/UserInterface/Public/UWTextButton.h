// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "UWTextButton.generated.h"

class UUWTextButton;
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnTextButtonClickedEvent, UUWTextButton*, InTextButton);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnTextButtonPressedEvent, UUWTextButton*, InTextButton);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnTextButtonReleasedEvent, UUWTextButton*, InTextButton);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnTextButtonHoverEvent, UUWTextButton*, InTextButton);

/**
 * 
 */
UCLASS()
class USERINTERFACE_API UUWTextButton : public UUserWidget
{
	GENERATED_BODY()
	
	UPROPERTY(meta = (BindWidget))
	class UTextBlock* Txt_Title;
	
	UPROPERTY(meta = (BindWidget))
	class UButton* Button;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = true))
	FString Title = TEXT("Button Text");

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = true))
	FSlateFontInfo Font;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = true))
	float HoveredFontScale = 1.2f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = true))
	float HoveredFontScaleChangeDuration = 0.1f;

	float HoveredFontScaleRatio;
	bool bIsHovered;

public:
	FOnTextButtonClickedEvent OnTextButtonClicked;
	FOnTextButtonPressedEvent OnTextButtonPressed;
	FOnTextButtonReleasedEvent OnTextButtonReleased;
	FOnTextButtonHoverEvent OnTextButtonHover;
	FOnTextButtonHoverEvent OnTextButtonUnhover;

protected:
	virtual void NativePreConstruct() override;
	virtual void NativeConstruct() override;
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;

	UFUNCTION()
	virtual void Internal_OnButtonClicked();

	UFUNCTION()
	virtual void Internal_OnButtonPressed();

	UFUNCTION()
	virtual void Internal_OnButtonReleased();

	UFUNCTION()
	virtual void Internal_OnButtonHover();

	UFUNCTION()
	virtual void Internal_OnButtonUnhover();

private:
	void UpdateTitle();
	void UpdateFont();

public:
	UFUNCTION(BlueprintCallable)
	const FString& GetTitle() const { return Title; }

	UFUNCTION(BlueprintCallable)
	void SetTitle(const FString& InTitle);

	UFUNCTION(BlueprintCallable)
	const FSlateFontInfo& GetFont() const { return Font; }

	UFUNCTION(BlueprintCallable)
	void SetFont(const FSlateFontInfo& InFont);
};
