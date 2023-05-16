// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "UWFade.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnFadeEndedEvent);

/**
 * 
 */
UCLASS()
class USERINTERFACE_API UUWFade : public UUserWidget
{
	GENERATED_BODY()

	UPROPERTY(meta = (BindWidget))
	class UImage* Image;

	float FadeDuration;
	float FadeRemainingTime;
	enum class EFadeMode { None, In, Out } FadeMode = EFadeMode::None;

	float WaitRemainingTime;
	bool ShouldWait = false;

	float AutoFadeOutDuration;
	bool ShouldAutoFade = false;

public:
	UPROPERTY(BlueprintAssignable, Category = "Fade|Event")
	FOnFadeEndedEvent OnFadeInEnded;

	UPROPERTY(BlueprintAssignable, Category = "Fade|Event")
	FOnFadeEndedEvent OnFadeOutEnded;

protected:
	virtual void NativeConstruct() override;
	virtual void NativePreConstruct() override;
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;
	virtual void OnFadeEnded(EFadeMode PrevMode);

private:
	void ResetVariables();
	void SetupFadeVariables(float Duration, float Wait);
	
public:
	UFUNCTION(BlueprintCallable)
	void FadeIn_Immediate();

	UFUNCTION(BlueprintCallable)
	void FadeOut_Immediate();

	UFUNCTION(BlueprintCallable)
	void FadeIn(float Duration, float Wait = 0);

	UFUNCTION(BlueprintCallable)
	void FadeOut(float Duration, float Wait = 0);

	UFUNCTION(BlueprintCallable)
	void Fade(float FadeInDuration, float Wait, float FadeOutDuration);

	UFUNCTION(BlueprintCallable)
	bool IsWorking() const;
};
