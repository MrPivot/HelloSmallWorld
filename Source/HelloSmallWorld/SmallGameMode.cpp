#include "HelloSmallWorld.h"
#include "SmallGameMode.h"

#include "SmallCameraPawn.h"
#include "SmallCameraController.h"

ASmallGameMode::ASmallGameMode()
{
    PlayerControllerClass = ASmallCameraController::StaticClass();
    DefaultPawnClass      = ASmallCameraPawn::StaticClass();
}