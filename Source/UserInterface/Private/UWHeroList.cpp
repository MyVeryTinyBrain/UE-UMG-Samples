// Fill out your copyright notice in the Description page of Project Settings.


#include "UWHeroList.h"
#include "UWHeroButton.h"
#include <Components/WrapBox.h>
#include <Components/Image.h>

void UUWHeroList::NativeConstruct()
{
	Super::NativeConstruct();
}

void UUWHeroList::NativePreConstruct()
{
	Super::NativePreConstruct();

	UpdateHeroList();
	UpdateVisual();
}

void UUWHeroList::OnHeroButtonClicked(UUWHeroButton* HeroButton)
{
	OnHeroButtonClickedA.Broadcast(HeroButton->GetHeroDesc());
	OnHeroButtonClickedB.Broadcast(HeroButton);
}

void UUWHeroList::UpdateHeroList()
{
	WB_WrapBox->ClearChildren();
	for (const FHeroDesc& desc : HeroDescriptions)
	{
		UUWHeroButton* button = CreateWidget<UUWHeroButton>(WB_WrapBox, ElementTemplate);

		button->SetHeroDesc(desc);

		button->OnClicked.AddDynamic(this, &UUWHeroList::OnHeroButtonClicked);

		WB_WrapBox->AddChild(button);
	}
}

void UUWHeroList::UpdateVisual()
{
	Img_BG->SetColorAndOpacity(BackgroundColor);
}

void UUWHeroList::SetHeroDescriptions(const TArray<FHeroDesc>& InHeroDescriptions)
{
	HeroDescriptions = InHeroDescriptions;
	UpdateHeroList();
}

void UUWHeroList::SetBackgroundColor(const FLinearColor& InBackgroundColor)
{
	BackgroundColor = InBackgroundColor;
	UpdateVisual();
}
