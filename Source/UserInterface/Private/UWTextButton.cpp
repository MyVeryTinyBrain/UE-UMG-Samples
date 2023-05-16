// Fill out your copyright notice in the Description page of Project Settings.


#include "UWTextButton.h"
#include <Components/TextBlock.h>
#include <Components/Button.h>

void UUWTextButton::NativePreConstruct()
{
	Super::NativePreConstruct();

	UpdateTitle();
	UpdateFont();
}

void UUWTextButton::NativeConstruct()
{
	Super::NativeConstruct();

	Button->OnClicked.AddDynamic(this, &UUWTextButton::Internal_OnButtonClicked);
	Button->OnPressed.AddDynamic(this, &UUWTextButton::Internal_OnButtonPressed);
	Button->OnReleased.AddDynamic(this, &UUWTextButton::Internal_OnButtonReleased);
	Button->OnHovered.AddDynamic(this, &UUWTextButton::Internal_OnButtonHover);
	Button->OnUnhovered.AddDynamic(this, &UUWTextButton::Internal_OnButtonUnhover);

	bIsHovered = false;
	HoveredFontScaleRatio = 0.0f;
}

void UUWTextButton::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);
	
	if (Txt_Title)
	{
		float Adder = InDeltaTime;
		if (HoveredFontScaleChangeDuration > 0.0f)
		{
			Adder /= HoveredFontScaleChangeDuration;
		}

		if (!bIsHovered)
		{
			Adder *= -1.0f;
		}
		HoveredFontScaleRatio += Adder;
		HoveredFontScaleRatio = FMath::Clamp(HoveredFontScaleRatio, 0.0f, 1.0f);
		float FontScale = FMath::Lerp(1.0f, HoveredFontScale, HoveredFontScaleRatio);

		Txt_Title->SetRenderScale(FVector2D::One() * FontScale);
	}
}

void UUWTextButton::Internal_OnButtonClicked()
{
	OnTextButtonClicked.Broadcast(this);
}

void UUWTextButton::Internal_OnButtonPressed()
{
	OnTextButtonPressed.Broadcast(this);
}

void UUWTextButton::Internal_OnButtonReleased()
{
	OnTextButtonReleased.Broadcast(this);
}

void UUWTextButton::Internal_OnButtonHover()
{
	OnTextButtonHover.Broadcast(this);

	bIsHovered = true;
}

void UUWTextButton::Internal_OnButtonUnhover()
{
	OnTextButtonUnhover.Broadcast(this);

	bIsHovered = false;
}

void UUWTextButton::UpdateTitle()
{
	Txt_Title->SetText(FText::FromString(Title));
}

void UUWTextButton::UpdateFont()
{
	Txt_Title->SetFont(Font);
}

void UUWTextButton::SetTitle(const FString& InTitle)
{
	Title = InTitle;
	UpdateTitle();
}

void UUWTextButton::SetFont(const FSlateFontInfo& InFont)
{
	Font = InFont;
	UpdateFont();
}
