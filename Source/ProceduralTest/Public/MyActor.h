// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ProceduralMeshComponent.h"
#include "MyActor.generated.h"

UCLASS()
class PROCEDURALTEST_API AMyActor : public AActor
{
	GENERATED_BODY()

private:
	UPROPERTY(VisibleAnywhere)
	UProceduralMeshComponent * mesh;
	// The vertices of the mesh
	TArray<FVector> Vertices;
	// The triangles of the mesh
	TArray<int32> Triangles;
	//Creates a triangle that connects the given vertices
	void AddTriangle(int32 V1, int32 V2, int32 V3);
	
public:	
	// Sets default values for this actor's properties
	AMyActor();
	virtual void PostActorCreated();
	virtual void PostLoad();

	void CreateWall(double width, double height, double length, 
					double winHeight, double winLength, double winDist);

};
