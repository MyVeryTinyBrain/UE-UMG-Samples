#pragma once

#include "CoreMinimal.h"
#include "HeroData.h"
#include <Engine/DataTable.h>
#include "SkillData.generated.h"

USTRUCT(BlueprintType)
struct FSkillData : public FTableRowBase
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString SkillName = TEXT("SKILL NAME");

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString SkillDescription = TEXT("SKILL DESCRIPTION");

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<class UTexture2D> SkillTexture;
	
	bool operator == (const FSkillData x) const
	{
		return
			SkillName == x.SkillName &&
			SkillDescription == x.SkillDescription &&
			SkillTexture == x.SkillTexture;
	}

	bool operator != (const FSkillData& x) const
	{
		return !(operator==(x));
	}

	static bool FindSkillData(class UDataTable* SkillDataTable, FName RowName, struct FSkillData& SkillData)
	{
		uint8* const* finded = SkillDataTable->GetRowMap().Find(RowName);
		if (finded == nullptr)
			return false;

		SkillData = *(reinterpret_cast<FSkillData*>(*finded));
		return true;
	}
};

USTRUCT(BlueprintType)
struct DATA_API FSkillArray
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<FSkillData> Array;
};
