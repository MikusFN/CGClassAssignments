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


public:
	// Sets default values for this actor's properties
	AMovableObj();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void Matrixmultiply(FMatrix matrix, FVector* vector);
	void Translation(float x, float y, float z);
	void Scale(float x, float y, float z);
	void Rotate(float x, float y, float z);

	void print_v(int turn, float x, float y, float z, float w);

};
