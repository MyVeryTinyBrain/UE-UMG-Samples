// Copyright Epic Games, Inc. All Rights Reserved.


#include "UMGSampleGameModeBase.h"
#include "UserState.h"

AUMGSampleGameModeBase::AUMGSampleGameModeBase()
{
	PlayerStateClass = AUserState::StaticClass();
}
