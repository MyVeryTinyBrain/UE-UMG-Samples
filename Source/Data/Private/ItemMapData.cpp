// Fill out your copyright notice in the Description page of Project Settings.


#include "ItemMapData.h"


class UDataTable* FItemMapData::FindItemDataTable(class UDataTable* ItemMapDataTable, EHeroType HeroType, EItemType ItemType)
{
    TArray<FItemMapData*> Pointers;
    ItemMapDataTable->GetAllRows(TEXT("GetAllRows"), Pointers);
    
    for (FItemMapData* Pointer : Pointers)
    {
        if (Pointer->HeroType == HeroType && Pointer->ItemType == ItemType)
            return Pointer->ItemDataTable;
    }

    return nullptr;
}
