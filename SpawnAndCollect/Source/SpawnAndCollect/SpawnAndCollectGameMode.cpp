// Copyright Epic Games, Inc. All Rights Reserved.

#include "SpawnAndCollectGameMode.h"
#include "SpawnAndCollectCharacter.h"
#include "UObject/ConstructorHelpers.h"

ASpawnAndCollectGameMode::ASpawnAndCollectGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPerson/Blueprints/BP_ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
