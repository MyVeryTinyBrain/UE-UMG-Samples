// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "UWSkillDescription.generated.h"

/**
 * 
 */
UCLASS()
class USERINTERFACE_API UUWSkillDescription : public UUserWidget
{
	GENERATED_BODY()

	UPROPERTY(meta = (BindWidget))
	class UImage* Img_Skill;
	
	UPROPERTY(meta = (BindWidget))
	class UTextBlock* Txt_SkillName;

	UPROPERTY(meta = (BindWidget))
	class UTextBlock* Txt_SkillDescription;

private:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, BlueprintGetter = "GetSkillTexture", BlueprintSetter = "SetSkillTexture", meta = (AllowPrivateAccess))
	TObjectPtr<class UTexture2D> SkillTexture;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, BlueprintGetter = "GetSkillName", BlueprintSetter = "SetSkillName", meta = (AllowPrivateAccess))
	FString SkillName = TEXT("SKILL NAME");

	UPROPERTY(EditAnywhere, BlueprintReadWrite, BlueprintGetter = "GetSkillDescription", BlueprintSetter = "SetSkillDescription", meta = (AllowPrivateAccess = true, Multiline = true))
	FString SkillDescription = TEXT("SKILL DESCRIPTION");

protected:
	virtual void NativePreConstruct() override;

private:
	void Update();

public:
	UFUNCTION(BlueprintCallable)
	class UTexture2D* GetSkillTexture() const { return SkillTexture; }

	UFUNCTION(BlueprintCallable)
	void SetSkillTexture(class UTexture2D* InSkillTexture);

	UFUNCTION(BlueprintCallable)
	const FString& GetSkillName() const { return SkillName; }

	UFUNCTION(BlueprintCallable)
	void SetSkillName(const FString& InSkillName);

	UFUNCTION(BlueprintCallable)
	const FString& GetSkillDescription() const { return SkillDescription; }

	UFUNCTION(BlueprintCallable)
	void SetSkillDescription(const FString& InSkillDescription);
};
