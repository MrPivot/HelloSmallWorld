#pragma once

#include "GameFramework/PlayerController.h"
#include "SmallCameraController.generated.h"

#define PLAYER_COUNT 2

class ASmallCharacter;

UCLASS()
class HELLOSMALLWORLD_API ASmallCameraController : public APlayerController
{
	GENERATED_BODY()

    public:
        ASmallCameraController();

        virtual void BeginPlay() override;
        virtual void Tick(float DeltaTime) override;

        void NextTurn();

    private:
        UPROPERTY(EditAnywhere)
        FVector2D StartPositions[PLAYER_COUNT];
        ASmallCharacter* Players[PLAYER_COUNT];
        
        UPROPERTY(VisibleAnywhere)
        int CurrentPlayer;
};
