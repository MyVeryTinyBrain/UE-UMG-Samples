// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include <Components/Button.h>
#include "Blueprint/UserWidget.h"
#include "UWItemTypeSelector.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnSelectorButtonClickedEvent, int, Direction);

/**
 * 
 */
UCLASS()
class USERINTERFACE_API UUWItemTypeSelector : public UUserWidget
{
	GENERATED_BODY()
	
	UPROPERTY(meta = (BindWidget))
	class UButton* Btn_Left;

	UPROPERTY(meta = (BindWidget))
	class UTextBlock* Txt_LeftBtn;

	UPROPERTY(meta = (BindWidget))
	class UTextBlock* Txt_Title;

	UPROPERTY(meta = (BindWidget))
	class UButton* Btn_Right;

	UPROPERTY(meta = (BindWidget))
	class UTextBlock* Txt_RightBtn;

private:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, BlueprintGetter = "GetTitle", BlueprintSetter = "SetTitle", meta = (AllowPrivateAccess))
	FText Title = FText::FromString(TEXT("Item"));

	UPROPERTY(EditAnywhere, BlueprintReadWrite, BlueprintGetter = "GetTitleFontSize", BlueprintSetter = "SetTitleFontSize", meta = (AllowPrivateAccess))
	int32 TitleFontSize = 30;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, BlueprintGetter = "GetButtonFontSize", BlueprintSetter = "SetButtonFontSize", meta = (AllowPrivateAccess))
	int32 ButtonFontSize = 40;

public:
	UPROPERTY(BlueprintAssignable, Category = "Button|Event")
	FOnSelectorButtonClickedEvent OnClicked;

protected:
	virtual void NativeConstruct() override;
	virtual void NativePreConstruct() override;

	UFUNCTION()
	virtual void Internal_OnLeftClicked();

	UFUNCTION()
	virtual void Internal_OnRightClicked();

private:
	void UpdateTitle();

public:
	UFUNCTION(BlueprintCallable)
	const FText& GetTitle() const { return Title; }

	UFUNCTION(BlueprintCallable)
	void SetTitle(const FText& InTitle);
	void SetTitle(const FString& InTitle);

	UFUNCTION(BlueprintCallable)
	int32 GetTitleFontSize() const { return TitleFontSize; }

	UFUNCTION(BlueprintCallable)
	void SetTitleFontSize(int32 InTitleFontSize);

	UFUNCTION(BlueprintCallable)
	int32 GetButtonFontSize() const { return ButtonFontSize; }

	UFUNCTION(BlueprintCallable)
	void SetButtonFontSize(int32 InButtonFontSize);
};
