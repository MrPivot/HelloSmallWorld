// Fill out your copyright notice in the Description page of Project Settings.

#include "HelloSmallWorld.h"
#include "SmallGrid.h"

#include "Components/InstancedStaticMeshComponent.h"

// Sets default values
ASmallGrid::ASmallGrid() : width(10), height(10), tileSize(100)
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	grid = CreateDefaultSubobject<UInstancedStaticMeshComponent>(TEXT("Grid"));
	RootComponent = grid;
	const ConstructorHelpers::FObjectFinder<UStaticMesh> Mesh(TEXT("/Game/Geometry/Meshes/1M_Cube"));
	grid->SetStaticMesh(Mesh.Object);
}

void ASmallGrid::CreateGrid()
{
	for (int i = 0; i < width; ++i)
	{
		for (int j = 0; j < height; ++j)
		{
			grid->AddInstance(FTransform(FVector(i * tileSize, j * tileSize, 0)));
		}
	}
}

void ASmallGrid::DestroyGrid()
{
	for (int i = width * height - 1; i >= 0; --i)
	{
		grid->RemoveInstance(i);
	}
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
