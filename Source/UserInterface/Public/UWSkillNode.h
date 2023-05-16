// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include <Components/Button.h>
#include <SkillData.h>
#include "Blueprint/UserWidget.h"
#include "UWSkillNode.generated.h"

class UUWSkillNode;
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnSkillNodeClickedEvent, UUWSkillNode*, SkillNode, bool, IsInteractible);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnSkillNodePressedEvent, UUWSkillNode*, SkillNode, bool, IsInteractible);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnSkillNodeReleasedEvent, UUWSkillNode*, SkillNode, bool, IsInteractible);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnSkillNodeHoverEvent, UUWSkillNode*, SkillNode, bool, IsInteractible);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnSkillNodeClickingEvent, UUWSkillNode*, SkillNode, float, Ratio);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnSkillNodeInteractEvent, UUWSkillNode*, SkillNode);

/**
 * 
 */
UCLASS()
class USERINTERFACE_API UUWSkillNode : public UUserWidget
{
	GENERATED_BODY()

	UPROPERTY(meta = (BindWidget))
	class UButton* Button;

	UPROPERTY(meta = (BindWidget))
	class UImage* Img_Out;

	UPROPERTY(meta = (BindWidget))
	class UImage* Img_In;

	UPROPERTY(meta = (BindWidget))
	class UImage* Img_Icon;

	UPROPERTY(meta = (BindWidget))
	class UNiagaraSystemWidget* NSW_UnlockedEffect;

	UPROPERTY(meta = (BindWidget))
	class UNiagaraSystemWidget* NSW_UnlockEffect;

private:
	// Must setup this variables
	UPROPERTY(EditAnywhere, BlueprintReadWrite, BlueprintGetter = "GetSkillDataTable", BlueprintSetter = "SetSkillDataTable", meta = (AllowPrivateAccess))
	TObjectPtr<class UDataTable> SkillDataTable = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, BlueprintGetter = "GetLockedColor", BlueprintSetter = "SetLockedColor", meta = (AllowPrivateAccess))
	FLinearColor LockedColor = FLinearColor::Black;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, BlueprintGetter = "GetUnlockedColor", BlueprintSetter = "SetUnlockedColor", meta = (AllowPrivateAccess))
	FLinearColor UnlockedColor = FLinearColor::White;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, BlueprintGetter = "GetNormalForeground", BlueprintSetter = "SetNormalForeground", meta = (AllowPrivateAccess))
	FLinearColor NormalForeground = FLinearColor::White;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, BlueprintGetter = "GetHoverForeground", BlueprintSetter = "SetHoverForeground", meta = (AllowPrivateAccess))
	FLinearColor HoverForeground = FLinearColor(1, 1, 1, 0.7f);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, BlueprintGetter = "GetPressedForeground", BlueprintSetter = "SetPressedForeground", meta = (AllowPrivateAccess))
	FLinearColor PressedForeground = FLinearColor(1, 1, 1, 0.4f);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, BlueprintGetter = "GetUnlockedNormalForeground", BlueprintSetter = "SetUnlockedNormalForeground", meta = (AllowPrivateAccess))
	FLinearColor UnlockedNormalForeground = FLinearColor::White;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, BlueprintGetter = "GetUnlockedHoverForeground", BlueprintSetter = "SetUnlockedHoverForeground", meta = (AllowPrivateAccess))
	FLinearColor UnlockedHoverForeground = FLinearColor::White;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, BlueprintGetter = "GetUnlockedPressedForeground", BlueprintSetter = "SetUnlockedPressedForeground", meta = (AllowPrivateAccess))
	FLinearColor UnlockedPressedForeground = FLinearColor::White;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, BlueprintGetter = "GetRowName", BlueprintSetter = "SetRowName", meta = (AllowPrivateAccess))
	FName RowName;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, BlueprintGetter = "GetSkillData", meta = (AllowPrivateAccess))
	FSkillData SkillData;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, BlueprintGetter = "HasSkillData", meta = (AllowPrivateAccess))
	bool bHasSkillData = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, BlueprintGetter = "GetDefaultSkillTexture", BlueprintSetter = "SetDefaultSkillTexture", meta = (AllowPrivateAccess))
	TObjectPtr<class UTexture2D> DefaultSkillTexture;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, BlueprintGetter = "GetParentNode", BlueprintSetter = "SetParentNode", meta = (AllowPrivateAccess))
	TObjectPtr<UUWSkillNode> ParentNode;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, BlueprintGetter = "IsUnlocked", BlueprintSetter = "SetUnlocked", meta = (AllowPrivateAccess))
	bool bUnlocked = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, BlueprintGetter = "GetInteractPressTime", BlueprintSetter = "SetInteractPressTime", meta = (AllowPrivateAccess))
	float InteractPressTime = 0.5f;

	bool bIsPressing = false;
	float CurrentPressAccumulation = 0;

