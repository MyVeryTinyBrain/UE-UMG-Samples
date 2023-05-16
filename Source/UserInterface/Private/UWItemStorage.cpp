// Fill out your copyright notice in the Description page of Project Settings.


#include "UWItemStorage.h"
#include "UWItemGrid.h"
#include <Components/CanvasPanelSlot.h>
#include <Components/Image.h>
#include "UserInterfaceLibrary.h"

void UUWItemStorage::NativeConstruct()
{
	Super::NativeConstruct();

	WBIG_ItemGrid->OnClickedSlot.AddDynamic(this, &UUWItemStorage::Internal_OnClickedSlot);
	WBIG_ItemGrid->OnChanged.AddDynamic(this, &UUWItemStorage::Internal_OnChanged);
}

void UUWItemStorage::NativePreConstruct()
{
	Super::NativePreConstruct();

	UpdateBorder();
	UpdateGrid();
}

void UUWItemStorage::Internal_OnClickedSlot(class UUWItemGrid* InItemGrid, const FGridPair& Index)
{
	OnClickedSlot.Broadcast(this, Index);
}

void UUWItemStorage::Internal_OnChanged(class UUWItemGrid* InItemGrid)
{
	OnChanged.Broadcast(this);
}

void UUWItemStorage::UpdateBorder()
{
	WBIG_ItemGrid->SetPadding(FMargin(BorderWidth, BorderWidth, BorderWidth, BorderWidth));

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

void UUWItemStorage::UpdateGrid()
{
	FVector2D Size = FVector2D(CountX, CountY) * CellSize;

	if (UCanvasPanelSlot* CanvasPanelSlot = Cast<UCanvasPanelSlot>(WBIG_ItemGrid->Slot))
	{
		CanvasPanelSlot->SetSize(Size);
	}

	WBIG_ItemGrid->SetCount(CountX, CountY);
	UUWItemGrid::InitializeItemGrid(WBIG_ItemGrid, Size);
}

void UUWItemStorage::SetCount(int32 InCountX, int32 InCountY)
{
	CountX = InCountX;
	CountY = InCountY;
	UpdateGrid();
}

void UUWItemStorage::SetCountX(int32 InCountX)
{
	CountX = InCountX;
	UpdateGrid();
}

void UUWItemStorage::SetCountY(int32 InCountY)
{
	CountY = InCountY;
	UpdateGrid();
}

void UUWItemStorage::SetBorderWidth(float InBorderWidth)
{
	BorderWidth = InBorderWidth;
	UpdateBorder();
}
