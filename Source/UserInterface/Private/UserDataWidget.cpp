// Fill out your copyright notice in the Description page of Project Settings.


#include "UserDataWidget.h"

void UUserDataWidget::Setup(UUserData* InUserData)
{
	UserData = InUserData;
	OnUserDataWidgetSetup();
	NativeOnUserDataWidgetSetup();
}
