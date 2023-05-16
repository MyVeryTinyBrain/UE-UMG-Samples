// Fill out your copyright notice in the Description page of Project Settings.


#include "UWUserName.h"
#include <Components/TextBlock.h>

void UUWUserName::NativePreConstruct()
{
	Super::NativeConstruct();
	Update();
}

void UUWUserName::Update()
{
	Txt_UserName->SetText(UserName);
}

void UUWUserName::SetUserName(const FText& InUserName)
{
	UserName = InUserName;
	Update();
}

void UUWUserName::SetUserName(const FString& InUserName)
{
	UserName = FText::FromString(InUserName);
	Update();
}
