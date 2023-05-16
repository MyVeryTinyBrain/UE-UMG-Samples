// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "UWUserCash.generated.h"

/**
 * 
 */
UCLASS()
class USERINTERFACE_API UUWUserCash : public UUserWidget
{
	GENERATED_BODY()

	UPROPERTY(meta = (BindWidget))
	class UTextBlock* Txt_CashUnit;

	UPROPERTY(meta = (BindWidget))
	class UTextBlock* Txt_Cash;

private:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, BlueprintGetter = "GetCash", BlueprintSetter = "SetCash", meta = (AllowPrivateAccess))
	int32 Cash = 999999;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, BlueprintGetter = "GetFontSize", BlueprintSetter = "SetFontSize", meta = (AllowPrivateAccess))
	int32 FontSize = 30;

protected:
	virtual void NativePreConstruct() override;

private:
	void Update();

public:
	UFUNCTION(BlueprintCallable)
	int32 GetCash() const { return Cash; }

	UFUNCTION(BlueprintCallable)
	void SetCash(int32 InCash);

	UFUNCTION(BlueprintCallable)
	int32 GetFontSize() const { return FontSize; }

	UFUNCTION(BlueprintCallable)
	void SetFontSize(int32 InFontSize);
};
