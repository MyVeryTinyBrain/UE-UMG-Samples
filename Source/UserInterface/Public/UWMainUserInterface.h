// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "UWMainUserInterface.generated.h"

/**
 * 
 */
UCLASS()
class USERINTERFACE_API UUWMainUserInterface : public UUserWidget
{
	GENERATED_BODY()

	UPROPERTY(meta = (BindWidget))
	class UCanvasPanel* Canv_Root;

	UPROPERTY(meta = (BindWidget))
	class UCanvasPanel* Canv_Main;

	UPROPERTY(meta = (BindWidget))
	class UUWTextButton* WBTB_Loot;

	UPROPERTY(meta = (BindWidget))
	class UUWTextButton* WBTB_SkillTree;

	UPROPERTY(meta = (BindWidget))
	class UUWTextButton* WBTB_Item;

	UPROPERTY(meta = (BindWidget))
	class UUWTextButton* WBTB_Exit;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess))
	TSubclassOf<class UUWMainGlobalWidgets> MainGlobalWidgetsTemplate;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess))
	TSubclassOf<class UUserDataWidget> LootWidgetTemplate;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess))
	TSubclassOf<class UUserDataWidget> SkillTreeWidgetTemplate;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess))
	TSubclassOf<class UUserDataWidget> ItemWidgetTemplate;

	UPROPERTY()
	TObjectPtr<class UUWMainGlobalWidgets> MainGlobalWidgets;

	UPROPERTY()
	TObjectPtr<class UUserDataWidget> CurrentUserDataWidget;

	UPROPERTY()
	TObjectPtr<UWidget> CurrentWidget = nullptr;

	UPROPERTY()
	TObjectPtr<UWidget> NextWidget = nullptr;

private:
	UPROPERTY()
	TObjectPtr<class UUserData> UserData = nullptr;

protected:
	virtual void NativeConstruct() override;

	UFUNCTION()
	virtual void OnTextButtonClicked(class UUWTextButton* InTextButton);

	UFUNCTION()
	virtual void OnEscapeButtonClicked();

	UFUNCTION()
	void OnFadeInEnded();

private:
	class UUserDataWidget* SetupUserDataWidget(TSubclassOf<class UUserDataWidget> InUserDataWidget);

public:
	UFUNCTION(BlueprintCallable)
	void InitalizeMainUserInterface(class UUserData* InUserData);
};
