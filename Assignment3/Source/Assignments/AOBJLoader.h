#pragma once

#include "CoreMinimal.h"
#include "ProceduralMeshComponent.h"
#include "AOBJLoader.generated.h"

USTRUCT()
struct FV
{
	GENERATED_BODY()

	UPROPERTY()
	double x;

	UPROPERTY()
	double y;

	UPROPERTY()
	double z;
};

USTRUCT()
struct FVT
{
	GENERATED_BODY()

	UPROPERTY()
	double u;

	UPROPERTY()
	double v;
};

USTRUCT()
struct FVN
{
	GENERATED_BODY()

	UPROPERTY()
	double nx;

	UPROPERTY()
	double ny;

	UPROPERTY()
	double nz;
};

USTRUCT()
struct FF
{
	GENERATED_BODY()

	UPROPERTY()
	FV v;

	UPROPERTY()
	FVT vt;

	UPROPERTY()
	FVN vn;
};

UCLASS()
class AOBJLoader : public AActor
{
	GENERATED_BODY()

	UPROPERTY(VisibleAnywhere, Category = "OBJLoader") //Category to be removed later
	UProceduralMeshComponent * mesh;

public:
	AOBJLoader();
	
	UPROPERTY()
	TArray<FV> VArray;

	UPROPERTY()
	TArray<FVT> VTArray;

	UPROPERTY()
	TArray<FVN> VNArray;

	UPROPERTY()
	TArray<FF> FArray;

	UPROPERTY()
	TArray<FVector> vertices;
	UPROPERTY()
	TArray<FVector> normals;
	UPROPERTY()
	TArray<int32> triangles;
	UPROPERTY()
	TArray<FVector2D> uvs;
	UPROPERTY()
	TArray<FLinearColor> vertexColors;
	UPROPERTY()
	TArray<FProcMeshTangent> tangents;

	virtual void PostActorCreated() override;
	virtual void PostLoad() override;
	
	TArray<FString> OpenFileDialog();
	void ReadOBJ();
	void CreateFace(TArray<FF> F_Array);
	void ClearMeshData();
};
