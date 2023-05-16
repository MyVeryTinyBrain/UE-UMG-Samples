#include "SkillMapData.h"

class UDataTable* FSkillMapData::FindSkillDataTable(UDataTable* SkillMapDataTable, EHeroType HeroType)
{
    TArray<FSkillMapData*> Pointers;
    SkillMapDataTable->GetAllRows(TEXT("GetAllRows"), Pointers);

    for (FSkillMapData* Pointer : Pointers)
    {
        if (Pointer->HeroType == HeroType)
            return Pointer->SkillDataTable;
    }

    return nullptr;
}
