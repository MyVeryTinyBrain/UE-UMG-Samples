// Fill out your copyright notice in the Description page of Project Settings.


#include "UWSkillDescription.h"
#include <Components/Image.h>
#include <Components/TextBlock.h>

void UUWSkillDescription::NativePreConstruct()
{
	Super::NativePreConstruct();

	Update();
}

void UUWSkillDescription::Update()
{
	Img_Skill->SetBrushFromTexture(SkillTexture.Get());
	Txt_SkillName->SetText(FText::FromString(SkillName));
	Txt_SkillDescription->SetText(FText::FromString(SkillDescription));
}

void UUWSkillDescription::SetSkillTexture(UTexture2D* InSkillTexture)
{
	SkillTexture = InSkillTexture;
	Update();
}

void UUWSkillDescription::SetSkillName(const FString& InSkillName)
{
	SkillName = InSkillName;
	Update();
}

void UUWSkillDescription::SetSkillDescription(const FString& InSkillDescription)
{
	SkillDescription = InSkillDescription;
	Update();
}
