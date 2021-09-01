#include "GameFramework/Actor.h"
#include "ProceduralMeshComponent.h"
#include "AMyPMesh.generated.h"

UCLASS()
class AMyPMesh : public AActor
{
	GENERATED_BODY()

		UPROPERTY(VisibleAnywhere, Category = "MyPMesh")
		UProceduralMeshComponent* pm;

public:
	AMyPMesh();

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

	virtual void OnConstruction(const FTransform& Transform) override;

	void ClearMeshData();
};