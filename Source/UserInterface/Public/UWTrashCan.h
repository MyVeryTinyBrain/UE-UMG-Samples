// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "UWTrashCan.generated.h"

/**
 * 
 */
UCLASS()
class USERINTERFACE_API UUWTrashCan : public UUserWidget
{
	GENERATED_BODY()

	UPROPERTY(meta = (BindWidget))
	class UImage* Img_Icon;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess))
	float UnhoverIconScale = 0.5f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess))
	float HoverIconScale = 1.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess))
	float IconScaleChangePower = 10.0f;

	float IconScale;
	bool bHover;

protected:
	virtual void NativeConstruct() override;
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;

private:
	void ApplyIconScale();

public:
	UFUNCTION(BlueprintCallable)
	bool GetHoverState() const { return bHover; }

	UFUNCTION(BlueprintCallable)
	void SetHoverState(bool InHoverState);
};
