// Fill out your copyright notice in the Description page of Project Settings.


#include "UWItemCount.h"
#include <Components/TextBlock.h>

void UUWItemCount::NativePreConstruct()
{
	Super::NativePreConstruct();

	UpdateTitle();
}

void UUWItemCount::UpdateTitle()
{
	Txt_Title->SetText(Title);

	FString ContextText = FString::Printf(TEXT("%d/%d"), ItemCount, MaxItemCount);
	Txt_ItemCount->SetText(FText::FromString(ContextText));
}

void UUWItemCount::SetTitle(const FText& InTitile)
{
	Title = InTitile;
	UpdateTitle();
}

void UUWItemCount::SetTitle(const FString& InTitile)
{
	Title = FText::FromString(InTitile);
	UpdateTitle();
}

void UUWItemCount::SetItemCount(int32 InItemCount)
{
	ItemCount = InItemCount;
	UpdateTitle();
}

void UUWItemCount::SetMaxItemCount(int32 IntMaxItemCount)
{
	MaxItemCount = IntMaxItemCount;
	UpdateTitle();
}
