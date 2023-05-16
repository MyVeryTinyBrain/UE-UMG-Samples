// Fill out your copyright notice in the Description page of Project Settings.


#include "UWHeroButton.h"
#include <Components/Image.h>
#include <Components/TextBlock.h>

void UUWHeroButton::NativeConstruct()
{
	Super::NativeConstruct();

	Button->OnClicked.AddDynamic(this, &UUWHeroButton::Internal_OnClicked);
	Button->OnPressed.AddDynamic(this, &UUWHeroButton::Internal_OnPressed);
	Button->OnReleased.AddDynamic(this, &UUWHeroButton::Internal_OnReleased);
	Button->OnHovered.AddDynamic(this, &UUWHeroButton::Internal_OnHovered);
	Button->OnUnhovered.AddDynamic(this, &UUWHeroButton::Internal_OnUnhovered);
}

void UUWHeroButton::NativePreConstruct()
{
	Super::NativePreConstruct();

	Update();
}

void UUWHeroButton::Internal_OnClicked()
{
	OnClicked.Broadcast(this);
}

void UUWHeroButton::Internal_OnPressed()
{
	OnPressed.Broadcast(this);
}

void UUWHeroButton::Internal_OnReleased()
{
	OnReleased.Broadcast(this);
}

void UUWHeroButton::Internal_OnHovered()
{
	OnHovered.Broadcast(this);
}

void UUWHeroButton::Internal_OnUnhovered()
{
	OnUnhovered.Broadcast(this);
}

void UUWHeroButton::Update()
{
	Img_Hero->SetBrushFromTexture(HeroDesc.DefaultHeroTexture ? HeroDesc.DefaultHeroTexture : DefaultHeroTexture);
	Txt_HeroName->SetText(FText::FromString(HeroDesc.HeroName));
}

void UUWHeroButton::SetDefaultHeroTexture(UTexture2D* InDefaultHeroTexture)
{
	DefaultHeroTexture = InDefaultHeroTexture;
	Update();
}

void UUWHeroButton::SetHeroDesc(FHeroDesc InHeroDesc)
{
	HeroDesc = InHeroDesc;
	Update();
}
