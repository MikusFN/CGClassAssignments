// Fill out your copyright notice in the Description page of Project Settings.


#include "MovableObj.h"
#include <Runtime\Engine\Classes\Kismet\GameplayStatics.h>

// Sets default values
AMovableObj::AMovableObj()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("My mesh"));
	SetActorLocation(FVector(0, 0, 0));
}

// Called when the game starts or when spawned
void AMovableObj::BeginPlay()
{
	Super::BeginPlay();
	PlayerCharacter = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);	
}

// Called every frame
void AMovableObj::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	//Rotate(10.0f, 0.0f,0.0f);

	FRotator actorRot = GetActorRotation();
	actorRot.Yaw += 1.0f;
	SetActorRotation(actorRot);

}

void  AMovableObj::Matrixmultiply(FMatrix matrix, FVector* vector)
{
	float res[4] = { 0 };
	float aux[4] = { 0 };
	aux[0] = vector->X;
	aux[1] = vector->Y;
	aux[2] = vector->Z;
	aux[3] = 1;
	print_v(0, aux[0], aux[1], aux[2], aux[3]);
	int i, k, N = 4;
	for (i = 0; i < N; i++)
	{
		for (k = 0; k < N; k++)
		{
			res[i] += matrix.M[k][i] * aux[k];
		}
	}
	*vector = FVector(res[0], res[1], res[2]);
}


void AMovableObj::Translation(float x, float y, float z)
{	
	FMatrix TranslationM = FMatrix();
	TranslationM.SetIdentity();

	FVector actorLocation = GetActorLocation();

	TranslationM.M[3][0] = x;
	TranslationM.M[3][1] = y;
	TranslationM.M[3][2] = z;
	TranslationM.M[3][3] = 1;

	Matrixmultiply(TranslationM, &actorLocation);
	
	SetActorLocation(actorLocation, false);

}
void AMovableObj::Scale(float x, float y, float z)
{
	FMatrix TranslationM = FMatrix();
	TranslationM.SetIdentity();

	FVector actorLocation = GetActorLocation();
}
void AMovableObj::Rotate(float x, float y, float z)
{
	FMatrix RotationMx = FMatrix();
	FMatrix RotationMy = FMatrix();
	FMatrix RotationMz = FMatrix();
	RotationMx.SetIdentity();
	RotationMy.SetIdentity();
	RotationMz.SetIdentity();

	FVector actorLocation = GetActorLocation();

	Translation(-actorLocation.X, -actorLocation.Y, -actorLocation.Z);

	FRotator actorRotation = GetActorRotation();
	FVector aux = FVector(actorRotation.Yaw, actorRotation.Pitch, actorRotation.Roll);
	
	RotationMx.M[1][1] = cos(x);
	RotationMx.M[1][2] = -sin(x);
	RotationMx.M[2][1] = sin(x);
	RotationMx.M[2][2] = cos(x);

	RotationMy.M[0][0] = cos(y);
	RotationMy.M[0][2] = sin(y);
	RotationMy.M[2][0] = -sin(y);
	RotationMy.M[2][2] = cos(y);

	RotationMz.M[0][0] = cos(z);
	RotationMz.M[0][1] = -sin(z);
	RotationMz.M[1][0] = sin(z);
	RotationMz.M[1][1] = cos(z);

	Matrixmultiply(RotationMx, &aux);
	Matrixmultiply(RotationMy, &aux);
	Matrixmultiply(RotationMz, &aux);

	actorRotation = FRotator(aux.X, aux.Y, aux.Z);
	
	SetActorRotation(actorRotation);

	Translation(actorLocation.X, actorLocation.Y, actorLocation.Z);

}

void AMovableObj::print_v(int turn, float x, float y, float z, float w ) {
	UE_LOG(LogTemp, Warning, TEXT("v: %d (%f, %f, %f, %f)"),turn, x, y, z, w);
}

