// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include <DraggableItemData.h>
#include "Blueprint/UserWidget.h"
#include "UWItemStorage.generated.h"

class UUWItemStorage;
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnClickedItemStorageSlot, UUWItemStorage*, InItemStorage, const FGridPair&, InIndex);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnChangedItemStorage, UUWItemStorage*, InItemStorage);

/**
 * 
 */
UCLASS()
class USERINTERFACE_API UUWItemStorage : public UUserWidget
{
	GENERATED_BODY()

	UPROPERTY(meta = (BindWidget))
	class UUWItemGrid* WBIG_ItemGrid;

	UPROPERTY(meta = (BindWidget))
	class UImage* Img_Border_Top;

	UPROPERTY(meta = (BindWidget))
	class UImage* Img_Border_Bottom;

	UPROPERTY(meta = (BindWidget))
	class UImage* Img_Border_Left;

	UPROPERTY(meta = (BindWidget))
	class UImage* Img_Border_Right;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = true))
	int32 CountX;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = true))
	int32 CountY;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = true))
	float CellSize = 100;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = true))
	float BorderWidth = 0;

public:
	FOnClickedItemStorageSlot OnClickedSlot;
	FOnChangedItemStorage OnChanged;

protected:
	virtual void NativeConstruct() override;
	virtual void NativePreConstruct() override;

	UFUNCTION()
	virtual void Internal_OnClickedSlot(class UUWItemGrid* InItemGrid, const FGridPair& Index);

	UFUNCTION()
	virtual void Internal_OnChanged(class UUWItemGrid* InItemGrid);

private:
	void UpdateBorder();
	void UpdateGrid();

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
	float GetBorderWidth() const { return BorderWidth; }

	UFUNCTION(BlueprintCallable)
	void SetBorderWidth(float InBorderWidth);

	UFUNCTION(BlueprintCallable)
	class UUWItemGrid* GetItemGrid() const { return WBIG_ItemGrid; }
};
