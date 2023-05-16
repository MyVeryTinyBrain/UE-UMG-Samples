// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UserDataWidget.h"
#include "UWItemLoot.generated.h"

/**
 * 
 */
UCLASS()
class USERINTERFACE_API UUWItemLoot : public UUserDataWidget
{
	GENERATED_BODY()
	
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget = true, AllowPrivateAccess = true))
	class UUWDraggableItemZone* WBDZ_DraggableItemZone;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget = true, AllowPrivateAccess = true))
	class UUWItemStorage* WBIS_UserItemStorage;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget = true, AllowPrivateAccess = true))
	class UUWItemStorage* WBIS_LootItemStorage;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget = true, AllowPrivateAccess = true))
	class UUWInventoryButton* WBRB_UserItemSortButton;
	
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget = true, AllowPrivateAccess = true))
	class UUWInventoryButton* WBRB_LootItemSortButton;
	
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget = true, AllowPrivateAccess = true))
	class UUWInventoryButton* WBRB_LootItemRefreshButton;

private:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess))
	TObjectPtr<class UDataTable> DraggableItemDataTable = nullptr;

protected:
	virtual void NativeConstruct() override;

	virtual void NativeOnUserDataWidgetSetup() override;

	UFUNCTION()
	virtual void OnUserItemSortButtonClicked();

	UFUNCTION()
	virtual void OnLootSortButtonClicked();

	UFUNCTION()
	virtual void OnLootRefreshButtonClicked();

	UFUNCTION()
	virtual void OnStartDrag();

	UFUNCTION()
	virtual void OnEndDrag();

	UFUNCTION()
	virtual void Internal_OnChanged(class UUWItemStorage* InItemStorage);

private:
	void SetupLootItems();
};
