// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include <DraggableItemData.h>
#include "Blueprint/UserWidget.h"
#include "UWItemGrid.generated.h"

class UUWItemGrid;
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnClickedItemGridSlot, UUWItemGrid*, InItemGrid, const FGridPair&, InIndex);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnChangedItemGrid, UUWItemGrid*, InItemGrid);

/**
 * 
 */
UCLASS()
class USERINTERFACE_API UUWItemGrid : public UUserWidget
{
	GENERATED_BODY()

	UPROPERTY(meta = (BindWidget))
	class UCanvasPanel* Canv_SlotArea;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = true))
	int32 CountX;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = true))
	int32 CountY;

	UPROPERTY()
	FVector2D SlotAreaCanvasSize;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = true))
	TSubclassOf<class UUWItemGridCell> CellTemplate;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = true))
	TSubclassOf<class UUWDraggableItem> ItemTemplate;

	UPROPERTY()
	TArray<TObjectPtr<class UUWItemGridCell>> Cells;

	TMap<FGridPair, TObjectPtr<class UUWDraggableItem>> Items;
	TMap<FGridPair, TObjectPtr<class UUWDraggableItem>> UsingCells;

public:
	FOnChangedItemGrid OnChanged;
	FOnClickedItemGridSlot OnClickedSlot;

protected:
	virtual void NativeConstruct() override;
	virtual void NativePreConstruct() override;

	virtual void Internal_OnChanged();
	virtual void Internal_OnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent);
	virtual FReply NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent) override;
	virtual FReply NativeOnMouseButtonDoubleClick(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent) override;

public:
	UFUNCTION()
	virtual void OnPressedDraggableItem(class UUWDraggableItem* InItem);

private:
	void ReplaceElements();
	void Internal_SetItem(const FGridPair& InIndex, class UUWDraggableItem* InItem, bool bGenerateChangedNotify);
	void GenerateMouseButtonDownEvent();

public:
	UFUNCTION(BlueprintCallable)
	void SetCount(int32 InCountX, int32 InCountY);

	UFUNCTION(BlueprintCallable)
	int32 GetCountX() const { return CountX; }

	UFUNCTION(BlueprintCallable)
	int32 GetCountY() const { return CountY; }

	UFUNCTION(BlueprintCallable)
	void SetCountX(int32 InCountX);

	UFUNCTION(BlueprintCallable)
	void SetCountY(int32 InCountY);

	UFUNCTION(BlueprintCallable)
	FGridPair LocalPositionToIndex(const FVector2D& InLocalPosition) const;

	UFUNCTION(BlueprintCallable)
	FGridPair AbsolutePositionToIndex(const FVector2D& InAbsolutePosition) const;
	
	UFUNCTION(BlueprintCallable)
	FVector2D IndexToLocalPosition(const FGridPair& InIndex) const;

	UFUNCTION(BlueprintCallable)
	FVector2D IndexToAbsolutePosition(const FGridPair& InIndex) const;

	UFUNCTION(BlueprintCallable)
	FVector2D GetCellSize() const;

	UFUNCTION(BlueprintCallable)
	bool CanPlaceAt(const FGridPair& InIndex, int32 SizeX, int32 SizeY) const;

	UFUNCTION(BlueprintCallable)
	bool CreateAndSetItem(const FGridPair& InIndex, const FDraggableItemData& InItemData, bool bGenerateChangedNotify = true);

	UFUNCTION(BlueprintCallable)
	bool SetItem(const FGridPair& InIndex, class UUWDraggableItem* InItem, bool bGenerateChangedNotify = true);

	UFUNCTION(BlueprintCallable)
	UUWDraggableItem* GetItem(const FGridPair& InIndex) const;

	UFUNCTION(BlueprintCallable)
	bool GetItemIndex(class UUWDraggableItem* InItem, FGridPair& OutIndex) const;

	UFUNCTION(BlueprintCallable)
	bool RemoveItem(class UUWDraggableItem* InItem, bool bGenerateChangedNotify = true);

	UFUNCTION(BlueprintCallable)
	void ClearItems(bool bGenerateChangedNotify = true);

	UFUNCTION(BlueprintCallable)
	class UUWItemGridCell* GetCell(const FGridPair& InIndex) const;
	
	UFUNCTION(BlueprintCallable)
	void ResetCellsMode(EItemGridCellMode InMode);

	UFUNCTION(BlueprintCallable)
	void LoadFromContainer(class UDraggableItemContainer* InContainer, bool bGenerateChangedNotify = true);

	UFUNCTION(BlueprintCallable)
	void LoadFromUserData(class UUserData* InUserData, bool bGenerateChangedNotify = true);

	UFUNCTION(BlueprintCallable)
	void StoreToUserData(class UUserData* InUserData) const;

	UFUNCTION(BlueprintCallable)
	bool Sort(bool bGenerateChangedNotify = true);

	UFUNCTION(BlueprintCallable)
	static void InitializeItemGrid(UUWItemGrid* InItemGrid, const FVector2D& InGridSize);
};
