#pragma once

#include "CoreMinimal.h"
#include "SkillData.h"
#include "HeroData.h"
#include <Engine/DataTable.h>
#include "SkillMapData.generated.h"

USTRUCT(BlueprintType)
struct DATA_API FSkillMapData : public FTableRowBase
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	EHeroType HeroType = EHeroType::None;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UDataTable* SkillDataTable = nullptr;

	static class UDataTable* FindSkillDataTable(class UDataTable* SkillMapDataTable, EHeroType HeroType);
};
