// Fill out your copyright notice in the Description page of Project Settings.

#include "MyActor.h"

AMyActor::AMyActor()
{
	mesh = CreateDefaultSubobject<UProceduralMeshComponent>(TEXT("GeneratedMesh"));
	RootComponent = mesh;
	mesh->bUseAsyncCooking = true;
}

// This is called when actor is spawned (at runtime or when you drop it into the world in editor)
void AMyActor::PostActorCreated()
{
	Super::PostActorCreated();
	CreateWall(-50, 500, 500, 200, 300, 200);
}

// This is called when actor is already in level and map is opened
void AMyActor::PostLoad()
{
	Super::PostLoad();
	CreateWall(-50, 500, 500, 200, 300, 200);
}

void AMyActor::AddTriangle(int32 V1, int32 V2, int32 V3)
{
	Triangles.Add(V1);
	Triangles.Add(V2);
	Triangles.Add(V3);
}

void AMyActor::CreateWall(double width, double height, double length,
	double winHeight, double winLength, double winDist)
{
	width	  = abs(width);
	height	  = abs(height);
	winDist	  = abs(winDist);
	winHeight = abs(winHeight);
	if (winLength > length)
		winLength = length - 10;
	if (winHeight > height)
		winHeight = height - 10;
	if (winDist + winHeight > height) 
		winDist = height - winHeight;

	//Wall vertices
	double xCoord = abs(length) / 2;
	Vertices.Add(FVector(-xCoord, width, 0));
	Vertices.Add(FVector(-xCoord, 0,	 0));
	Vertices.Add(FVector( xCoord, width, 0));
	Vertices.Add(FVector( xCoord, 0,	 0));
	Vertices.Add(FVector(-xCoord, width, height));
	Vertices.Add(FVector(-xCoord, 0,	 height));
	Vertices.Add(FVector( xCoord, width, height));
	Vertices.Add(FVector( xCoord, 0,	 height));

	//Window vertices
	xCoord = abs(winLength) / 2;
	Vertices.Add(FVector(-xCoord, width, winDist));
	Vertices.Add(FVector(-xCoord, 0,	 winDist));
	Vertices.Add(FVector( xCoord, width, winDist));
	Vertices.Add(FVector( xCoord, 0,	 winDist));
	Vertices.Add(FVector(-xCoord, width, winDist + winHeight));
	Vertices.Add(FVector(-xCoord, 0,	 winDist + winHeight));
	Vertices.Add(FVector( xCoord, width, winDist + winHeight));
	Vertices.Add(FVector( xCoord, 0,	 winDist + winHeight));

	//Sides
	AddTriangle(0, 4, 5);
	AddTriangle(5, 1, 0);
	AddTriangle(1, 0, 2);
	AddTriangle(1, 3, 2);
	AddTriangle(2, 3, 7);
	AddTriangle(7, 6, 2);
	AddTriangle(6, 7, 5);
	AddTriangle(5, 4, 6);

	//Window
	AddTriangle(13, 12,  8);
	AddTriangle( 8,  9, 13);
	AddTriangle( 9,  8, 10);
	AddTriangle(10, 11,  9);
	AddTriangle(10, 15, 11);
	AddTriangle(10, 14, 15);
	AddTriangle(14, 13, 15);
	AddTriangle(12, 13, 14);

	//Front
	AddTriangle( 4,  0,  8);
	AddTriangle( 4,  8, 12);
	AddTriangle( 6,  4, 12);
	AddTriangle( 6, 12, 14);
	AddTriangle( 6, 14,  2);
	AddTriangle(14, 10,  2);
	AddTriangle(10,  0,  2);
	AddTriangle( 8,  0, 10);

	//Back
	AddTriangle( 1,  5,  9);
	AddTriangle( 9,  5, 13);
	AddTriangle( 5,  7, 13);
	AddTriangle(13,  7, 15);
	AddTriangle(15,  7,  3);
	AddTriangle(11, 15,  3);
	AddTriangle( 1, 11,  3);
	AddTriangle( 1,  9, 11);

	TArray<FLinearColor> vertexColors;
	vertexColors.Add(FLinearColor(0.75, 0.75, 0.75, 1.0));

	mesh->CreateMeshSection_LinearColor(0, Vertices, Triangles, TArray<FVector>(), TArray<FVector2D>(), vertexColors, TArray<FProcMeshTangent>(), true);

	// Enable collision data
	mesh->ContainsPhysicsTriMeshData(true);
}

