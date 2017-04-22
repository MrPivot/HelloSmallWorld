#pragma once

#include "GameFramework/Pawn.h"
#include "SmallCameraPawn.generated.h"

UCLASS()
class HELLOSMALLWORLD_API ASmallCameraPawn : public APawn
{
	GENERATED_BODY()

    public:
	    ASmallCameraPawn();

        virtual void Tick(float DeltaTime) override;

        virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

        void MoveForward(float AxisValue);
        void MoveRight(float AxisValue);

    private:
        UPROPERTY(EditAnywhere)
        USpringArmComponent* CameraSpringArm;
        UCameraComponent*    Camera;
        FVector2D            CameraMovementInput;

        UPROPERTY(EditAnywhere)
        float MovementSpeed;
};
