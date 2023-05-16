// Fill out your copyright notice in the Description page of Project Settings.


#include "UWSizableTextBlock.h"
#include <Components/TextBlock.h>
#include <Components/CanvasPanelSlot.h>
#include <Components/Image.h>

void UUWSizableTextBlock::NativePreConstruct()
{
	Super::NativePreConstruct();
	Update();
}

void UUWSizableTextBlock::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);
	
	switch (GetVisibility())
	{
		case ESlateVisibility::SelfHitTestInvisible:
		case ESlateVisibility::Visible:
			UpdateBorderSize();
			break;
	}
}

void UUWSizableTextBlock::Update()
{
	Txt_Text->SetFont(Font);
	Txt_Text->SetText(Text);

	UpdateBorderSize();
	UpdateBorderWidth();
}

void UUWSizableTextBlock::UpdateBorderSize()
{
	Txt_Text->ForceLayoutPrepass();

	if (UCanvasPanelSlot* BorderSlot = Cast<UCanvasPanelSlot>(Canv_Root->Slot))
	{
		BorderSlot->SetAlignment(Alignment);

		FVector2D TextSize = Txt_Text->GetDesiredSize();
		FVector2D BorderSize = TextSize + Margin;
		BorderSlot->SetSize(BorderSize);
	}
}

void UUWSizableTextBlock::UpdateBorderWidth()
{
	if (UCanvasPanelSlot* ImgSlot = Cast<UCanvasPanelSlot>(Img_Top->Slot))
	{
		FVector2D Size = ImgSlot->GetSize();
		Size.Y = BorderWidth;
		ImgSlot->SetSize(Size);
	}
	if (UCanvasPanelSlot* ImgSlot = Cast<UCanvasPanelSlot>(Img_Bottom->Slot))
	{
		FVector2D Size = ImgSlot->GetSize();
		Size.Y = BorderWidth;
		ImgSlot->SetSize(Size);
	}
	if (UCanvasPanelSlot* ImgSlot = Cast<UCanvasPanelSlot>(Img_left->Slot))
	{
		FVector2D Size = ImgSlot->GetSize();
		Size.X = BorderWidth;
		ImgSlot->SetSize(Size);
	}
	if (UCanvasPanelSlot* ImgSlot = Cast<UCanvasPanelSlot>(Img_Right->Slot))
	{
		FVector2D Size = ImgSlot->GetSize();
		Size.X = BorderWidth;
		ImgSlot->SetSize(Size);
	}
}

void UUWSizableTextBlock::SetText(const FText& InText)
{
	Text = InText;
	Update();
}

void UUWSizableTextBlock::SetFont(const FSlateFontInfo& InFont)
{
	Font = InFont;
	Update();
}

void UUWSizableTextBlock::SetBorderWidth(float InBorderWidth)
{
	BorderWidth = InBorderWidth;
	UpdateBorderWidth();
}

void UUWSizableTextBlock::SetMargin(const FVector2D& InMargin)
{
	Margin = InMargin;
	Update();
}

void UUWSizableTextBlock::SetAlignment(const FVector2D& InAlignment)
{
	Alignment = InAlignment;
	Update();
}
