// Copyright Epic Games, Inc. All Rights Reserved.

#include "MannyAdventureGameMode.h"
#include "MannyAdventureCharacter.h"
#include "UObject/ConstructorHelpers.h"

AMannyAdventureGameMode::AMannyAdventureGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPerson/Blueprints/BP_ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
