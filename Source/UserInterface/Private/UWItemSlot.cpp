// Fill out your copyright notice in the Description page of Project Settings.


#include "UWItemSlot.h"
#include <Components/TextBlock.h>
#include <Components/Overlay.h>
#include <Components/Image.h>

void UUWItemSlot::NativeConstruct()
{
	Super::NativeConstruct();

	Button->OnClicked.AddDynamic(this, &UUWItemSlot::Internal_OnClicked);
	Button->OnPressed.AddDynamic(this, &UUWItemSlot::Internal_OnPressed);
	Button->OnReleased.AddDynamic(this, &UUWItemSlot::Internal_OnReleased);
	Button->OnHovered.AddDynamic(this, &UUWItemSlot::Internal_OnHovered);
	Button->OnUnhovered.AddDynamic(this, &UUWItemSlot::Internal_OnUnhovered);
}

void UUWItemSlot::NativePreConstruct()
{
	Update();
}

void UUWItemSlot::Internal_OnClicked()
{
	OnClicked.Broadcast(this);
}

void UUWItemSlot::Internal_OnPressed()
{
	OnPressed.Broadcast(this);
}

void UUWItemSlot::Internal_OnReleased()
{
	OnReleased.Broadcast(this);
}

void UUWItemSlot::Internal_OnHovered()
{
	OnHovered.Broadcast(this);
}

void UUWItemSlot::Internal_OnUnhovered()
{
	OnUnhovered.Broadcast(this);
}

void UUWItemSlot::Update()
{
	// Set visual
	Img_Select->SetVisibility(bIsSelected ? ESlateVisibility::Visible : ESlateVisibility::Collapsed);
	Img_Equip->SetVisibility(bIsEquipped ? ESlateVisibility::Visible : ESlateVisibility::Collapsed);

	FLinearColor Color = ItemData.GetColorOfGrade();
	FLinearColor InvertedColor = FLinearColor(1 - Color.R, 1 - Color.G, 1 - Color.B, Color.A);

	Txt_ItemName->SetText(FText::FromString(ItemData.ItemName));
	Txt_ItemName->SetColorAndOpacity(Color);

	ESlateVisibility NewSkinIconVisibility = bIsNewItem ? ESlateVisibility::Visible : ESlateVisibility::Collapsed;
	Ov_NewIcon->SetVisibility(NewSkinIconVisibility);
	Img_NewBox->SetColorAndOpacity(Color);
	Txt_NewText->SetColorAndOpacity(InvertedColor);

	Txt_Cost->SetText(FText::FromString(FormatCash(ItemData.Cost)));

	// Set Visibilty by Lock State
	if (bIsLocked)
	{
		Img_Lock->SetVisibility(ESlateVisibility::Visible);
		Img_Unlock->SetVisibility(ESlateVisibility::Collapsed);
	}
	else
	{
		Img_Lock->SetVisibility(ESlateVisibility::Collapsed);
		Img_Unlock->SetVisibility(ESlateVisibility::Visible);
	}
}

void UUWItemSlot::SetSelectState(bool Value)
{
	bIsSelected = Value;
	Update();
}

void UUWItemSlot::SetEquipState(bool Value)
{
	bIsEquipped = Value;
	Update();
}

void UUWItemSlot::SetItemData(const FItemData& InItemData)
{
	ItemData = InItemData;
	Update();
}

void UUWItemSlot::SetIsNewItem(bool InIsNewItem)
{
	bIsNewItem = InIsNewItem;
	Update();
}

void UUWItemSlot::SetIsLocked(bool InIsLocked)
{
	bIsLocked = InIsLocked;
	Update();
}

void UUWItemSlot::SetIsSelected(bool InIsSelected)
{
	bIsSelected = InIsSelected;
	Update();
}

void UUWItemSlot::SetIsEquipped(bool InIsEquipped)
{
	bIsEquipped = InIsEquipped;
	Update();
}

FString UUWItemSlot::FormatCash(int32 Cash)
{
	// Insert ',' at every 3 numbers from right to left
	FString CostText = FString::FromInt(Cash);
	int32 charCounting = 0;
	for (int32 i = CostText.Len() - 1; i > 0; --i)
	{
		++charCounting;
		if (charCounting == 3)
		{
			charCounting = 0;
			CostText.InsertAt(i, TEXT(','));
		}
	}
	return CostText;
}
