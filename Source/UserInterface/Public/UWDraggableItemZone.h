// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include <DraggableItemData.h>
#include "Blueprint/UserWidget.h"
#include "UWDraggableItemZone.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnStartDragEvent);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnEndDragEvent);

/**
 * 
 */
UCLASS()
class USERINTERFACE_API UUWDraggableItemZone : public UUserWidget
{
	GENERATED_BODY()
	
	UPROPERTY(meta = (BindWidget))
	class UCanvasPanel* Canv_Root;

	UPROPERTY(meta = (BindWidget))
	class UImage* Img_ClickArea;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = true))
	TSubclassOf<class UUWDraggableItem> ItemTemplate;

	UPROPERTY()
	TObjectPtr<class UUWDraggableItem> CurrentDraggingItem = nullptr;
	FVector2D DragOffsetInLocal = FVector2D::ZeroVector;
	FGridPair OverlappedLeftTopIndex;
	bool bCanPlace;
	UPROPERTY()
	TObjectPtr<class UUWItemStorage> OverlappedItemStorage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess))
	TArray<TObjectPtr<class UUWItemStorage>> ItemStorages;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess))
	TObjectPtr<class UUWTrashCan> TrashCan;

	struct FThrowingItem
	{
		TObjectPtr<class UUWDraggableItem> ThrowingItemWidget = 0;
		float AccumulatedTime = 0;
		float Duration = 0;
		FVector2D StartPositionInAbsolute = FVector2D::ZeroVector;
		TObjectPtr<class UWidget> TargetWidget = 0;
		FVector2D StartAlignment;
		float StartScale = 0;
		float EndScale = 0;
		FThrowingItem(
			TObjectPtr<class UUWDraggableItem> InThrowingItemWidget,
			float InDuration,
			FVector2D InStartPositionInAbsolute,
			TObjectPtr<class UWidget> InTargetWidget,
			FVector2D InStartAlignment,
			float InStartScale,
			float InEndScale) :
			ThrowingItemWidget(InThrowingItemWidget),
			AccumulatedTime(0),
			Duration(InDuration),
			StartPositionInAbsolute(InStartPositionInAbsolute),
			TargetWidget(InTargetWidget),
			StartAlignment(InStartAlignment),
			StartScale(InStartScale),
			EndScale(InEndScale)
		{ }
	};
	TArray<FThrowingItem> ThrowingItems;

public:
	FOnStartDragEvent OnStartDrag;
	FOnEndDragEvent OnEndDrag;

protected:
	virtual void NativePreConstruct() override;
	virtual void NativeConstruct() override;
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override; 

	virtual void Internal_OnMouseButtonDown_AtViewport();

private:
	UFUNCTION()
	virtual void Internal_OnClickedSlot(class UUWItemStorage* InItemStorage, const FGridPair& InIndex);

	bool OverlapTrashCanWithDraggingItem() const;

public:
	UFUNCTION(BlueprintCallable)
	void StartDrag(class UUWDraggableItem* InItem, const FGeometry& InItemGeometry, bool UseOffset); 

	UFUNCTION(BlueprintCallable)
	class UUWDraggableItem* StopDrag(bool bRemoveDraggingItem = true); 

	UFUNCTION(BlueprintCallable)
	class UUWDraggableItem* GetDraggingItem() const { return CurrentDraggingItem; }	

	UFUNCTION(BlueprintCallable)
	const TArray<TObjectPtr<class UUWItemStorage>>& GetItemStorages() const { return ItemStorages; }
	
	UFUNCTION(BlueprintCallable)
	void AddItemStorage(class UUWItemStorage* InItemStorage);
};
