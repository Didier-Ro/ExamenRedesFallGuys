// Copyright Epic Games, Inc. All Rights Reserved.

#include "ExamenRedesGameMode.h"
#include "ExamenRedesCharacter.h"
#include "UObject/ConstructorHelpers.h"

AExamenRedesGameMode::AExamenRedesGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPerson/Blueprints/BP_ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
