// Fill out your copyright notice in the Description page of Project Settings.


#include "ItemData.h"

FItemData FItemData::Invalid()
{ 
	return  FItemData(EItemType::None, -1, 0, TEXT("INVALID")); 
}

FLinearColor FItemData::GetColorOfGrade() const
{
	switch (Grade)
	{
		case 0:
			return FLinearColor::White;
		case 1:
			return FLinearColor(0.1f, 0.35f, 1.0f, 1.0f);	// Blue
		case 2:
			return FLinearColor(0.2f, 0.1f, 0.85f, 1.0f);	// Purple
		case 3:
			return FLinearColor(1.0f, 1.0f, 0.1f, 1.0f);	// Yellow
		case 4:
			return FLinearColor::Red;
	}
	return FLinearColor::White;
}

bool FItemData::operator==(const FItemData& x) const
{
	return
		ItemType == x.ItemType &&
		Grade == x.Grade &&
		Cost == x.Cost &&
		ItemName == x.ItemName;
}

bool FItemData::operator!=(const FItemData& x) const
{
	return !FItemData::operator==(x);
}

void FItemsByItemType::Add(const FItemData& ItemData)
{
	FItemsArray& ItemsArray = Map.FindOrAdd(ItemData.ItemType);
	ItemsArray.Array.Add(ItemData);
}

bool FItemsByItemType::Contains(FItemData ItemData) const
{
	const FItemsArray* pItemsArray = Map.Find(ItemData.ItemType);
	if (!pItemsArray)
		return false;
	return pItemsArray->Array.Contains(ItemData);
}

int32 FItemsByItemType::Num(EItemType ItemType) const
{
	const FItemsArray* pItemsArray = Map.Find(ItemType);
	if (!pItemsArray)
		return 0;
	return pItemsArray->Array.Num();
}

TArray<FItemData>* FItemsByItemType::FindItemsByItemType(EItemType ItemType)
{
	FItemsArray* pItemsArray = Map.Find(ItemType);
	if (!pItemsArray)
		return nullptr;
	return &pItemsArray->Array;
}

const TArray<FItemData>* FItemsByItemType::FindItemsByItemType(EItemType ItemType) const
{
	const FItemsArray* pItemsArray = Map.Find(ItemType);
	if (!pItemsArray)
		return nullptr;
	return &pItemsArray->Array;
}

void FItemsByHeroType::Add(EHeroType HeroType, const FItemData& ItemData)
{
	FItemsByItemType& ItemMapByItem = Map.FindOrAdd(HeroType);
	ItemMapByItem.Add(ItemData);
}

bool FItemsByHeroType::Contains(EHeroType HeroType, FItemData ItemData) const
{
	const FItemsByItemType* pItemMapByItem = Map.Find(HeroType);
	if (!pItemMapByItem)
		return false;
	return pItemMapByItem->Contains(ItemData);
}

int32 FItemsByHeroType::Num(EHeroType HeroType, EItemType ItemType) const
{
	const FItemsByItemType* pItemMapByItem = Map.Find(HeroType);
	if (!pItemMapByItem)
		return 0;
	return pItemMapByItem->Num(ItemType);
}

TArray<FItemData>* FItemsByHeroType::FindItems(EHeroType HeroType, EItemType ItemType)
{
	FItemsByItemType* pItemMapByItem = Map.Find(HeroType);
	if (!pItemMapByItem)
		return nullptr;
	return pItemMapByItem->FindItemsByItemType(ItemType);
}

const TArray<FItemData>* FItemsByHeroType::FindItems(EHeroType HeroType, EItemType ItemType) const
{
	const FItemsByItemType* pItemMapByItem = Map.Find(HeroType);
	if (!pItemMapByItem)
		return nullptr;
	return pItemMapByItem->FindItemsByItemType(ItemType);
}
