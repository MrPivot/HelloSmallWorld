#include "HelloSmallWorld.h"
#include "SmallCameraPawn.h"

ASmallCameraPawn::ASmallCameraPawn() :
    MovementSpeed(1000.0f),
    ZoomSpeed(100.0f),
    CameraZoomInput(0)
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
        FVector newLocation = GetActorLocation();
        newLocation += GetActorForwardVector() * CameraMovementInput.X * DeltaTime * MovementSpeed;
        newLocation += GetActorRightVector() * CameraMovementInput.Y * DeltaTime * MovementSpeed;
        SetActorLocation(newLocation);
    }

    if(CameraZoomInput != 0)
    {
        CameraSpringArm->TargetArmLength += CameraZoomInput * ZoomSpeed;
        CameraZoomInput = 0;
    }
}

void ASmallCameraPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

    InputComponent->BindAction("ZoomIn", EInputEvent::IE_Pressed, this, &ASmallCameraPawn::ZoomIn);
    InputComponent->BindAction("ZoomOut", EInputEvent::IE_Pressed, this, &ASmallCameraPawn::ZoomOut);

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

void ASmallCameraPawn::ZoomIn()
{
    CameraZoomInput = -1;
}

void ASmallCameraPawn::ZoomOut()
{
    CameraZoomInput = 1;
}