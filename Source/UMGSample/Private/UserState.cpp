// Fill out your copyright notice in the Description page of Project Settings.


#include "UserState.h"
#include <UserData.h>

AUserState::AUserState()
{
	if (!UserData)
	{
		UserData = NewObject<UUserData>();
	}
}

void AUserState::CopyProperties(APlayerState* PlayerState)
{
	Super::CopyProperties(PlayerState);

	if (AUserState* UserState = Cast<AUserState>(PlayerState))
	{
		UserData = UserState->UserData;
	}
}
