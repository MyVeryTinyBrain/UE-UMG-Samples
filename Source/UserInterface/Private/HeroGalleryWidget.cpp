// Fill out your copyright notice in the Description page of Project Settings.


#include "HeroGalleryWidget.h"

void UHeroGalleryWidget::Setup(UUserData* InUserData, const FHeroGalleryWidgetSubData& InSubData)
{
	UserData = InUserData;
	SubData = InSubData;
	OnHeroGalleryWidgetSetup();
	NativeOnHeroGalleryWidgetSetup();
}
