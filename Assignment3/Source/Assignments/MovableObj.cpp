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

	/*if (oldvalueTX != translationX || oldvalueTY != translationY || oldvalueTZ != translationZ)
	{*/
	if (translationX != 0 || translationY != 0 || translationZ != 0)
	{
		Translation(translationX, translationY, translationZ);
		/*oldvalueTX = translationX;
		oldvalueTY = translationY;
		oldvalueTZ = translationZ;*/
	}
	/*if (oldvalueRX != RotationX || oldvalueRY != RotationY || oldvalueRZ != RotationZ)
	{*/
	if (RotationX != 0 || RotationY != 0 || RotationZ != 0)
	{

		Rotate(RotationX, RotationY, RotationZ);
		oldvalueRX = RotationX;
		oldvalueRY = RotationY;
		oldvalueRZ = RotationZ;
	}
	/*if (oldvalueSX != ScaleX || oldvalueSY != ScaleY || oldvalueSZ != ScaleZ)
	{*/
	if (ScaleX != 1 || ScaleY != 1 || ScaleZ != 1)
	{
		Scale(ScaleX, ScaleY, ScaleZ);
		/*oldvalueSX = ScaleX;
		oldvalueSY = ScaleY;
		oldvalueSZ = ScaleZ;*/
	}

	translationX = 0;
	translationY = 0;
	translationZ = 0;
	RotationX = 0;
	RotationY = 0;
	RotationZ = 0;
	ScaleX = 1;
	ScaleY = 1;
	ScaleZ = 1;
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
	FMatrix ScaleM = FMatrix();
	ScaleM.SetIdentity();

	FVector actorScale = GetActorScale();

	ScaleM.M[0][0] = x;
	ScaleM.M[1][1] = y;
	ScaleM.M[2][2] = z;
	ScaleM.M[3][3] = 1;

	Matrixmultiply(ScaleM, &actorScale);

	SetActorScale3D(actorScale);

}
void AMovableObj::Rotate(float x, float y, float z)
{
	//FMatrix RotationMr = FMatrix();
	///*FMatrix RotationMy = FMatrix();
	//FMatrix RotationMz = FMatrix();*/
	//RotationMr.SetIdentity();
	///*RotationMy.SetIdentity();
	//RotationMz.SetIdentity();*/

	//FVector actorLocation = GetActorLocation();

	//Translation(-actorLocation.X, -actorLocation.Y, -actorLocation.Z);

	FRotator actorRotation = GetActorRotation();
	//FVector aux = FVector(0.0f, 10.0f, 10.0f);

		/*RotationMr.M[1][1] = cos(x);
		RotationMr.M[1][2] = -sin(x);
		RotationMr.M[2][1] = sin(x);
		RotationMr.M[2][2] = cos(x);*/

	/*
	RotationMr.M[0][0] = cos(x) * cos(y);
	RotationMr.M[0][1] = (cos(x) * sin(y) * sin(z)) - (sin(x) * cos(z));
	RotationMr.M[0][2] = (cos(x) * sin(y) * cos(z)) + (sin(x) * sin(z));
	RotationMr.M[1][0] = sin(x) * cos(y);
	RotationMr.M[1][1] = (sin(x) * sin(y) * sin(z)) + (cos(x) * cos(z));;
	RotationMr.M[1][2] = (sin(x) * sin(y) * cos(z)) - (cos(x) * sin(z));;
	RotationMr.M[2][0] = -sin(y);
	RotationMr.M[2][1] = cos(y) * sin(z);
	RotationMr.M[2][2] = cos(y) * cos(z);
	*/
	
	/*RotationMr.M[0][0] = cos(x);
	RotationMr.M[0][1] = -sin(x);
	RotationMr.M[1][0] = sin(x);
	RotationMr.M[1][1] = cos(x);*/

	/*FVector aux = actorRotation.Vector();
	Matrixmultiply(RotationMr, &aux);
	actorRotation = aux.Rotation();*/
	
	/*Matrixmultiply(RotationMy, &aux);
	Matrixmultiply(RotationMz, &aux);*/

	//actorRotation = FRotator(aux.X, aux.Y, aux.Z);


	actorRotation = FRotator( actorRotation.Pitch+y, actorRotation.Yaw + x,actorRotation.Roll+z);
	SetActorRotation(actorRotation);

	//Translation(actorLocation.X, actorLocation.Y, actorLocation.Z);

}

void AMovableObj::print_v(int turn, float x, float y, float z, float w) {
	UE_LOG(LogTemp, Warning, TEXT("v: %d (%f, %f, %f, %f)"), turn, x, y, z, w);
}

