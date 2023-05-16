// Fill out your copyright notice in the Description page of Project Settings.


#include "UWUserCash.h"
#include <Components/TextBlock.h>
#include "UWItemSlot.h"

void UUWUserCash::NativePreConstruct()
{
	Update();
}

void UUWUserCash::Update()
{
	FSlateFontInfo fontInfo = Txt_Cash->GetFont();
	fontInfo.Size = FontSize;
	Txt_Cash->SetFont(fontInfo);
	Txt_Cash->SetText(FText::FromString(UUWItemSlot::FormatCash(Cash)));

	fontInfo = Txt_CashUnit->GetFont();
	fontInfo.Size = FontSize;
	Txt_CashUnit->SetFont(fontInfo);
}

void UUWUserCash::SetCash(int32 InCash)
{
	Cash = InCash;
	Update();
}

void UUWUserCash::SetFontSize(int32 InFontSize)
{
	FontSize = InFontSize;
	Update();
}
