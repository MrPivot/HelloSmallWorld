#include "HelloSmallWorld.h"
#include "SmallCameraController.h"

#include "SmallCharacter.h"


ASmallCameraController::ASmallCameraController()
{
    // Disable automatic swapping of used camera.
    bAutoManageActiveCameraTarget = false;
}


void ASmallCameraController::BeginPlay()
{
    SetViewTarget(GetPawn());
}
