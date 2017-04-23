#include "HelloSmallWorld.h"
#include "SmallCharacter.h"

#include "Runtime/Engine/Classes/Components/DecalComponent.h"

ASmallCharacter::ASmallCharacter()
{
	PrimaryActorTick.bCanEverTick = true;

    // Set the skeletal mesh of the player.
    ConstructorHelpers::FObjectFinder<USkeletalMesh> skeletalMesh(TEXT("SkeletalMesh'/Game/Mannequin/Character/Mesh/SK_Mannequin.SK_Mannequin'"));
    GetMesh()->SetSkeletalMesh(skeletalMesh.Object);
    
    // Limit movement to x and y direction.
    GetCharacterMovement()->bConstrainToPlane = true;
    // Rotate character to moving direction.
    GetCharacterMovement()->bOrientRotationToMovement = true;

    // Set up the cursor decal.
    DebugCursorDecal = CreateDefaultSubobject<UDecalComponent>(TEXT("DebugCursorDecal"));
    DebugCursorDecal->SetupAttachment(RootComponent);
    DebugCursorDecal->DecalSize = FVector(16.0f, 32.0f, 32.0f);
    DebugCursorDecal->SetRelativeRotation(FRotator(90.0f, 0.0f, 0.0f).Quaternion());


    ConstructorHelpers::FObjectFinder<UMaterial> decalMaterial1(TEXT("Material'/Game/Material/CursorDecalPlayer1.CursorDecalPlayer1'"));
    DecalMaterialP1 = decalMaterial1.Object;
    ConstructorHelpers::FObjectFinder<UMaterial> decalMaterial2(TEXT("Material'/Game/Material/CursorDecalPlayer2.CursorDecalPlayer2'"));
    DecalMaterialP2 = decalMaterial2.Object;
}


void ASmallCharacter::PostInit(int PlayerID)
{
    switch(PlayerID)
    {
        case 0: {
            DebugCursorDecal->SetDecalMaterial(DecalMaterialP1);
        } break;

        case 1: {
            DebugCursorDecal->SetDecalMaterial(DecalMaterialP2);
        } break;
    }

    DebugCursorDecal->bVisible = false;
}

void ASmallCharacter::Activate()
{
    DebugCursorDecal->bVisible = true;
}

void ASmallCharacter::Deactivate()
{
    DebugCursorDecal->bVisible = false;
}

void ASmallCharacter::MoveCursor(const FVector& Position, const FRotator& Rotation)
{
    DebugCursorDecal->SetWorldLocation(Position);
    DebugCursorDecal->SetWorldRotation(Rotation);
}