// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include <DraggableItemData.h>
#include "Blueprint/UserWidget.h"
#include "UWDraggableItem.generated.h"

class UUWDraggableItem;
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnDraggableItemClickedEvent, UUWDraggableItem*, InDraggableItem);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnDraggableItemPressedEvent, UUWDraggableItem*, InDraggableItem);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnDraggableItemReleasedEvent, UUWDraggableItem*, InDraggableItem);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnDraggableItemHoverEvent, UUWDraggableItem*, InDraggableItem);

/**
 * 
 */
UCLASS()
class USERINTERFACE_API UUWDraggableItem : public UUserWidget
{
	GENERATED_BODY()
	
	UPROPERTY(meta = (BindWidget))
	class UUWImage* WBI_Image;

	UPROPERTY(meta = (BindWidget))
	class UImage* Img_Border_Top;

	UPROPERTY(meta = (BindWidget))
	class UImage* Img_Border_Bottom;

	UPROPERTY(meta = (BindWidget))
	class UImage* Img_Border_Left;

	UPROPERTY(meta = (BindWidget))
	class UImage* Img_Border_Right;

	UPROPERTY(meta = (BindWidget))
	class UImage* Img_Icon;

	UPROPERTY(meta = (BindWidget))
	class UButton* Button;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = true))
	float BorderWidth = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = true))
	float IconScale = 0.5f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess))
	bool bButtonEnable = true;

	FDraggableItemData ItemData;

public:
	/** Called when the button is clicked */
	UPROPERTY(BlueprintAssignable, Category = "Button|Event")
	FOnDraggableItemClickedEvent OnClicked;

	/** Called when the button is pressed */
	UPROPERTY(BlueprintAssignable, Category = "Button|Event")
	FOnDraggableItemPressedEvent OnPressed;

	/** Called when the button is released */
	UPROPERTY(BlueprintAssignable, Category = "Button|Event")
	FOnDraggableItemReleasedEvent OnReleased;

	UPROPERTY(BlueprintAssignable, Category = "Button|Event")
	FOnDraggableItemHoverEvent OnHovered;

	UPROPERTY(BlueprintAssignable, Category = "Button|Event")
	FOnDraggableItemHoverEvent OnUnhovered;

protected:
	virtual void NativeConstruct() override;
	virtual void NativePreConstruct() override;

	UFUNCTION()
	virtual void OnClickedButton();
	
	UFUNCTION()
	virtual void OnPressedButton();
	
	UFUNCTION()
	virtual void OnReleasedButton();

	UFUNCTION()
	virtual void OnHoveredButton();

	UFUNCTION()
	virtual void OnUnhoveredButton();

private:
	void UpdateIcon();
	void UpdateBorderAndImage();
	void UpdateButton();

public:
	UFUNCTION(BlueprintCallable)
	float GetBorderWidth() const { return BorderWidth; }

	UFUNCTION(BlueprintCallable)
	void SetBorderWidth(float InBorderWidth);

	UFUNCTION(BlueprintCallable)
	float GetIconScale() const { return IconScale; }

	UFUNCTION(BlueprintCallable)
	void SetIconScale(float InIconScale);

	UFUNCTION(BlueprintCallable)
	bool IsEnabledButton() const { return bButtonEnable; }

	UFUNCTION(BlueprintCallable)
	void SetButtonEnable(bool InEnable);

	UFUNCTION(BlueprintCallable)
	const FDraggableItemData& GetItemData() { return ItemData; }

	UFUNCTION(BlueprintCallable)
	void SetItemData(const FDraggableItemData& InItemData);

	UFUNCTION(BlueprintCallable)
	static FVector2D GetCellSizeInAbsolute(UUWDraggableItem* InItem);

	UFUNCTION(BlueprintCallable)
	static FVector2D GetCellCenterInAbsolute(UUWDraggableItem* InItem, const FGridPair& InIndex);

	UFUNCTION(BlueprintCallable)
	static UUWDraggableItem* Copy(TSubclassOf<UUWDraggableItem> Template, UUWDraggableItem* InSrc, const FDraggableItemData& InItemData, UPanelWidget* Parent);
};
