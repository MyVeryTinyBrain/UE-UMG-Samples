// Fill out your copyright notice in the Description page of Project Settings.


#include "UWItemTypeSelector.h"
#include <Components/Button.h>
#include <Components/TextBlock.h>

void UUWItemTypeSelector::NativeConstruct()
{
	Btn_Left->OnClicked.AddDynamic(this, &UUWItemTypeSelector::Internal_OnLeftClicked);
	Btn_Right->OnClicked.AddDynamic(this, &UUWItemTypeSelector::Internal_OnRightClicked);
}

void UUWItemTypeSelector::NativePreConstruct()
{
	Super::NativePreConstruct();

	UpdateTitle();
}

void UUWItemTypeSelector::Internal_OnLeftClicked()
{
	OnClicked.Broadcast(-1);
}

void UUWItemTypeSelector::Internal_OnRightClicked()
{
	OnClicked.Broadcast(+1);
}

void UUWItemTypeSelector::UpdateTitle()
{
	Txt_Title->SetText(Title);

	FSlateFontInfo font = Txt_Title->GetFont();
	font.Size = TitleFontSize;
	Txt_Title->SetFont(font);

	font = Txt_LeftBtn->GetFont();
	font.Size = ButtonFontSize;
	Txt_LeftBtn->SetFont(font);
	Txt_RightBtn->SetFont(font);
}

void UUWItemTypeSelector::SetTitle(const FText& InTitle)
{
	Title = InTitle;
	UpdateTitle();
}

void UUWItemTypeSelector::SetTitle(const FString& InTitle)
{
	Title = FText::FromString(InTitle);
	UpdateTitle();
}

void UUWItemTypeSelector::SetTitleFontSize(int32 InTitleFontSize)
{
	TitleFontSize = InTitleFontSize;
	UpdateTitle();
}

void UUWItemTypeSelector::SetButtonFontSize(int32 InButtonFontSize)
{
	ButtonFontSize = InButtonFontSize;
	UpdateTitle();
}
