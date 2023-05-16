// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "UWSizableTextBlock.generated.h"

/**
 * 
 */
UCLASS()
class USERINTERFACE_API UUWSizableTextBlock : public UUserWidget
{
	GENERATED_BODY()

	UPROPERTY(meta = (BindWidget))
	class UWidget* Canv_Root;
	
	UPROPERTY(meta = (BindWidget))
	class UTextBlock* Txt_Text;

	UPROPERTY(meta = (BindWidget))
	class UImage* Img_Top;

	UPROPERTY(meta = (BindWidget))
	class UImage* Img_Bottom;

	UPROPERTY(meta = (BindWidget))
	class UImage* Img_left;

	UPROPERTY(meta = (BindWidget))
	class UImage* Img_Right;

private:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, BlueprintGetter = "GetText", BlueprintSetter = "SetText", meta = (AllowPrivateAccess = true, Multiline = true))
	FText Text = FText::FromString(TEXT("Text"));

	UPROPERTY(EditAnywhere, BlueprintReadWrite, BlueprintGetter = "GetFont", BlueprintSetter = "SetFont", meta = (AllowPrivateAccess))
	FSlateFontInfo Font = FSlateFontInfo();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, BlueprintGetter = "GetBorderWidth", BlueprintSetter = "SetBorderWidth", meta = (AllowPrivateAccess))
	float BorderWidth = 3.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, BlueprintGetter = "GetMargin", BlueprintSetter = "SetMargin", meta = (AllowPrivateAccess))
	FVector2D Margin = FVector2D(10.0f, 10.0f);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, BlueprintGetter = "GetAlignment", BlueprintSetter = "SetAlignment", meta = (AllowPrivateAccess))
	FVector2D Alignment = FVector2D(0, 0);

protected:
	virtual void NativePreConstruct() override;
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;

private:
	void Update();
	void UpdateBorderSize();
	void UpdateBorderWidth();

public:
	UFUNCTION(BlueprintCallable)
	const FText& GetText() const { return Text; }

	UFUNCTION(BlueprintCallable)
	void SetText(const FText& InText);

	UFUNCTION(BlueprintCallable)
	const FSlateFontInfo& GetFont() const { return Font; }

	UFUNCTION(BlueprintCallable)
	void SetFont(const FSlateFontInfo& InFont);

	UFUNCTION(BlueprintCallable)
	float GetBorderWidth() const { return BorderWidth; }

	UFUNCTION(BlueprintCallable)
	void SetBorderWidth(float InBorderWidth);

	UFUNCTION(BlueprintCallable)
	const FVector2D& GetMargin() const { return Margin; }

	UFUNCTION(BlueprintCallable)
	void SetMargin(const FVector2D& InMargin);

	UFUNCTION(BlueprintCallable)
	const FVector2D& GetAlignment() const { return Alignment; }

	UFUNCTION(BlueprintCallable)
	void SetAlignment(const FVector2D& InAlignment);
};
