// Fill out your copyright notice in the Description page of Project Settings.


#include "UWInventoryButton.h"
#include <Components/Image.h>
#include <Components/Button.h>

void UUWInventoryButton::NativePreConstruct()
{
	Super::NativePreConstruct();

	UpdateIcon();
	UpdateButton();
}

void UUWInventoryButton::NativeConstruct()
{
	Super::NativeConstruct();

	Button->OnClicked.AddDynamic(this, &UUWInventoryButton::Internal_OnInventoryButtonClicked);
	Button->OnPressed.AddDynamic(this, &UUWInventoryButton::Internal_OnInventoryButtonPressed);
	Button->OnReleased.AddDynamic(this, &UUWInventoryButton::Internal_OnInventoryButtonReleased);
	Button->OnHovered.AddDynamic(this, &UUWInventoryButton::Internal_OnInventoryButtonHover);
	Button->OnUnhovered.AddDynamic(this, &UUWInventoryButton::Internal_OnInventoryButtonUnhover);
}

void UUWInventoryButton::Internal_OnInventoryButtonClicked()
{
	OnInventoryButtonClicked.Broadcast();
}

void UUWInventoryButton::Internal_OnInventoryButtonPressed()
{
	OnInventoryButtonPressed.Broadcast();
}

void UUWInventoryButton::Internal_OnInventoryButtonReleased()
{
	OnInventoryButtonReleased.Broadcast();
}

void UUWInventoryButton::Internal_OnInventoryButtonHover()
{
	OnInventoryButtonHover.Broadcast();
}

void UUWInventoryButton::Internal_OnInventoryButtonUnhover()
{
	OnInventoryButtonUnhover.Broadcast();
}

void UUWInventoryButton::UpdateIcon()
{
	Img_Icon->SetBrushFromTexture(IconTexture);
}

void UUWInventoryButton::UpdateButton()
{
	Button->SetIsEnabled(bButtonEnable);
}

void UUWInventoryButton::SetButtonEnable(bool InButtonEnable)
{
	bButtonEnable = InButtonEnable;
	UpdateButton();
}
