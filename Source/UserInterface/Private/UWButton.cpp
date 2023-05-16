// Fill out your copyright notice in the Description page of Project Settings.


#include "UWButton.h"
#include <Components/TextBlock.h>

void UUWButton::NativeConstruct()
{
	Super::NativeConstruct();

	Button->OnClicked.AddDynamic(this, &UUWButton::Internal_OnClicked);
	Button->OnPressed.AddDynamic(this, &UUWButton::Internal_OnPressed);
	Button->OnReleased.AddDynamic(this, &UUWButton::Internal_OnReleased);
	Button->OnHovered.AddDynamic(this, &UUWButton::Internal_OnHovered);
	Button->OnUnhovered.AddDynamic(this, &UUWButton::Internal_OnUnhovered);
}

void UUWButton::NativePreConstruct()
{
	Super::NativePreConstruct();
	Update();
}

void UUWButton::Internal_OnClicked()
{
	OnClicked.Broadcast();
}

void UUWButton::Internal_OnPressed()
{
	OnPressed.Broadcast();
}

void UUWButton::Internal_OnReleased()
{
	OnReleased.Broadcast();
}

void UUWButton::Internal_OnHovered()
{
	OnHovered.Broadcast();
}

void UUWButton::Internal_OnUnhovered()
{
	OnUnhovered.Broadcast();
}

void UUWButton::Update()
{
	SetText(Text);
	SetFontColor(FontColor);
	SetFontSize(FontSize);
	SetBackgroundColor(BackgroundColor);
	SetOutlineColor(OutlineColor);
	SetNormalColor(NormalColor);
	SetHoverColor(HoverColor);
	SetPressedColor(PressedColor);
	SetOutlineWidth(OutlineWidth);
	SetUseTransparentOutline(UseTransparentOutline);
	SetButtonEnable(bButtonEnable);
}

void UUWButton::UpdateFontStyle()
{
	FButtonStyle style = Button->WidgetStyle;
	FSlateBrushOutlineSettings outlineSettings = style.Normal.OutlineSettings;
	outlineSettings.Color = OutlineColor;
	outlineSettings.Width = OutlineWidth;
	outlineSettings.bUseBrushTransparency = UseTransparentOutline;
	style.Normal.OutlineSettings = outlineSettings;
	style.Hovered.OutlineSettings = outlineSettings;
	style.Pressed.OutlineSettings = outlineSettings;
	style.Normal.TintColor = NormalColor;
	style.Hovered.TintColor = HoverColor;
	style.Pressed.TintColor = PressedColor;
	Button->SetStyle(style);
}

void UUWButton::SetText(const FText& InText)
{
	Text = InText;
	TextBlock->SetText(Text);
}

void UUWButton::SetFontColor(const FLinearColor& InColor)
{
	FontColor = InColor;
	TextBlock->SetColorAndOpacity(FontColor);
}

void UUWButton::SetFontSize(int32 InSize)
{
	FontSize = InSize;
	FSlateFontInfo font = TextBlock->GetFont();
	font.Size = FontSize;
	TextBlock->SetFont(font);
}

void UUWButton::SetBackgroundColor(const FLinearColor& InColor)
{
	BackgroundColor = InColor;
	Button->SetBackgroundColor(BackgroundColor);
}

void UUWButton::SetOutlineColor(const FLinearColor& InColor)
{
	OutlineColor = InColor;
	UpdateFontStyle();
}

void UUWButton::SetNormalColor(const FLinearColor& InColor)
{
	NormalColor = InColor;
	UpdateFontStyle();
}

void UUWButton::SetHoverColor(const FLinearColor& InColor)
{
	HoverColor = InColor;
	UpdateFontStyle();
}

void UUWButton::SetPressedColor(const FLinearColor& InColor)
{
	PressedColor = InColor;
	UpdateFontStyle();
}

void UUWButton::SetOutlineWidth(float InWidth)
{
	OutlineWidth = InWidth;
	UpdateFontStyle();
}

void UUWButton::SetUseTransparentOutline(bool InUse)
{
	UseTransparentOutline = InUse;
	UpdateFontStyle();
}

void UUWButton::SetButtonEnable(bool InEnable)
{
	bButtonEnable = InEnable;
	Button->SetIsEnabled(bButtonEnable);
}
