// Fill out your copyright notice in the Description page of Project Settings.


#include "UWDraggableItem.h"
#include "UWImage.h"
#include <Components/Image.h>
#include <Components/CanvasPanelSlot.h>
#include <Components/Button.h>
#include <Blueprint/WidgetLayoutLibrary.h>
#include <Blueprint/SlateBlueprintLibrary.h>
#include "UserInterfaceLibrary.h"

void UUWDraggableItem::NativeConstruct()
{
	Super::NativeConstruct();

	Button->OnClicked.AddDynamic(this, &UUWDraggableItem::OnClickedButton);
	Button->OnPressed.AddDynamic(this, &UUWDraggableItem::OnPressedButton);
	Button->OnReleased.AddDynamic(this, &UUWDraggableItem::OnReleasedButton);
	Button->OnHovered.AddDynamic(this, &UUWDraggableItem::OnHoveredButton);
	Button->OnUnhovered.AddDynamic(this, &UUWDraggableItem::OnUnhoveredButton);
}

void UUWDraggableItem::NativePreConstruct()
{
	Super::NativePreConstruct();
	UpdateIcon();
	UpdateBorderAndImage();
}

void UUWDraggableItem::OnClickedButton()
{
	OnClicked.Broadcast(this);
}

void UUWDraggableItem::OnPressedButton()
{
	OnPressed.Broadcast(this);
}

void UUWDraggableItem::OnReleasedButton()
{
	OnReleased.Broadcast(this);
}

void UUWDraggableItem::OnHoveredButton()
{
	OnHovered.Broadcast(this);
}

void UUWDraggableItem::OnUnhoveredButton()
{
	OnUnhovered.Broadcast(this);
}

void UUWDraggableItem::UpdateIcon()
{
	Img_Icon->SetBrushFromTexture(ItemData.ItemTexture);

	if (ItemData.ItemTexture)
	{
		Img_Icon->SetVisibility(ESlateVisibility::Visible);
	}
	else
	{
		Img_Icon->SetVisibility(ESlateVisibility::Hidden);
	}

	if (UCanvasPanelSlot* CanvasPanelSlot = Cast<UCanvasPanelSlot>(Img_Icon->Slot))
	{
		float CenterXRatio = FMath::Clamp(ItemData.SizeX / (float)ItemData.SizeY, 0.0f, 1.0f) * IconScale;
		float CenterYRatio = FMath::Clamp(ItemData.SizeY / (float)ItemData.SizeX, 0.0f, 1.0f) * IconScale;
		float SideXRatio = (1.0f - CenterYRatio) * 0.5f;
		float SideYRatio = (1.0f - CenterXRatio) * 0.5f;

		CanvasPanelSlot->SetAnchors(FAnchors(SideXRatio, SideYRatio, 1.0f - SideXRatio, 1.0f - SideYRatio));
		CanvasPanelSlot->SetOffsets(FMargin(0, 0, 0, 0));
	}
}

void UUWDraggableItem::UpdateBorderAndImage()
{
	WBI_Image->SetPadding(FMargin(BorderWidth, BorderWidth, BorderWidth, BorderWidth));

	if (UCanvasPanelSlot* CanvasPanelSlot = Cast<UCanvasPanelSlot>(Img_Border_Top->Slot))
	{
		FVector2D Size = CanvasPanelSlot->GetSize();
		Size.Y = BorderWidth;
		CanvasPanelSlot->SetSize(Size);
	}
	if (UCanvasPanelSlot* CanvasPanelSlot = Cast<UCanvasPanelSlot>(Img_Border_Bottom->Slot))
	{
		FVector2D Size = CanvasPanelSlot->GetSize();
		Size.Y = BorderWidth;
		CanvasPanelSlot->SetSize(Size);
	}
	if (UCanvasPanelSlot* CanvasPanelSlot = Cast<UCanvasPanelSlot>(Img_Border_Left->Slot))
	{
		FVector2D Size = CanvasPanelSlot->GetSize();
		Size.X = BorderWidth;
		CanvasPanelSlot->SetSize(Size);
	}
	if (UCanvasPanelSlot* CanvasPanelSlot = Cast<UCanvasPanelSlot>(Img_Border_Right->Slot))
	{
		FVector2D Size = CanvasPanelSlot->GetSize();
		Size.X = BorderWidth;
		CanvasPanelSlot->SetSize(Size);
	}
}

