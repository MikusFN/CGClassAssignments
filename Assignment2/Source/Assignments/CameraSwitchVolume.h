// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CameraSwitchVolume.generated.h"

// Forward Declarations
class UBoxComponent;
class UTextRenderComponent;

UCLASS()
class ASSIGNMENTS_API ACameraSwitchVolume : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ACameraSwitchVolume();

	// Components
	UBoxComponent* BoxCollision;

	UTextRenderComponent* TextRenderNewCamera;
	UTextRenderComponent*TextRenderPreviousCamera;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Contruction Script
	virtual void OnConstruction(const FTransform& Transform);

	// Properties
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Volume")
		float VolumeWidth = 32.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Volume")
		float VolumeHeight = 32.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Cameras")
		float BlendRate = 0.0f;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Cameras")
		AActor* NewCamera;

	//UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Cameras")
		AActor* PreviousCamera;



	// Overlap Event
	UFUNCTION()
		void OnEndOverlap(class AActor* ThisActor, class AActor* OtherActor);
};
