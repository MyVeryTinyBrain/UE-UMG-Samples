// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "UWItemGridCell.generated.h"

UENUM(BlueprintType)
enum class EItemGridCellMode : uint8
{
	Deactive,
	Active,
	Invalid,
};

/**
 * 
 */
UCLASS()
class USERINTERFACE_API UUWItemGridCell : public UUserWidget
{
	GENERATED_BODY()
	
	UPROPERTY(meta = (BindWidget))
	class UImage* Img_Base;

	UPROPERTY()
	FLinearColor BaseColor = FLinearColor::White;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess))
	FLinearColor DeactiveColor = FLinearColor::Transparent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess))
	FLinearColor ActiveColor = FLinearColor::White;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess))
	FLinearColor InvalidColor = FLinearColor::Red;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess))
	float CellModeColorChangePower = 7.5f;

	EItemGridCellMode ItemGridCellMode;
	FLinearColor NewColor;

protected:
	virtual void NativePreConstruct() override;
	virtual void NativeConstruct() override;
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;

public:
	UFUNCTION(BlueprintCallable)
	void SetItemGridCellMode(EItemGridCellMode InMode);
};