public:
	/** Called when the button is clicked */
	UPROPERTY(BlueprintAssignable, Category = "Button|Event")
	FOnSkillNodeClickedEvent OnClicked;

	/** Called when the button is pressed */
	UPROPERTY(BlueprintAssignable, Category = "Button|Event")
	FOnSkillNodePressedEvent OnPressed;

	/** Called when the button is released */
	UPROPERTY(BlueprintAssignable, Category = "Button|Event")
	FOnSkillNodeReleasedEvent OnReleased;

	UPROPERTY(BlueprintAssignable, Category = "Button|Event")
	FOnSkillNodeHoverEvent OnHovered;

	UPROPERTY(BlueprintAssignable, Category = "Button|Event")
	FOnSkillNodeHoverEvent OnUnhovered;

	UPROPERTY(BlueprintAssignable, Category = "Button|Event")
	FOnSkillNodeClickingEvent OnPressing;

	UPROPERTY(BlueprintAssignable, Category = "Button|Event")
	FOnSkillNodeInteractEvent OnInteract;

protected:
	virtual void NativeConstruct() override;
	virtual void NativePreConstruct() override;
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;

	UFUNCTION()
	virtual void Internal_OnClicked();

	UFUNCTION()
	virtual void Internal_OnPressed();

	UFUNCTION()
	virtual void Internal_OnReleased();

	UFUNCTION()
	virtual void Internal_OnHovered();

	UFUNCTION()
	virtual void Internal_OnUnhovered();

	UFUNCTION()
	virtual void Internal_OnPressing();

	UFUNCTION()
	virtual void Internal_OnInteract();

private:
	void Update();

public:
	UFUNCTION(BlueprintCallable)
	void ResetPressingState();

	UFUNCTION(BlueprintCallable)
	float GetRatio() const;

	UFUNCTION(BlueprintCallable)
	bool IsInteractibleState() const;

	UFUNCTION(BlueprintCallable)
	bool HasSkillData() const { return bHasSkillData; }

	UFUNCTION(BlueprintCallable)
	const FSkillData& GetSkillData() const { return SkillData; }

	UFUNCTION(BlueprintCallable)
	class UDataTable* GetSkillDataTable() const { return SkillDataTable; }

	UFUNCTION(BlueprintCallable)
	void SetSkillDataTable(class UDataTable* InSkillDataTable);

	UFUNCTION(BlueprintCallable)
	const FLinearColor& GetLockedColor() const { return LockedColor; }

	UFUNCTION(BlueprintCallable)
	void SetLockedColor(const FLinearColor& InLockedColor);

	UFUNCTION(BlueprintCallable)
	const FLinearColor& GetUnlockedColor() const { return UnlockedColor; }

	UFUNCTION(BlueprintCallable)
	void SetUnlockedColor(const FLinearColor& InUnlockedColor);

	UFUNCTION(BlueprintCallable)
	const FLinearColor& GetNormalForeground() const { return NormalForeground; }

	UFUNCTION(BlueprintCallable)
	void SetNormalForeground(const FLinearColor& InNormalForeground);

	UFUNCTION(BlueprintCallable)
	const FLinearColor& GetHoverForeground() const { return HoverForeground; }

	UFUNCTION(BlueprintCallable)
	void SetHoverForeground(const FLinearColor& InHoverForeground);

	UFUNCTION(BlueprintCallable)
	const FLinearColor& GetPressedForeground() const { return PressedForeground; }

	UFUNCTION(BlueprintCallable)
	void SetPressedForeground(const FLinearColor& InPressedForeground);

	UFUNCTION(BlueprintCallable)
	const FLinearColor& GetUnlockedNormalForeground() const { return UnlockedNormalForeground; }

	UFUNCTION(BlueprintCallable)
	void SetUnlockedNormalForeground(const FLinearColor& InUnlockedNormalForeground);

	UFUNCTION(BlueprintCallable)
	const FLinearColor& GetUnlockedHoverForeground() const { return UnlockedHoverForeground; }

	UFUNCTION(BlueprintCallable)
	void SetUnlockedHoverForeground(const FLinearColor& InUnlockedHoverForeground);

	UFUNCTION(BlueprintCallable)
	const FLinearColor& GetUnlockedPressedForeground() const { return UnlockedPressedForeground; }

	UFUNCTION(BlueprintCallable)
	void SetUnlockedPressedForeground(const FLinearColor& InUnlockedPressedForeground);

	UFUNCTION(BlueprintCallable)
	const FName& GetRowName() const { return RowName; }

	UFUNCTION(BlueprintCallable)
	void SetRowName(const FName& InRowName);

	UFUNCTION(BlueprintCallable)
	class UTexture2D* GetDefaultSkillTexture() const { return DefaultSkillTexture; }

	UFUNCTION(BlueprintCallable)
	void SetDefaultSkillTexture(class UTexture2D* InDefaultSkillTexture);

	UFUNCTION(BlueprintCallable)
	class UUWSkillNode* GetParentNode() const { return ParentNode; }

	UFUNCTION(BlueprintCallable)
	void SetParentNode(class UUWSkillNode* InParentNode);

	UFUNCTION(BlueprintCallable)
	bool IsUnlocked() const { return bUnlocked; }

	UFUNCTION(BlueprintCallable)
	void SetUnlocked(bool InUnlocked);

	UFUNCTION(BlueprintCallable)
	float GetInteractPressTime() const { return InteractPressTime; }

	UFUNCTION(BlueprintCallable)
	void SetInteractPressTime(float InInteractPressTime);
};
