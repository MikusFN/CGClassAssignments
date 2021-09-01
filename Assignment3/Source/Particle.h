// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Math/UnrealMathUtility.h"
#include "Components/StaticMeshComponent.h"
#include "Engine/World.h"
#include "Particle.generated.h"

UCLASS()
class ASSIGNMENTS_API AParticle : public AActor
{
	GENERATED_BODY()

	//UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	//	class UAParticle* prt;

	//class UChildActorComponent* prt;
public:
	// Sets default values for this actor's properties
	AParticle();
	//FORCEINLINE class UStaticMeshComponent* GetMesh() const {return mesh};
	//class UMyActorMovementComponent* OurMovementComponent;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "mesh")
		UStaticMeshComponent* mesh;
	UPROPERTY()
		FVector currentPos;
	UPROPERTY()
		FVector previousPos;
	UPROPERTY()
		float velocity;
	UPROPERTY()
		int timeAlive;
	UPROPERTY()
		TArray<FLinearColor> color;
	UPROPERTY()
		bool alive;
	UPROPERTY()
		bool gravity;
	UPROPERTY()
	UMaterial* material = nullptr;
	
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	
	bool Collided();
};