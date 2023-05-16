// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include <ItemData.h>
#include "Blueprint/UserWidget.h"
#include "UWItemList.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnItemSlotSelectedEvent);

/**
 * 
 */
UCLASS()
class USERINTERFACE_API UUWItemList : public UUserWidget
{
	GENERATED_BODY()

	UPROPERTY(meta = (BindWidget))
	class UScrollBox* SB_ItemList;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = true))
	TSubclassOf<class UUWItemSlot> ElementTemplate;

private:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, BlueprintGetter = "GetItemList", BlueprintSetter = "SetItemList", meta = (AllowPrivateAccess))
	TArray<FItemData> ItemList;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, BlueprintGetter = "GetOwnedItems", BlueprintSetter = "SetOwnedItems", meta = (AllowPrivateAccess))
	TArray<FItemData> OwnedItems;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, BlueprintGetter = "GetEquippedItem", BlueprintSetter = "SetEquippedItem", meta = (AllowPrivateAccess))
	FItemData EquippedItem;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, BlueprintGetter = "GetSelect", BlueprintSetter = "SetSelect", meta = (AllowPrivateAccess))
	int32 Select = -1;

public:
	UPROPERTY(BlueprintAssignable, Category = "Button|Event")
	FOnItemSlotSelectedEvent OnItemSlotSelected;

protected:
	virtual void NativeConstruct() override;
	virtual void NativePreConstruct() override;

	UFUNCTION()
	virtual void OnItemSlotClicked(class UUWItemSlot* ItemSlot);

private:
	class UUWItemSlot* GetItemSlotByIndex(int32 Index) const;
	void AddItemSlot(const FItemData& ItemData, bool IsNewItem, bool IsLocked);
	void UpdateItemList();
	void UpdateEquippedState();
	void UpdateSelectedState();

public:
	void ResetEquippedItem();

	UFUNCTION(BlueprintCallable)
	bool HasValidSelectedItemData() const;

	UFUNCTION(BlueprintCallable)
	FItemData GetSelectedItemData() const;

	UFUNCTION(BlueprintCallable)
	const TArray<FItemData>& GetItemList() const { return ItemList; };

	UFUNCTION(BlueprintCallable)
	void SetItemList(const TArray<FItemData>& InItemList);
	void MoveItemList(TArray<FItemData>&& InItemList);

	UFUNCTION(BlueprintCallable)
	const TArray<FItemData>& GetOwnedItems() const { return OwnedItems; };

	UFUNCTION(BlueprintCallable)
	void SetOwnedItems(const TArray<FItemData>& InOwnedItems);
	void MoveOwnedItems(TArray<FItemData>&& InOwnedItems);

	UFUNCTION(BlueprintCallable)
	const FItemData& GetEquippedItem() const { return EquippedItem; };

	UFUNCTION(BlueprintCallable)
	void SetEquippedItem(const FItemData& InEquippedItem);

	UFUNCTION(BlueprintCallable)
	int32 GetSelect() const { return Select; };

	UFUNCTION(BlueprintCallable)
	void SetSelect(int32 InSelect);
};
