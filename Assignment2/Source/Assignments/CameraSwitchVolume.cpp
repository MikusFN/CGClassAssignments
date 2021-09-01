// Fill out your copyright notice in the Description page of Project Settings.


#include "CameraSwitchVolume.h"
#include "Components/BoxComponent.h"
#include "Components/TextRenderComponent.h"
#include "GameFramework/Character.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
ACameraSwitchVolume::ACameraSwitchVolume()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Box Collision
	BoxCollision = CreateDefaultSubobject<UBoxComponent>(TEXT("Box Collision"));
	RootComponent = BoxCollision;
	BoxCollision->SetBoxExtent(FVector(1.5f, 32.0f, 32.0f));

	// Setup Text Renders
	TextRenderNewCamera = CreateDefaultSubobject<UTextRenderComponent>(TEXT("Text Render New Camera"));
	TextRenderNewCamera->SetupAttachment(RootComponent);
	TextRenderNewCamera->SetText("New Camera Side");
	TextRenderNewCamera->SetHiddenInGame(true);
	TextRenderNewCamera->SetRelativeLocation(FVector(15.0f, 0.0f, 0.0f));
	TextRenderNewCamera->SetHorizontalAlignment(EHTA_Center);
	TextRenderNewCamera->SetVerticalAlignment(EVRTA_TextCenter);

	TextRenderPreviousCamera = CreateDefaultSubobject<UTextRenderComponent>(TEXT("Text Render Previous Camera"));
	TextRenderPreviousCamera->SetupAttachment(RootComponent);
	TextRenderPreviousCamera->SetText("Previous Camera Side");
	TextRenderPreviousCamera->SetHiddenInGame(true);
	TextRenderPreviousCamera->SetRelativeLocation(FVector(-15.0f, 0.0f, 0.0f));
	TextRenderPreviousCamera->SetRelativeRotation(FRotator(0.0f, 180.0f, 0.0f));
	TextRenderPreviousCamera->SetHorizontalAlignment(EHTA_Center);
	TextRenderPreviousCamera->SetVerticalAlignment(EVRTA_TextCenter);

}

// Called when the game starts or when spawned
void ACameraSwitchVolume::BeginPlay()
{
	Super::BeginPlay();

	APlayerController* PlayerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	PreviousCamera = PlayerController->GetViewTarget();
		
	// Bind Overlap Event
	OnActorEndOverlap.AddDynamic(this, &ACameraSwitchVolume::OnEndOverlap);
}

// Called every frame
void ACameraSwitchVolume::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}


// Construction Script
void ACameraSwitchVolume::OnConstruction(const FTransform & Transform)
{
	BoxCollision->SetBoxExtent(FVector(1.5f, VolumeWidth, VolumeHeight));

}

void ACameraSwitchVolume::OnEndOverlap(AActor * ThisActor, AActor * OtherActor)
{
	ACharacter* PlayerCharacter = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);
	APlayerController* PlayerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);

	FViewTargetTransitionParams TransitionParams;

	// Toggle camera based on players x relative location


	if (PlayerCharacter && OtherActor == PlayerCharacter && PlayerController) {
		FVector PlayerRelativeLocation = GetTransform().InverseTransformPosition(PlayerCharacter->GetActorLocation());

		// If player exists new camera side
		if (NewCamera && PlayerRelativeLocation.X > 0) {
			PlayerController->SetViewTargetWithBlend(NewCamera, BlendRate);
		}
		
		// If player exits previous camera side
		if (PreviousCamera && PlayerRelativeLocation.X < 0) {
			PlayerController->SetViewTarget(PreviousCamera, TransitionParams);
		}

	}
}

