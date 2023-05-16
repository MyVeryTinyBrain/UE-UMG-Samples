// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "UWImage.generated.h"

/**
 * 
 */
UCLASS()
class USERINTERFACE_API UUWImage : public UUserWidget
{
	GENERATED_BODY()
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (BindWidget = true, AllowPrivateAccess = true))
	class UImage* Image;

public:
	UFUNCTION(BlueprintCallable)
	class UImage* GetImage() const { return Image; }
};
