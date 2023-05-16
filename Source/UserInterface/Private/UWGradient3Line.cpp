// Fill out your copyright notice in the Description page of Project Settings.


#include "UWGradient3Line.h"
#include <Components/Image.h>
#include <Components/PanelSlot.h>
#include <Components/CanvasPanelSlot.h>
#include <Components/PanelWidget.h>
#include <Blueprint/SlateBlueprintLibrary.h>

void UUWGradient3Line::NativeOnInitialized()
{
	Super::NativeOnInitialized();
}

void UUWGradient3Line::NativePreConstruct()
{
	Super::NativePreConstruct();
	Update();
}

void UUWGradient3Line::NativeConstruct()
{
	Super::NativeConstruct();
	Update();
}

void UUWGradient3Line::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);
}

void UUWGradient3Line::Update()
{
	UpdateLineMaterial();
	UpdateLineTransform();
}

void UUWGradient3Line::UpdateLineMaterial()
{
	UMaterialInstanceDynamic* material = Img_Line->GetDynamicMaterial();
	if (material)
	{
		material->SetVectorParameterValue(TEXT("StartColor"), StartColor);
		material->SetVectorParameterValue(TEXT("MidColor"), MidColor);
		material->SetVectorParameterValue(TEXT("EndColor"), EndColor);
		material->SetScalarParameterValue(TEXT("StartRatio"), StartRatio);
		material->SetScalarParameterValue(TEXT("MidRatio"), MidRatio);
		material->SetScalarParameterValue(TEXT("EndRatio"), EndRatio);
	}
}

void UUWGradient3Line::UpdateLineTransform()
{
	UCanvasPanelSlot* canvasPanelSlot = Cast<UCanvasPanelSlot>(Slot);
	UCanvasPanelSlot* startCanvasPanelSlot = StartTarget ? Cast<UCanvasPanelSlot>(StartTarget->Slot) : nullptr;
	UCanvasPanelSlot* endCanvasPanelSlot = EndTarget ? Cast<UCanvasPanelSlot>(EndTarget->Slot) : nullptr;

	SetRenderTransformAngle(0);
	if (StartTarget && EndTarget && canvasPanelSlot && startCanvasPanelSlot && endCanvasPanelSlot)
	{
		FVector2D startTargetPosition = startCanvasPanelSlot->GetPosition();
		FVector2D endTargetPosition = endCanvasPanelSlot->GetPosition();

		// Start to end
		FVector2D delta = endTargetPosition - startTargetPosition;
		FVector2D normalizedDelta = delta.GetSafeNormal();

		// Adjust target positions
		startTargetPosition += normalizedDelta * StartPadding;
		endTargetPosition -= normalizedDelta * EndPadding;
		delta = endTargetPosition - startTargetPosition;

		float lookAngle = FMath::RadiansToDegrees(FMath::Atan2(normalizedDelta.Y, normalizedDelta.X));
		SetRenderTransformAngle(lookAngle);

		FVector2D center = (startTargetPosition + endTargetPosition) * 0.5f;
		canvasPanelSlot->SetPosition(center);

		float distance = delta.Length();
		canvasPanelSlot->SetSize(FVector2D(distance, LineWidht));
	}
}

void UUWGradient3Line::SetStartColor(const FLinearColor& InStartColor)
{
	StartColor = InStartColor;
	UpdateLineMaterial();
}

void UUWGradient3Line::SetMidColor(const FLinearColor& InMidColor)
{
	MidColor = InMidColor;
	UpdateLineMaterial();
}

void UUWGradient3Line::SetEndColor(const FLinearColor& InEndColor)
{
	EndColor = InEndColor;
	UpdateLineMaterial();
}

void UUWGradient3Line::SetStartRatio(float InStartRatio)
{
	StartRatio = InStartRatio;
	UpdateLineMaterial();
}

void UUWGradient3Line::SetMidRatio(float InMidRatio)
{
	MidRatio = InMidRatio;
	UpdateLineMaterial();
}

void UUWGradient3Line::SetEndRatio(float InEndRatio)
{
	EndRatio = InEndRatio;
	UpdateLineMaterial();
}

void UUWGradient3Line::SetLineWidht(float InLineWidht)
{
	LineWidht = InLineWidht;
	UpdateLineTransform();
}

void UUWGradient3Line::SetStartTarget(UWidget* InStartTarget)
{
	StartTarget = InStartTarget;
	UpdateLineTransform();
}

void UUWGradient3Line::SetEndTarget(UWidget* InEndTarget)
{
	EndTarget = InEndTarget;
	UpdateLineTransform();
}

void UUWGradient3Line::SetStartPadding(float InStartPadding)
{
	StartPadding = InStartPadding;
}

void UUWGradient3Line::SetEndPadding(float InEndPadding)
{
	EndPadding = InEndPadding;
	UpdateLineTransform();
}
