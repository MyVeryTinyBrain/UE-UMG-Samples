// Fill out your copyright notice in the Description page of Project Settings.


#include "UWTrashCan.h"
#include <Components/Image.h>

void UUWTrashCan::NativeConstruct()
{
	Super::NativeConstruct();

	bHover = false;
	IconScale = UnhoverIconScale;
	ApplyIconScale();
}

void UUWTrashCan::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);

	float TargetIconScale;
	if (bHover)
	{
		TargetIconScale = HoverIconScale;
	}
	else
	{
		TargetIconScale = UnhoverIconScale;
	}
	IconScale = FMath::Lerp(IconScale, TargetIconScale, InDeltaTime * IconScaleChangePower);

	ApplyIconScale();
}

void UUWTrashCan::ApplyIconScale()
{
	FWidgetTransform Transform = Img_Icon->GetRenderTransform();
	Transform.Scale = FVector2D::One() * IconScale;
	Img_Icon->SetRenderTransform(Transform);
}

void UUWTrashCan::SetHoverState(bool InHoverState)
{
	bHover = InHoverState;
}
