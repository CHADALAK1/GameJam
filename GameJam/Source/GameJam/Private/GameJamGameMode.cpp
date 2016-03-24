// Copyright 1998-2015 Epic Games, Inc. All Rights Reserved.

#include "GameJam.h"
#include "GameJamGameMode.h"
#include "GameJamPlayerController.h"
#include "GameJamCharacter.h"

AGameJamGameMode::AGameJamGameMode()
{
	// use our custom PlayerController class
	PlayerControllerClass = AGameJamPlayerController::StaticClass();

	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/TopDownCPP/Blueprints/TopDownCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}