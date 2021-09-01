// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MovableObj.generated.h"

UCLASS()
class ASSIGNMENTS_API AMovableObj : public AActor
{
	GENERATED_BODY()

	UPROPERTY(VisibleAnywhere, Category = "MyComponents")
	UStaticMeshComponent* mesh;

	UPROPERTY(VisibleAnywhere, Category = "MyComponents")
	ACharacter* PlayerCharacter;

private :
	float oldvalueTX = 0.0f;
	float oldvalueTY = 0.0f;
	float oldvalueTZ = 0.0f;

	float oldvalueRX = 0.0f;
	float oldvalueRY = 0.0f;
	float oldvalueRZ = 0.0f;

	float oldvalueSX = 0.0f;
	float oldvalueSY = 0.0f;
	float oldvalueSZ = 0.0f;

public:
	// Sets default values for this actor's properties
	AMovableObj();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	//3D transitions control vars
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Translation")
		int translationX = 0;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Translation")
		int translationY = 0;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Translation")
		int translationZ = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Rotation")
		int RotationX = 0;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Rotation")
		int RotationY = 0;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Rotation")
		int RotationZ = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Scale")
		int ScaleX = 1;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Scale")
		int ScaleY = 1;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Scale")
		int ScaleZ = 1;



	void Matrixmultiply(FMatrix matrix, FVector* vector);
	void Translation(float x, float y, float z);
	void Scale(float x, float y, float z);
	void Rotate(float x, float y, float z);

	void print_v(int turn, float x, float y, float z, float w);

};
