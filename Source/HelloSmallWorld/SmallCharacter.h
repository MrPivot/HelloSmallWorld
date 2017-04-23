#pragma once

#include "GameFramework/Character.h"
#include "SmallCharacter.generated.h"

class UDecalComponent;

UCLASS()
class HELLOSMALLWORLD_API ASmallCharacter : public ACharacter
{
	GENERATED_BODY()

    public:
        ASmallCharacter();

        void PostInit(int PlayerID);
        void Activate();
        void Deactivate();

        void MoveCursor(const FVector& Position, const FRotator& Rotation);

    private:
        UPROPERTY(VisibleAnywhere)
        UDecalComponent* DebugCursorDecal;

        UMaterial* DecalMaterialP1;
        UMaterial* DecalMaterialP2;
};
