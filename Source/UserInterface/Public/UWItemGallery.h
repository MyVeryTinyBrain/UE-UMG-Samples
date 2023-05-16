// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include <ItemData.h>
#include "HeroGalleryWidget.h"
#include "Blueprint/UserWidget.h"
#include "UWItemGallery.generated.h"

/**
 * 
 */
UCLASS()
class USERINTERFACE_API UUWItemGallery : public UHeroGalleryWidget
{
	GENERATED_BODY()

	UPROPERTY(meta = (BindWidget))
	class UUWUserName* WBUN_UserName;

	UPROPERTY(meta = (BindWidget))
	class UUWUserCash* WBUC_UserCash;

	UPROPERTY(meta = (BindWidget))
	class UUWItemTypeSelector* WBITS_ItemTypeSelector;

	UPROPERTY(meta = (BindWidget))
	class UUWItemCount* WBIC_ItemCount;

	UPROPERTY(meta = (BindWidget))
	class UUWItemList* WBIL_ItemList;

	UPROPERTY(meta = (BindWidget))
	class UUWButton* WBB_Equip;

	UPROPERTY(meta = (BindWidget))
	class UUWButton* WBB_Unlock;

private:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess))
	EItemType ItemType = EItemType::None;

protected:
	virtual void NativeOnHeroGalleryWidgetSetup();
	virtual void NativePreConstruct() override;
	virtual void NativeConstruct() override;

	UFUNCTION()
	virtual void OnSelectorButtonClicked(int Direction);

	UFUNCTION()
	virtual void OnItemSlotSelected();

	UFUNCTION()
	virtual void OnEquipClicked();

	UFUNCTION()
	virtual void OnUnlockClicked();

private:
	FString GetCurrentItemTypeName() const;

	void Update();
	void UpdateClickable();
};
