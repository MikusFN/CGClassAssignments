// Fill out your copyright notice in the Description page of Project Settings.


#include "BezierCurve.h"

FVector CalculateBezierPoint(float t, FVector p0, FVector p1, FVector p2, FVector p3);

// Sets default values
ABezierCurve::ABezierCurve()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Root = CreateDefaultSubobject<USceneComponent>(FName(TEXT("Root")));
	RootComponent = Root;

	SplineComponent = CreateDefaultSubobject<USplineComponent>(FName(TEXT("Spline")));
	SplineComponent->SetupAttachment(Root);
	SplineComponent->bDrawDebug = true;
}

// Called when the game starts or when spawned
void ABezierCurve::BeginPlay()
{
	Super::BeginPlay();
	
	if (ObjectToMoveClass != nullptr) {
		ObjectToMove = GetWorld()->SpawnActor<AActor>(ObjectToMoveClass, SplineComponent->GetComponentTransform());

		if (ObjectToMove != nullptr) {
			StartTime = GetWorld()->GetTimeSeconds(); // seconds since play was pressed
			bCanMoveObject = true;
		}
	}
}

// Called every frame
void ABezierCurve::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if ((ObjectToMove != nullptr) && (bCanMoveObject)) {
		float CurrentSplineTime = (GetWorld()->GetTimeSeconds() - StartTime) / TotalPathTimeController;
		float distance = SplineComponent->GetSplineLength() * CurrentSplineTime;

		FVector Pos = SplineComponent->GetLocationAtDistanceAlongSpline(distance, ESplineCoordinateSpace::World);
		ObjectToMove->SetActorLocation(Pos);

		FVector Direction = SplineComponent->GetDirectionAtDistanceAlongSpline(distance, ESplineCoordinateSpace::World);
		FRotator rotator = FRotationMatrix::MakeFromX(Direction).Rotator();
		ObjectToMove->SetActorRotation(rotator);

		if (CurrentSplineTime >= 1.0f) {
			if (bSplineInLoop) {
				bCanMoveObject = true;
				StartTime = GetWorld()->GetTimeSeconds();
				CurrentSplineTime = (GetWorld()->GetTimeSeconds() - StartTime) / TotalPathTimeController;
			}
		}

	}

}

void ABezierCurve::OnConstruction(const FTransform & Transform)
{
	USplineMeshComponent *SplineMesh = NewObject<USplineMeshComponent>(this);
	SplineMesh->RegisterComponent();
	SplineMesh->CreationMethod = EComponentCreationMethod::UserConstructionScript;
	SplineMesh->SetMobility(EComponentMobility::Movable);
	SplineMesh->SetStaticMesh(StaticMesh);
	SplineMesh->SetMaterial(0, material);
	SplineMesh->SetForwardAxis(ForwardAxis);
	SplineMesh->AttachToComponent(SplineComponent, FAttachmentTransformRules::KeepRelativeTransform);

	TArray<FVector> points;
	points.Add(FVector(0.0f, 0.0f, 0.0f));
	points.Add(FVector(50.0f, 0.0f, 50.0f));
	points.Add(FVector(100.0f, 0.0f, 50.0f));
	points.Add(FVector(150.0f, 0.0f, 0.0f));
	//SplineComponent->SetSplinePoints(points, ESplineCoordinateSpace::World, true);
	//SplineComponent->bSplineHasBeenEdited = true;

	/*
	FVector StartPos, StartTangent, EndPos, EndTangent;
	SplineComponent->GetLocalLocationAndTangentAtSplinePoint(i, StartPos, StartTangent);
	SplineComponent->GetLocalLocationAndTangentAtSplinePoint(i + 1, EndPos, EndTangent);
	*/

	FVector P0 = SplineComponent->GetLocationAtSplinePoint(0, ESplineCoordinateSpace::Type::Local);
	FVector P1 = SplineComponent->GetLocationAtSplinePoint(1, ESplineCoordinateSpace::Type::Local);
	FVector P2 = SplineComponent->GetLocationAtSplinePoint(2, ESplineCoordinateSpace::Type::Local);
	FVector P3 = SplineComponent->GetLocationAtSplinePoint(3, ESplineCoordinateSpace::Type::Local);
	UE_LOG(LogTemp, Warning, TEXT("NumberPoints: %d"), SplineComponent->GetNumberOfSplinePoints());

	//UE_LOG(LogTemp, Warning, TEXT("StartPos: %s"), *StartPos.ToCompactString());
	//UE_LOG(LogTemp, Warning, TEXT("EndPos: %s"), *EndPos.ToCompactString());

	float t = 0 / (float)SplineComponent->GetNumberOfSplinePoints();
	FVector PosB = CalculateBezierPoint(t, P0, P1, P2, P3);

	SplineMesh->SetStartPosition(PosB);
	//SplineMesh->SetStartAndEnd(StartPos, StartTangent, EndPos, EndTangent);

	RegisterAllComponents();
}

FVector CalculateBezierPoint(float t, FVector p0, FVector p1, FVector p2, FVector p3) 
{
	float tt = t * t;
	float ttt = tt * t;

	return (((1 - t) * (1 - t) * (1 - t)) * p0) + (3 * t * ((1 - t) * (1 - t)) * p1) + (3 * tt* (1 - t) * p2) + ttt*p3;
}
