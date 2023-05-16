// Fill out your copyright notice in the Description page of Project Settings.


#include "UWItemGridCell.h"
#include <Components/Image.h>

void UUWItemGridCell::NativePreConstruct()
{
	Super::NativePreConstruct();
}

void UUWItemGridCell::NativeConstruct()
{
	Super::NativeConstruct();

	BaseColor = DeactiveColor;
	SetItemGridCellMode(EItemGridCellMode::Deactive);
}

void UUWItemGridCell::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);

	BaseColor = FMath::Lerp(BaseColor, NewColor, InDeltaTime * CellModeColorChangePower);
	Img_Base->SetColorAndOpacity(BaseColor);
}

void UUWItemGridCell::SetItemGridCellMode(EItemGridCellMode InMode)
{
	ItemGridCellMode = InMode;

	switch (ItemGridCellMode)
	{
		case EItemGridCellMode::Deactive:
			NewColor = DeactiveColor;
			break;
		case EItemGridCellMode::Active:
			NewColor = ActiveColor;
			break;
		case EItemGridCellMode::Invalid:
			NewColor = InvalidColor;
			break;
	}
}
