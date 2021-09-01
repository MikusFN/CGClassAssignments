// Fill out your copyright notice in the Description page of Project Settings.


#include "Particle.h"

// Sets default values
AParticle::AParticle()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));
	mesh->AttachToComponent(GetRootComponent(), FAttachmentTransformRules::KeepRelativeTransform);
	mesh->SetMaterial(0, (UMaterialInterface*)material);

	//previousPos = currentPos;

	timeAlive = FMath::RandRange(5, 20);
	
	alive = true;
	gravity = true;
}

// Called when the game starts or when spawned
void AParticle::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void AParticle::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

bool AParticle::Collided()
{
	FHitResult* HitResult = new FHitResult();
	FVector Start = currentPos;
	FVector ForwardVector = GetActorForwardVector();
	FVector End = ((ForwardVector * 700.f) + Start);
	FCollisionQueryParams* ColParams = new FCollisionQueryParams();

	return GetWorld()->LineTraceSingleByChannel(*HitResult, Start, End, ECC_Visibility, *ColParams);
}