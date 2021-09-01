// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/SplineComponent.h"
#include "Components/SplineMeshComponent.h"
#include "BezierCurve.generated.h"

UCLASS()
class ASSIGNMENTS_API ABezierCurve : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABezierCurve();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual void OnConstruction(const FTransform& Transform) override;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "General")
		USceneComponent *Root = nullptr;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "General")
		USplineComponent *SplineComponent = nullptr;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "General")
		UStaticMesh *StaticMesh = nullptr;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "General")
		UMaterial *material = nullptr;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "General")
		TEnumAsByte<ESplineMeshAxis::Type> ForwardAxis;

	// Object to move in spline
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "SplineController")
		TSubclassOf<class AActor> ObjectToMoveClass;

	class AActor* ObjectToMove;

	UPROPERTY(EditAnywhere, Category = "SplineController")
		float TotalPathTimeController;

	UPROPERTY(EditAnywhere, Category = "SplineController")
		bool bSplineInLoop;

	

	bool bCanMoveObject;

	float StartTime;

	
};