void UUWDraggableItem::UpdateButton()
{
	Button->SetIsEnabled(bButtonEnable);
}

void UUWDraggableItem::SetBorderWidth(float InBorderWidth)
{
	BorderWidth = InBorderWidth;
	UpdateBorderAndImage();
}

void UUWDraggableItem::SetIconScale(float InIconScale)
{
	IconScale = InIconScale;
	UpdateIcon();
}

void UUWDraggableItem::SetButtonEnable(bool InEnable)
{
	bButtonEnable = InEnable;
	UpdateButton();
}

void UUWDraggableItem::SetItemData(const FDraggableItemData& InItemData)
{
	ItemData = InItemData;
	UpdateIcon();
}

FVector2D UUWDraggableItem::GetCellSizeInAbsolute(UUWDraggableItem* InItem)
{
	UCanvasPanelSlot* ItemCanvasSlotPanel = Cast<UCanvasPanelSlot>(InItem->Slot);
	if (!ItemCanvasSlotPanel)
		return FVector2D::ZeroVector;

	FVector2D ItemSize = ItemCanvasSlotPanel->GetSize();
	FVector2D CellLTInLocal = FVector2D::ZeroVector;
	FVector2D CellRBInLocal = FVector2D(ItemSize.X / InItem->ItemData.SizeX, ItemSize.Y / InItem->ItemData.SizeY);
	FVector2D CellLTInAbsolute = UUserInterfaceLibrary::LocalToAbsolute(InItem->GetParent(), CellLTInLocal);
	FVector2D CellRBInAbsolute = UUserInterfaceLibrary::LocalToAbsolute(InItem->GetParent(), CellRBInLocal);

	return CellRBInAbsolute - CellLTInAbsolute;
}

FVector2D UUWDraggableItem::GetCellCenterInAbsolute(UUWDraggableItem* InItem, const FGridPair& InIndex)
{
	UCanvasPanelSlot* ItemCanvasSlotPanel = Cast<UCanvasPanelSlot>(InItem->Slot);
	if (!ItemCanvasSlotPanel)
		return FVector2D::ZeroVector;

	FVector2D ItemSize = ItemCanvasSlotPanel->GetSize();
	FVector2D CellSize = FVector2D(ItemSize.X / InItem->ItemData.SizeX, ItemSize.Y / InItem->ItemData.SizeY);

	FVector2D Index = FVector2D(int32(InIndex.X), int32(InIndex.Y));
	FVector2D InLocal = (CellSize * 0.5f) + (Index * CellSize);
	FVector2D InAbsolute = UUserInterfaceLibrary::LocalToAbsolute(InItem, InLocal);
	return InAbsolute;
}

UUWDraggableItem* UUWDraggableItem::Copy(TSubclassOf<UUWDraggableItem> Template, UUWDraggableItem* InSrc, const FDraggableItemData& InItemData, UPanelWidget* Parent)
{
	UUWDraggableItem* NewItem = CreateWidget<UUWDraggableItem>(Parent, Template);
	Parent->AddChild(NewItem);
	NewItem->SetItemData(InItemData);

	if (InSrc)
	{
		UCanvasPanelSlot* SrcCanvasSlotPanel = Cast<UCanvasPanelSlot>(InSrc->Slot);
		UCanvasPanelSlot* NewCanvasSlotPanel = Cast<UCanvasPanelSlot>(NewItem->Slot);

		if (SrcCanvasSlotPanel && NewCanvasSlotPanel)
		{
			FVector2D ItemInLocal = UUserInterfaceLibrary::GetLocalPositionOf(Parent, InSrc);
			FVector2D ItemSize = SrcCanvasSlotPanel->GetSize();

			NewCanvasSlotPanel->SetPosition(ItemInLocal);
			NewCanvasSlotPanel->SetSize(ItemSize);
		}
	}

	return NewItem;
}
