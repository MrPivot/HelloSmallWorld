#include "HelloSmallWorld.h"
#include "SmallCharacter.h"

// Sets default values
ASmallCharacter::ASmallCharacter()
{
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void ASmallCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ASmallCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ASmallCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

