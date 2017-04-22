// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "SmallGrid.generated.h"

class UInstancedStaticMeshComponent;
class UProperty;
class UStaticMeshComponent;

UCLASS()
class HELLOSMALLWORLD_API ASmallGrid : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASmallGrid();
	void PreEditChange(UProperty * PropertyAboutToChange);
	void PostEditChangeProperty(struct FPropertyChangedEvent& PropertyChangedEvent) override;
	void CreateGrid();
	void DestroyGrid();

protected:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

private:
	//virtual void PostInitializeComponents() override;

	// The width of the grid
	UPROPERTY(EditAnywhere)
	int width;

	// The height of the grid
	UPROPERTY(EditAnywhere)
	int height;
	
	UPROPERTY(EditAnywhere)
	int tileSize;

	UPROPERTY(EditAnywhere)
	UInstancedStaticMeshComponent *grid;

	UStaticMeshComponent *mesh;
};
