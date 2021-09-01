// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Particle.h"
#include "Engine/World.h"
#include "Particle_System.generated.h"

UCLASS()
class ASSIGNMENTS_API AParticle_System : public AActor
{
	GENERATED_BODY()
	
	//UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	//	class AParticle* prt;
	
public:	
	// Sets default values for this actor's properties
	AParticle_System();

	UPROPERTY()
	TArray<AParticle*> listPrt;

	int nrParticulas;

	UPROPERTY()
		int nrPrtMin;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Particles")
		int nrPrtMax;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Material")
		UMaterial* material = nullptr;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "mesh")
		UStaticMeshComponent* mesh;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "ForceStrength")
		float ForceStrength;

	void CreateParticles(int nrPart);
	void KillParticles(int nrPart);
	void UpdateParticles();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
