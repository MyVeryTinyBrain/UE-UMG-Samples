// Fill out your copyright notice in the Description page of Project Settings.


#include "UWFade.h"
#include <Components/Image.h>

void UUWFade::NativeConstruct()
{
	Super::NativeConstruct();

	Image->SetVisibility(ESlateVisibility::Collapsed);
}

void UUWFade::NativePreConstruct()
{
	Super::NativePreConstruct();
}

void UUWFade::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	if (FadeMode != EFadeMode::None)
	{
		/* Fade */

		FadeRemainingTime -= GetWorld()->DeltaRealTimeSeconds;

		float Ratio = FadeRemainingTime / FadeDuration;
		if (FadeDuration == 0)
			Ratio = 0.0f;
		Ratio = FMath::Clamp(Ratio, 0.0f, 1.0f);
		
		float Alpha = 0.0f;
		ESlateVisibility JobCompleteVisibility = ESlateVisibility::Collapsed;
		switch (FadeMode)
		{
			case UUWFade::EFadeMode::In:
				Alpha = 1.0f - Ratio;
				JobCompleteVisibility = ESlateVisibility::Visible;
				break;
			case UUWFade::EFadeMode::Out:
				Alpha = Ratio;
				JobCompleteVisibility = ESlateVisibility::Collapsed;
				break;
		}

		FLinearColor Color = Image->ColorAndOpacity;
		Color.A = Alpha;
		Image->SetColorAndOpacity(Color);

		/* Wait after job */

		if (Ratio == 0.0f)
		{
			if (ShouldWait)
			{
				WaitRemainingTime -= GetWorld()->DeltaRealTimeSeconds;
				
				if (WaitRemainingTime <= 0.0f)
				{
					WaitRemainingTime = 0.0f;
					ShouldWait = false;
				}
			}

			if (!ShouldWait)
			{
				if (FadeMode == EFadeMode::In && ShouldAutoFade)
				{
					OnFadeEnded(EFadeMode::In);
					ShouldAutoFade = false;
					FadeOut(AutoFadeOutDuration);
				}
				else
				{
					OnFadeEnded(FadeMode);
					ResetVariables();
					Image->SetVisibility(JobCompleteVisibility);
				}
			}
		}
	}
}

void UUWFade::OnFadeEnded(EFadeMode PrevMode)
{
	switch (PrevMode)
	{
		case UUWFade::EFadeMode::In:
			OnFadeInEnded.Broadcast();
			break;
		case UUWFade::EFadeMode::Out:
			OnFadeOutEnded.Broadcast();
			break;
	}
}

void UUWFade::ResetVariables()
{
	FadeDuration = 0;
	FadeRemainingTime = 0;
	FadeMode = EFadeMode::None;

	ShouldWait = false;
	WaitRemainingTime = 0;

	AutoFadeOutDuration = 0;
	ShouldAutoFade = false;
}

void UUWFade::SetupFadeVariables(float Duration, float Wait)
{
	FadeDuration = Duration;
	FadeRemainingTime = Duration;

	ShouldWait = Wait > 0;
	if (ShouldWait)
	{
		WaitRemainingTime = Wait;
	}
}

void UUWFade::FadeIn_Immediate()
{
	FLinearColor Color = Image->ColorAndOpacity;
	Color.A = 1.0f;
	Image->SetColorAndOpacity(Color);
	Image->SetVisibility(ESlateVisibility::Visible);

	ResetVariables();
}

void UUWFade::FadeOut_Immediate()
{
	FLinearColor Color = Image->ColorAndOpacity;
	Color.A = 0.0f;
	Image->SetColorAndOpacity(Color);
	Image->SetVisibility(ESlateVisibility::Collapsed);

	ResetVariables();
}

void UUWFade::FadeIn(float Duration, float Wait)
{
	FadeMode = EFadeMode::In;
	Image->SetVisibility(ESlateVisibility::Visible);

	SetupFadeVariables(Duration, Wait);
}

void UUWFade::FadeOut(float Duration, float Wait)
{
	FadeMode = EFadeMode::Out;
	Image->SetVisibility(ESlateVisibility::Visible);

	SetupFadeVariables(Duration, Wait);
}

void UUWFade::Fade(float FadeInDuration, float Wait, float FadeOutDuration)
{
	FadeIn(FadeInDuration, Wait);
	ShouldAutoFade = true;
	AutoFadeOutDuration = FadeOutDuration;
}

bool UUWFade::IsWorking() const
{
	return FadeMode != EFadeMode::None;
}
