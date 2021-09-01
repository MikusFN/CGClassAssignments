// Fill out your copyright notice in the Description page of Project Settings.


#include "Particle_System.h"

// Sets default values
AParticle_System::AParticle_System()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	nrParticulas = 0;
	mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));
	mesh->AttachToComponent(GetRootComponent(), FAttachmentTransformRules::KeepRelativeTransform);
	mesh->SetMaterial(0, (UMaterialInterface*)material);
	ForceStrength = 700.f;

}

// Called when the game starts or when spawned
void AParticle_System::BeginPlay()
{
	Super::BeginPlay();
	CreateParticles(nrPrtMax);
}

// Called every frame
void AParticle_System::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	UpdateParticles();

	FVector Up = mesh->GetUpVector();
	mesh->AddForce(Up * ForceStrength * mesh->GetMass());
}



void AParticle_System::CreateParticles(int nrPart)
{
	for (int i = 0; i < nrPart; i++)
	{
		//AParticle prt = CreateDefaultSubobject<AParticle>(TEXT("Particle"));
		//UChildActorComponent prt = CreateDefaultSubobject<UChildActorComponent>(TEXT("PRT"));
		AParticle* prt = GetWorld()->SpawnActor<AParticle>(AParticle::StaticClass(), GetActorLocation(), FRotator::ZeroRotator);
		prt->currentPos = GetActorLocation();
		prt->material = material;
		listPrt.Add(prt);
		nrParticulas++;
	}
}

void AParticle_System::KillParticles(int nrPart)
{
	/*for (int32 i = 0; i != listPrt.Num(); i++)
	{
		if(listPrt.prt)
		listPrt[i]
	}*/

	for (const auto& prt : listPrt)
	{
		if (prt->alive == false)
		{
			listPrt.Remove(prt);
			nrParticulas--;
		}

	}
}


void AParticle_System::UpdateParticles()
{
	//KillParticles();

	for (auto& prt : listPrt)
	{
		if (prt->timeAlive < 0|| prt->Collided())
		{
			prt->alive = false;
		}
		else
		{
			prt->timeAlive -= 2.0f;
		}

	}
	if (nrParticulas < nrPrtMin)
	{
		CreateParticles(nrPrtMin);
	}
}