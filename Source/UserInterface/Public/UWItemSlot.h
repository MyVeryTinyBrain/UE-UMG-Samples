// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include <ItemData.h>
#include <Components/Button.h>
#include "Blueprint/UserWidget.h"
#include "UWItemSlot.generated.h"

class UUWItemSlot;
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnItemSlotClickedEvent, UUWItemSlot*, ItemSlot);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnItemSlotPressedEvent, UUWItemSlot*, ItemSlot);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnItemSlotReleasedEvent, UUWItemSlot*, ItemSlot);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnItemSlotHoverEvent, UUWItemSlot*, ItemSlot);

/**
 * 
 */
UCLASS()
class USERINTERFACE_API UUWItemSlot : public UUserWidget
{
	GENERATED_BODY()
	
	UPROPERTY(meta = (BindWidget))
	class UButton* Button;

	UPROPERTY(meta = (BindWidget))
	class UImage* Img_Select;

	UPROPERTY(meta = (BindWidget))
	class UImage* Img_Equip;

	UPROPERTY(meta = (BindWidget))
	class UTextBlock* Txt_ItemName;

	UPROPERTY(meta = (BindWidget))
	class UOverlay* Ov_NewIcon;

	UPROPERTY(meta = (BindWidget))
	class UImage* Img_NewBox;

	UPROPERTY(meta = (BindWidget))
	class UTextBlock* Txt_NewText;

	UPROPERTY(meta = (BindWidget))
	class UTextBlock* Txt_Cost;

	UPROPERTY(meta = (BindWidget))
	class UImage* Img_Lock;

	UPROPERTY(meta = (BindWidget))
	class UImage* Img_Unlock;

private:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, BlueprintGetter = "GetItemData", BlueprintSetter = "SetItemData", meta = (AllowPrivateAccess))
	FItemData ItemData;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, BlueprintGetter = "IsNewItem", BlueprintSetter = "SetIsNewItem", meta = (AllowPrivateAccess))
	bool bIsNewItem = true;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, BlueprintGetter = "IsLocked", BlueprintSetter = "SetIsLocked", meta = (AllowPrivateAccess))
	bool bIsLocked = true;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, BlueprintGetter = "IsSelected", BlueprintSetter = "SetIsSelected", meta = (AllowPrivateAccess))
	bool bIsSelected = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, BlueprintGetter = "IsEquipped", BlueprintSetter = "SetIsEquipped", meta = (AllowPrivateAccess))
	bool bIsEquipped = false;

public:
	/** Called when the button is clicked */
	UPROPERTY(BlueprintAssignable, Category = "Button|Event")
	FOnItemSlotClickedEvent OnClicked;

	/** Called when the button is pressed */
	UPROPERTY(BlueprintAssignable, Category = "Button|Event")
	FOnItemSlotPressedEvent OnPressed;

	/** Called when the button is released */
	UPROPERTY(BlueprintAssignable, Category = "Button|Event")
	FOnItemSlotReleasedEvent OnReleased;

	UPROPERTY(BlueprintAssignable, Category = "Button|Event")
	FOnItemSlotHoverEvent OnHovered;

	UPROPERTY(BlueprintAssignable, Category = "Button|Event")
	FOnItemSlotHoverEvent OnUnhovered;

protected:
	virtual void NativeConstruct() override;
	virtual void NativePreConstruct() override;

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
	
private:
	void Update();

public:
	UFUNCTION(BlueprintCallable)
	void SetSelectState(bool Value);

	UFUNCTION(BlueprintCallable)
	void SetEquipState(bool Value);

	UFUNCTION(BlueprintCallable)
	const FItemData& GetItemData() const { return ItemData; }

	UFUNCTION(BlueprintCallable)
	void SetItemData(const FItemData& InItemData);

	UFUNCTION(BlueprintCallable)
	bool IsNewItem() const { return bIsNewItem; }

	UFUNCTION(BlueprintCallable)
	void SetIsNewItem(bool InIsNewItem);

	UFUNCTION(BlueprintCallable)
	bool IsLocked() const { return bIsLocked; }

	UFUNCTION(BlueprintCallable)
	void SetIsLocked(bool InIsLocked);

	UFUNCTION(BlueprintCallable)
	bool IsSelected() const { return bIsSelected; }

	UFUNCTION(BlueprintCallable)
	void SetIsSelected(bool InIsSelected);

	UFUNCTION(BlueprintCallable)
	bool IsEquipped() const { return bIsEquipped; }

	UFUNCTION(BlueprintCallable)
	void SetIsEquipped(bool InIsEquipped);

	static FString FormatCash(int32 Cash);
};
