// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "UserState.generated.h"

/**
 * 
 */
UCLASS()
class UMGSAMPLE_API AUserState : public APlayerState
{
	GENERATED_BODY()

	UPROPERTY()
	TObjectPtr<class UUserData> UserData = nullptr;

public:
	AUserState();

	UFUNCTION(BlueprintCallable)
	class UUserData* GetUserDataPtr() const { return UserData; }

protected:
	virtual void CopyProperties(APlayerState* PlayerState) override;
};
