// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.

#include "HelloSmallWorld.h"
#include "HelloSmallWorldGameMode.h"
#include "HelloSmallWorldPlayerController.h"
#include "HelloSmallWorldCharacter.h"

AHelloSmallWorldGameMode::AHelloSmallWorldGameMode()
{
	// use our custom PlayerController class
	PlayerControllerClass = AHelloSmallWorldPlayerController::StaticClass();

	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/TopDownCPP/Blueprints/TopDownCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}