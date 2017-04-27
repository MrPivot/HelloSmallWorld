// Fill out your copyright notice in the Description page of Project Settings.

#include "HelloSmallWorld.h"
#include "SmallGrid.h"

#include <EngineGlobals.h>
#include <Runtime/Engine/Classes/Engine/Engine.h>

#include "Components/InstancedStaticMeshComponent.h"

// Sets default values
ASmallGrid::ASmallGrid() : width(10), height(10), tileSize(225), Min(0), Max(1)
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	const ConstructorHelpers::FObjectFinder<UStaticMesh> CubeMesh(TEXT("StaticMesh'/Game/SM_MERGED_Shape_Cube_59.SM_MERGED_Shape_Cube_59'"));
	const ConstructorHelpers::FObjectFinder<UStaticMesh> PlaneMesh(TEXT("StaticMesh'/Game/SM_MERGED_Shape_Plane_56.SM_MERGED_Shape_Plane_56'"));
	temp1 = CubeMesh.Object;
	//AStaticMeshActor* temp = ;

	

	
	MazeGrid.AddUninitialized(4, 4);









	//SmallGrid.Reserve(width * height);
	//temp = CreateDefaultSubobject<USceneComponent>(TEXT("temp"));
	//RootComponent = temp;
	//EmptyTiles = CreateDefaultSubobject<UInstancedStaticMeshComponent>(TEXT("PLANE"));
	//EmptyTiles->AttachToComponent(temp, FAttachmentTransformRules::SnapToTargetNotIncludingScale);
	//BlockTiles = CreateDefaultSubobject<UInstancedStaticMeshComponent>(TEXT("CUBE"));
	//BlockTiles->AttachToComponent(temp, FAttachmentTransformRules::SnapToTargetNotIncludingScale);

	//EmptyTiles->SetStaticMesh(PlaneMesh.Object);
	//BlockTiles->SetStaticMesh(CubeMesh.Object);
	//RootComponent = grid;
}

void ASmallGrid::CreateGrid()
{
	//MazeGrid.inittest();
	/*FVector Location(0.0f, 0.0f, 0.0f);
	FRotator Rotation(0.0f, 0.0f, 0.0f);
	FActorSpawnParameters SpawnInfo;
	AStaticMeshActor* actor = GetWorld()->SpawnActor<AStaticMeshActor>(Location, Rotation, SpawnInfo);
	actor->GetStaticMeshComponent()->SetStaticMesh(temp1);*/
	for (int32 r = 0; r < MazeGrid.Rows.Num(); ++r)
	{
		for (int32 c = 0; c < MazeGrid.Rows[r].Columns.Num(); ++c)
		{
			FVector Location(r * 240, c * 240, 0.0f);
			FRotator Rotation(0.0f, 0.0f, 0.0f);
			FActorSpawnParameters SpawnInfo;
			AStaticMeshActor* actor = GetWorld()->SpawnActor<AStaticMeshActor>(Location, Rotation, SpawnInfo);
			actor->GetStaticMeshComponent()->SetStaticMesh(temp1);
			MazeGrid.Rows[r].Columns[c] = actor;
		}
	}



	//for (int i = 0; i < width; ++i)
	//{
	//	for (int j = 0; j < height; ++j)
	//	{
	//		int rand = FMath::RandRange(Min, Max);
	//		//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("Random = %d"), rand));
	//		//UE_LOG(LogTemp, Warning, TEXT("Rand = %d"), rand);
	//		switch (rand)
	//		{
	//		case 0:
	//			SmallGrid.Add(EmptyTiles->AddInstance(FTransform(FVector(i * tileSize, j * tileSize, 0))));
	//			break;
	//		case 1:
	//			SmallGrid.Add(BlockTiles->AddInstance(FTransform(FVector(i * tileSize, j * tileSize, 0))));
	//			break;
	//		default:
	//			UE_LOG(LogTemp, Warning, TEXT("WHAT NO MUNEY?!"));
	//		}
	//	}
	//}
}

void ASmallGrid::RotateBlock()
{
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("Selected!")));
}

//void ASmallGrid::OnClicked(UPrimitive* )

void ASmallGrid::DestroyGrid()
{
	EmptyTiles->ClearInstances();
	BlockTiles->ClearInstances();
}

// Called when the game starts or when spawned
void ASmallGrid::BeginPlay()
{
	Super::BeginPlay();
	CreateGrid();
}

// Called every frame
void ASmallGrid::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

#if WITH_EDITOR  
void ASmallGrid::PreEditChange(UProperty * PropertyAboutToChange)
{
	// Get the name of the property that was changed  
	FName PropertyName = (PropertyAboutToChange != nullptr) ? PropertyAboutToChange->GetFName() : NAME_None;

	// We test using GET_MEMBER_NAME_CHECKED so that if someone changes the property name  
	// in the future this will fail to compile and we can update it.  
	if ((PropertyName == GET_MEMBER_NAME_CHECKED(ASmallGrid, width)) ||
		(PropertyName == GET_MEMBER_NAME_CHECKED(ASmallGrid, height)) ||
		(PropertyName == GET_MEMBER_NAME_CHECKED(ASmallGrid, tileSize)))
	{
		UE_LOG(LogTemp, Warning, TEXT("DID THIS WORK?!"));
		DestroyGrid();
		//CreateGrid();
	}

	// Call the base class version  
	Super::PreEditChange(PropertyAboutToChange);
}
#endif

#if WITH_EDITOR  
void ASmallGrid::PostEditChangeProperty(struct FPropertyChangedEvent& PropertyChangedEvent)
{
	// Get the name of the property that was changed  
	FName PropertyName = (PropertyChangedEvent.Property != nullptr) ? PropertyChangedEvent.Property->GetFName() : NAME_None;

	// We test using GET_MEMBER_NAME_CHECKED so that if someone changes the property name  
	// in the future this will fail to compile and we can update it.  
	if ((PropertyName == GET_MEMBER_NAME_CHECKED(ASmallGrid, width))  ||
		(PropertyName == GET_MEMBER_NAME_CHECKED(ASmallGrid, height)) || 
		(PropertyName == GET_MEMBER_NAME_CHECKED(ASmallGrid, tileSize)))
	{
		//UE_LOG(LogTemp, Warning, TEXT("DID THIS WORK?!"));
		//DestroyGrid();
		CreateGrid();
	}

	// Call the base class version  
	Super::PostEditChangeProperty(PropertyChangedEvent);
}
#endif

//void ASmallGrid::PostInitializeComponents()
//{
//	Super::PostInitializeComponents();
//	RootComponent->SetWorldLocation(FVector(0, 0, 0));
//}
