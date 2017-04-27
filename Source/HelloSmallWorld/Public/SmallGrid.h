// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "Engine/StaticMeshActor.h"
#include "SmallGrid.generated.h"

class UInstancedStaticMeshComponent;
class UProperty;
class UStaticMeshComponent;
class AStaticMeshActor;

USTRUCT()
struct FMazeGridRow
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY()
	TArray<AStaticMeshActor*> Columns;

	void AddColumn()
	{
		Columns.Add(nullptr);
	}

	void AddColumn(AStaticMeshActor* StaticMeshActor)
	{
		Columns.Add(StaticMeshActor);
	}

	// Default properties
	FMazeGridRow()
	{

	}
};

USTRUCT()
struct FMazeGrid
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY()
	TArray<FMazeGridRow> Rows;

	void AddRow()
	{
		Rows.Add(FMazeGridRow());
	}

	void inittest()
	{
		
	}

	void AddUninitialized(const int32 NumberOfRows, const int32 NumberOfColumns)
	{
		for (int32 Row = 0; Row < NumberOfRows; ++Row)
		{
			AddRow();
			for (int32 Column = 0; Column < NumberOfColumns; ++Column)
			{
				Rows[Row].AddColumn();
				UE_LOG(LogTemp, Warning, TEXT("Row = %d, Column = %d"), Row, Column);
			}
		}
	}

	void AddInitialized(const int32 NumberOfRows, const int32 NumberOfColumns, AStaticMeshActor* StaticMeshActor)
	{
		for (int32 Row = 0; Row < NumberOfRows; ++Row)
		{
			AddRow();
			for (int32 Column = 0; Column < NumberOfColumns; ++Column)
			{
				Rows[Row].AddColumn(StaticMeshActor);
				UE_LOG(LogTemp, Warning, TEXT("Row = %d, Column = %d"), Row, Column);
			}
		}
	}
	void Clear()
	{
		if (Rows.Num() <= 0) return;

		// Destroy any walls
		const int32 RowTotal = Rows.Num();
		const int32 ColumnTotal = Rows[0].Columns.Num();

		for (int32 v = 0; v < RowTotal; v++)
		{
			for (int32 b = 0; b < ColumnTotal; b++)
			{
				if (Rows[v].Columns[b] && Rows[v].Columns[b]->IsValidLowLevel())
				{
					Rows[v].Columns[b]->Destroy();
				}
			}
		}

		// Empty
		for (int32 v = 0; v < Rows.Num(); v++)
		{
			Rows[v].Columns.Empty();
		}
		Rows.Empty();
	}
	
	// Default properties
	FMazeGrid()
	{

	}
};

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
	void RotateBlock();

protected:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

private:
	//virtual void PostInitializeComponents() override;
	UPROPERTY()
	UStaticMesh* temp1;

	FMazeGrid MazeGrid;

	UPROPERTY(EditAnywhere)
	int Min;

	UPROPERTY(EditAnywhere)
	int Max;

	// The width of the grid
	UPROPERTY(EditAnywhere)
	int width;

	// The height of the grid
	UPROPERTY(EditAnywhere)
	int height;
	
	UPROPERTY(EditAnywhere)
	int tileSize;

	TArray<int> SmallGrid;
	USceneComponent* temp;
	UPROPERTY(EditAnywhere)
	UInstancedStaticMeshComponent* EmptyTiles;

	UPROPERTY(EditAnywhere)
	UInstancedStaticMeshComponent* BlockTiles;

	UStaticMeshComponent *mesh;
};
