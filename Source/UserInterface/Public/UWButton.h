// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include <Components/Button.h>
#include "Blueprint/UserWidget.h"
#include "UWButton.generated.h"

/**
 * 
 */
UCLASS()
class USERINTERFACE_API UUWButton : public UUserWidget
{
	GENERATED_BODY()
	
	UPROPERTY(meta = (BindWidget))
	class UButton* Button;

	UPROPERTY(meta = (BindWidget))
	class UTextBlock* TextBlock;

private:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, BlueprintGetter = "GetText", BlueprintSetter = "SetText", meta = (AllowPrivateAccess))
	FText Text = FText::FromString(TEXT("TEXT"));
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, BlueprintGetter = "GetFontColor", BlueprintSetter = "SetFontColor", meta = (AllowPrivateAccess))
	FLinearColor FontColor = FLinearColor(1.0f, 1.0f, 1.0f, 0.5f);
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, BlueprintGetter = "GetFontSize", BlueprintSetter = "SetFontSize", meta = (AllowPrivateAccess))
	int32 FontSize = 26;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, BlueprintGetter = "GetBackgroundColor", BlueprintSetter = "SetBackgroundColor", meta = (AllowPrivateAccess))
	FLinearColor BackgroundColor = FLinearColor(1.0f, 0.4f, 0.0f, 0.5f);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, BlueprintGetter = "GetOutlineColor", BlueprintSetter = "SetOutlineColor", meta = (AllowPrivateAccess))
	FLinearColor OutlineColor = FLinearColor(1.0f, 1.0f, 1.0f, 1.0f);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, BlueprintGetter = "GetNormalColor", BlueprintSetter = "SetNormalColor", meta = (AllowPrivateAccess))
	FLinearColor NormalColor = FLinearColor(1.0f, 1.0f, 1.0f, 1.0f);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, BlueprintGetter = "GetHoverColor", BlueprintSetter = "SetHoverColor", meta = (AllowPrivateAccess))
	FLinearColor HoverColor = FLinearColor(0.5f, 0.5f, 0.5f, 1.0f);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, BlueprintGetter = "GetPressedColor", BlueprintSetter = "SetPressedColor", meta = (AllowPrivateAccess))
	FLinearColor PressedColor = FLinearColor(0.2f, 0.2f, 0.2f, 1.0f);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, BlueprintGetter = "GetOutlineWidth", BlueprintSetter = "SetOutlineWidth", meta = (AllowPrivateAccess))
	float OutlineWidth = 1.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, BlueprintGetter = "IsUseTransparentOutline", BlueprintSetter = "SetUseTransparentOutline", meta = (AllowPrivateAccess))
	bool UseTransparentOutline = true;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, BlueprintGetter = "IsEnabledButton", BlueprintSetter = "SetButtonEnable", meta = (AllowPrivateAccess))
	bool bButtonEnable = true;

public:
	/** Called when the button is clicked */
	UPROPERTY(BlueprintAssignable, Category = "Button|Event")
	FOnButtonClickedEvent OnClicked;

	/** Called when the button is pressed */
	UPROPERTY(BlueprintAssignable, Category = "Button|Event")
	FOnButtonPressedEvent OnPressed;

	/** Called when the button is released */
	UPROPERTY(BlueprintAssignable, Category = "Button|Event")
	FOnButtonReleasedEvent OnReleased;

	UPROPERTY(BlueprintAssignable, Category = "Button|Event")
	FOnButtonHoverEvent OnHovered;

	UPROPERTY(BlueprintAssignable, Category = "Button|Event")
	FOnButtonHoverEvent OnUnhovered;

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
	void UpdateFontStyle();

public:
	UFUNCTION(BlueprintCallable)
	const FText& GetText() const { return Text; }

	UFUNCTION(BlueprintCallable)
	void SetText(const FText& InText);

	UFUNCTION(BlueprintCallable)
	const FLinearColor& GetFontColor() const { return FontColor; }

	UFUNCTION(BlueprintCallable)
	void SetFontColor(const FLinearColor& InColor);

	UFUNCTION(BlueprintCallable)
	int32 GetFontSize() const { return FontSize; }

	UFUNCTION(BlueprintCallable)
	void SetFontSize(int32 InSize);

	UFUNCTION(BlueprintCallable)
	const FLinearColor& GetBackgroundColor() const { return BackgroundColor; }

	UFUNCTION(BlueprintCallable)
	void SetBackgroundColor(const FLinearColor& InColor);

	UFUNCTION(BlueprintCallable)
	const FLinearColor& GetOutlineColor() const { return OutlineColor; }

	UFUNCTION(BlueprintCallable)
	void SetOutlineColor(const FLinearColor& InColor);

	UFUNCTION(BlueprintCallable)
	const FLinearColor& GetNormalColor() const { return NormalColor; }

	UFUNCTION(BlueprintCallable)
	void SetNormalColor(const FLinearColor& InColor);

	UFUNCTION(BlueprintCallable)
	const FLinearColor& GetHoverColor() const { return HoverColor; }

	UFUNCTION(BlueprintCallable)
	void SetHoverColor(const FLinearColor& InColor);

	UFUNCTION(BlueprintCallable)
	const FLinearColor& GetPressedColor() const { return PressedColor; }

	UFUNCTION(BlueprintCallable)
	void SetPressedColor(const FLinearColor& InColor);

	UFUNCTION(BlueprintCallable)
	float GetOutlineWidth() const { return OutlineWidth; }

	UFUNCTION(BlueprintCallable)
	void SetOutlineWidth(float InWidth);

	UFUNCTION(BlueprintCallable)
	bool IsUseTransparentOutline() const { return UseTransparentOutline; }

	UFUNCTION(BlueprintCallable)
	void SetUseTransparentOutline(bool InUse);

	UFUNCTION(BlueprintCallable)
	bool IsEnabledButton() const { return bButtonEnable; }

	UFUNCTION(BlueprintCallable)
	void SetButtonEnable(bool InEnable);
};
