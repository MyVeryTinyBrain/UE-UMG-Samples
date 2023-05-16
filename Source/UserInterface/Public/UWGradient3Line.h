// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "UWGradient3Line.generated.h"

/**
 * 
 */
UCLASS()
class USERINTERFACE_API UUWGradient3Line : public UUserWidget
{
	GENERATED_BODY()
	
	UPROPERTY(meta = (BindWidget))
	class UImage* Img_Line;

private:
	// Gradient variables

	UPROPERTY(EditAnywhere, BlueprintReadWrite, BlueprintGetter = "GetStartColor", BlueprintSetter = "SetStartColor", meta = (AllowPrivateAccess))
	FLinearColor StartColor = FLinearColor::Red;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, BlueprintGetter = "GetMidColor", BlueprintSetter = "SetMidColor", meta = (AllowPrivateAccess))
	FLinearColor MidColor = FLinearColor::Green;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, BlueprintGetter = "GetEndColor", BlueprintSetter = "SetEndColor", meta = (AllowPrivateAccess))
	FLinearColor EndColor = FLinearColor::Blue;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, BlueprintGetter = "GetStartRatio", BlueprintSetter = "SetStartRatio", meta = (UIMin = 0.0, ClampMin = 0.0, UIMax = 1.0, ClampMax = 1.0, AllowPrivateAccess))
	float StartRatio = 0.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, BlueprintGetter = "GetMidRatio", BlueprintSetter = "SetMidRatio", meta = (UIMin = 0.0, ClampMin = 0.0, UIMax = 1.0, ClampMax = 1.0, AllowPrivateAccess))
	float MidRatio = 0.5f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, BlueprintGetter = "GetEndRatio", BlueprintSetter = "SetEndRatio", meta = (UIMin = 0.0, ClampMin = 0.0, UIMax = 1.0, ClampMax = 1.0, AllowPrivateAccess))
	float EndRatio = 1.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, BlueprintGetter = "GetLineWidht", BlueprintSetter = "SetLineWidht", meta = (AllowPrivateAccess))
	float LineWidht = 10.0f;

	// Target variables
	/* This widget's alignment should be (0.5, 0.5) */
	/* This widget's targets are should be child of this widget's parent */

	UPROPERTY(EditAnywhere, BlueprintReadWrite, BlueprintGetter = "GetStartTarget", BlueprintSetter = "SetStartTarget", meta = (AllowPrivateAccess))
	TObjectPtr<UWidget> StartTarget = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, BlueprintGetter = "GetEndTarget", BlueprintSetter = "SetEndTarget", meta = (AllowPrivateAccess))
	TObjectPtr<UWidget> EndTarget = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, BlueprintGetter = "GetStartPadding", BlueprintSetter = "SetStartPadding", meta = (AllowPrivateAccess))
	float StartPadding = 0.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, BlueprintGetter = "GetEndPadding", BlueprintSetter = "SetEndPadding", meta = (AllowPrivateAccess))
	float EndPadding = 0.0f;

protected:
	virtual void NativeOnInitialized();
	virtual void NativePreConstruct() override;
	virtual void NativeConstruct() override;
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime);

private:
	void Update();
	void UpdateLineMaterial();
	void UpdateLineTransform();

public:
	// CallInEditor

	UFUNCTION(BlueprintCallable)
	const FLinearColor& GetStartColor() const { return StartColor; }

	UFUNCTION(BlueprintCallable)
	void SetStartColor(const FLinearColor& InStartColor);

	UFUNCTION(BlueprintCallable)
	const FLinearColor& GetMidColor() const { return MidColor; }

	UFUNCTION(BlueprintCallable)
	void SetMidColor(const FLinearColor& InMidColor);

	UFUNCTION(BlueprintCallable)
	const FLinearColor& GetEndColor() const { return EndColor; }

	UFUNCTION(BlueprintCallable)
	void SetEndColor(const FLinearColor& InEndColor);

	UFUNCTION(BlueprintCallable)
	float GetStartRatio() const { return StartRatio; }

	UFUNCTION(BlueprintCallable)
	void SetStartRatio(float InStartRatio);

	UFUNCTION(BlueprintCallable)
	float GetMidRatio() const { return MidRatio; }

	UFUNCTION(BlueprintCallable)
	void SetMidRatio(float InMidRatio);

	UFUNCTION(BlueprintCallable)
	float GetEndRatio() const { return EndRatio; }

	UFUNCTION(BlueprintCallable)
	void SetEndRatio(float InEndRatio);

	UFUNCTION(BlueprintCallable)
	float GetLineWidht() const { return LineWidht; }

	UFUNCTION(BlueprintCallable)
	void SetLineWidht(float InLineWidht);

	UFUNCTION(BlueprintCallable)
	UWidget* GetStartTarget() const { return StartTarget; }

	UFUNCTION(BlueprintCallable)
	void SetStartTarget(UWidget* InStartTarget);

	UFUNCTION(BlueprintCallable)
	UWidget* GetEndTarget() const { return EndTarget; }

	UFUNCTION(BlueprintCallable)
	void SetEndTarget(UWidget* InEndTarget);

	UFUNCTION(BlueprintCallable)
	float GetStartPadding() const { return StartPadding; }

	UFUNCTION(BlueprintCallable)
	void SetStartPadding(float InStartPadding);

	UFUNCTION(BlueprintCallable)
	float GetEndPadding() const { return EndPadding; }

	UFUNCTION(BlueprintCallable)
	void SetEndPadding(float InEndPadding);
};
