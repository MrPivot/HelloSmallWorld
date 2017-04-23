#include "HelloSmallWorld.h"
#include "SmallCameraController.h"

#include "SmallCharacter.h"

ASmallCameraController::ASmallCameraController() :
    CurrentPlayer(0)
{
    // Disable automatic swapping of used camera.
    bAutoManageActiveCameraTarget = false;
    
    bShowMouseCursor   = true;
    DefaultMouseCursor = EMouseCursor::GrabHand;
}

void ASmallCameraController::BeginPlay()
{
    Super::BeginPlay();

    SetViewTarget(GetPawn());

    FActorSpawnParameters spawnInfo;
    spawnInfo.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

    // Spawn the players.
    for(int i = 0; i < PLAYER_COUNT; ++i)
    {
        Players[i] = GWorld->SpawnActor<ASmallCharacter>(ASmallCharacter::StaticClass(), FVector(StartPositions[i].X, StartPositions[i].Y, 0.0f), FRotator::ZeroRotator, spawnInfo);

        Players[i]->PostInit(i);

        if(Players[i] == nullptr)
        {
            UE_LOG(LogTemp, Warning, TEXT("Failed to create character."))
        }
    }

    Players[CurrentPlayer]->Activate();
}

void ASmallCameraController::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    FHitResult hitResult;
    GetHitResultUnderCursor(ECC_Visibility, true, hitResult);
    
    Players[CurrentPlayer]->MoveCursor(hitResult.Location, hitResult.ImpactNormal.Rotation());
}

void ASmallCameraController::SetupInputComponent()
{
    Super::SetupInputComponent();

    InputComponent->BindAction("Select", EInputEvent::IE_Pressed, this, &ASmallCameraController::Select);
}

void ASmallCameraController::Select()
{
    FHitResult hitResult;
    GetHitResultUnderCursor(ECC_Visibility, true, hitResult);

    Players[CurrentPlayer]->SetActorLocation(hitResult.Location);
}

void ASmallCameraController::NextTurn()
{
    Players[CurrentPlayer]->Deactivate();

    CurrentPlayer += 1;

    if(CurrentPlayer >= PLAYER_COUNT)
    {
        CurrentPlayer = 0;
    }

    Players[CurrentPlayer]->Activate();
}
