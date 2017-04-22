#include "HelloSmallWorld.h"
#include "SmallCameraPawn.h"


ASmallCameraPawn::ASmallCameraPawn() :
    MovementSpeed(1000.0f)
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

    RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));

    CameraSpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraSpringArm"));
    CameraSpringArm->SetupAttachment(RootComponent);
    CameraSpringArm->SetRelativeLocationAndRotation(FVector(0.0f, 0.0f, 50.0f), FRotator(-60.0f, 0.0f, 0.0f));
    CameraSpringArm->TargetArmLength  = 1000.0f;
    CameraSpringArm->bEnableCameraLag = true;
    CameraSpringArm->CameraLagSpeed   = 2.5f;

    Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
    Camera->SetupAttachment(CameraSpringArm, USpringArmComponent::SocketName);
}

void ASmallCameraPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

    if(!CameraMovementInput.IsZero())
    {
        FVector NewLocation = GetActorLocation();
        NewLocation += GetActorForwardVector() * CameraMovementInput.X * DeltaTime * MovementSpeed;
        NewLocation += GetActorRightVector() * CameraMovementInput.Y * DeltaTime * MovementSpeed;
        SetActorLocation(NewLocation);
    }
}

void ASmallCameraPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

    InputComponent->BindAxis("MoveForward", this, &ASmallCameraPawn::MoveForward);
    InputComponent->BindAxis("MoveRight", this, &ASmallCameraPawn::MoveRight);
}

void ASmallCameraPawn::MoveForward(float AxisValue)
{
    CameraMovementInput.X = AxisValue;
}

void ASmallCameraPawn::MoveRight(float AxisValue)
{
    CameraMovementInput.Y = AxisValue;
}

