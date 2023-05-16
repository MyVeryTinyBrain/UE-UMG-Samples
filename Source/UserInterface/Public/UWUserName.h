// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "UWUserName.generated.h"

/**
 * 
 */
UCLASS()
class USERINTERFACE_API UUWUserName : public UUserWidget
{
	GENERATED_BODY()
	
	UPROPERTY(meta = (BindWidget))
	class UTextBlock* Txt_UserName;

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, BlueprintGetter = "GetUserName", BlueprintSetter = "SetUserName", meta = (AllowPrivateAccess))
	FText UserName = FText::FromString(TEXT("UserName"));

protected:
	virtual void NativePreConstruct() override;

private:
	void Update();

public:
	UFUNCTION(BlueprintCallable)
	const FText& GetUserName() const { return UserName; }
	
	UFUNCTION(BlueprintCallable)
	void SetUserName(const FText& InUserName);
	void SetUserName(const FString& InUserName);
};
