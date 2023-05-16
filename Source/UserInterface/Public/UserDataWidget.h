// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include <Engine/DataTable.h>
#include <HeroData.h>
#include <UserData.h>
#include "Blueprint/UserWidget.h"
#include "UserDataWidget.generated.h"

UCLASS()
class USERINTERFACE_API UUserDataWidget : public UUserWidget
{
	GENERATED_BODY()

protected:
	UPROPERTY()
	TObjectPtr<UUserData> UserData = nullptr;

public:
	void Setup(class UUserData* InUserData);

protected:
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void OnUserDataWidgetSetup(); // Blueprint Only
	virtual void OnUserDataWidgetSetup_Implementation() {}; // C++ Only
	
	virtual void NativeOnUserDataWidgetSetup() {}
};
