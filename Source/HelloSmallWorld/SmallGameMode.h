#pragma once

#include "GameFramework/GameModeBase.h"
#include "SmallGameMode.generated.h"

class ASmallCameraController;

UCLASS()
class HELLOSMALLWORLD_API ASmallGameMode : public AGameModeBase
{
	GENERATED_BODY()
	
    public:
        ASmallGameMode();
};
