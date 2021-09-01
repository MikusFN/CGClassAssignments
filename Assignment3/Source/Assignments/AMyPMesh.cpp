// Fill out your copyright notice in the Description page of Project Settings.


#include "AMyPMesh.h"

// Sets default values
AMyPMesh::AMyPMesh()
{
	PrimaryActorTick.bCanEverTick = true;

	pm = CreateDefaultSubobject<UProceduralMeshComponent>(TEXT("ProceduralMesh"));
	pm->AttachToComponent(GetRootComponent(), FAttachmentTransformRules::KeepRelativeTransform);

}
void AMyPMesh::OnConstruction(const FTransform& Transform)
{
	vertices.Add(FVector(0.0f, 0.0f, 0.0f));
	vertices.Add(FVector(100.0f, 0.0f, 0.0f));
	vertices.Add(FVector(0.0f, 100.0f, 0.0f));

	triangles.Add(0);
	triangles.Add(2);
	triangles.Add(1);

	// uvs.Init(FVector2D(0.0f, 0.0f), 3);
	uvs.Add(FVector2D(0.0f, 0.0f));
	uvs.Add(FVector2D(1.0f, 0.0f));
	uvs.Add(FVector2D(0.0f, 1.0f));

	normals.Init(FVector(0.0f, 0.0f, 1.0f), 3);
	vertexColors.Init(FLinearColor(0.0f, 0.0f, 0.0f, 1.0f), 3);
	tangents.Init(FProcMeshTangent(1.0f, 0.0f, 0.0f), 3);

	//Function that creates mesh section
	pm->CreateMeshSection_LinearColor(0, vertices, triangles, normals, uvs, vertexColors, tangents, false);
}
void AMyPMesh::ClearMeshData()
{
	vertices.Empty();
	triangles.Empty();
	uvs.Empty();
	normals.Empty();
	vertexColors.Empty();
	tangents.Empty();
}
// // Called when the game starts or when spawned
// void AMyPMesh::BeginPlay()
// {
	// Super::BeginPlay();

// }

// // Called every frame
// void AMyPMesh::Tick(float DeltaTime)
// {
	// Super::Tick(DeltaTime);

// }
