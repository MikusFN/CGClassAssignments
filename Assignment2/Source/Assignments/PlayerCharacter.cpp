// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerCharacter.h"
#include "Engine.h"


// Sets default values
APlayerCharacter::APlayerCharacter()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);

	// set our turn rates for input
	BaseTurnRate = 45.f;
	BaseLookUpRate = 45.f;

	isFPS = false;
	isLocalFPS = isFPS;

	// Don't rotate when the controller rotates. Let that just affect the camera.
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	// Configure character movement
	GetCharacterMovement()->bOrientRotationToMovement = true; // Character moves in the direction of input...	
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 540.0f, 0.0f); // ...at this rotation rate

	// Create a camera boom (pulls in towards the player if there is a collision)
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->AttachTo(RootComponent);

	CameraBoom->bUsePawnControlRotation = true; // Rotate the arm based on the controller

	// Create a follow camera
	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->AttachTo(CameraBoom, USpringArmComponent::SocketName);
	FollowCamera->bUsePawnControlRotation = false; // Camera does not rotate relative to arm
	FollowCamera->SetRelativeLocation(FVector(0.0f, 0.0f, 50.0f + BaseEyeHeight));
	CameraZoomCurrent = 300.f;
	CameraBoom->TargetArmLength = CameraZoomCurrent;

}

// Called when the game starts or when spawned
void APlayerCharacter::BeginPlay()
{
	Super::BeginPlay();
	APlayerController* PlayerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);

}

// Called every frame
void APlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	SwitchCamera();
}

// Called to bind functionality to input
void APlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	// Set up "movement" bindings.
	PlayerInputComponent->BindAxis("MoveForward", this, &APlayerCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &APlayerCharacter::MoveRight);

	// Set up "look" bindings.
	PlayerInputComponent->BindAxis("Turn", this, &APlayerCharacter::HandleYawInput);
	PlayerInputComponent->BindAxis("LookUp", this, &APlayerCharacter::AddControllerPitchInput);
	PlayerInputComponent->BindAction("ChangeCamera", IE_Pressed, this, &APlayerCharacter::OnAction);
}

void APlayerCharacter::OnAction()
{
	isFPS = !isFPS;
}

void APlayerCharacter::MoveForward(float Value)
{
	if (Value == 0.f) return;

	if (!isFPS)
	{
		if (Controller != NULL)
		{
			// find out which way is forward
			const FRotator Rotation = Controller->GetControlRotation();
			const FRotator YawRotation(0, Rotation.Yaw, 0);

			// get forward vector
			const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
			AddMovementInput(Direction, Value);
		}
	}
	else
	{
		AddMovementInput(GetActorForwardVector(), Value);
	}
	LastMovementTime = FApp::GetCurrentTime();
}
void APlayerCharacter::MoveRight(float Value)
{
	if (Value == 0.f) return;

	if (!isFPS)
	{
		if (Controller != NULL)
		{
			// find out which way is right
			const FRotator Rotation = Controller->GetControlRotation();
			const FRotator YawRotation(0, Rotation.Yaw, 0);

			// get right vector
			const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
			// add movement in that direction
			AddMovementInput(Direction, Value);
		}
	}
	else
	{
		AddMovementInput(GetActorRightVector(), Value);

	}
	LastMovementTime = FApp::GetCurrentTime();

}
void APlayerCharacter::HandleYawInput(float turnInput)
{
		if (turnInput != 0.f)
		{
			AddControllerYawInput(turnInput);
			LastMovementTime = FApp::GetCurrentTime();
		}
}

void APlayerCharacter::SwitchCamera()
{
	if (isFPS && isLocalFPS != isFPS)
	{
		APlayerController* PlayerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);
		FViewTargetTransitionParams TransitionParams;

		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::White, "Change Camera Requested to First Person");

		CameraBoom->TargetArmLength = 0.f;
		bUseControllerRotationPitch = true;
		bUseControllerRotationYaw = true;
		bUseControllerRotationRoll = true;

		PlayerController->SetViewTarget(this, TransitionParams);
		isLocalFPS = isFPS;
	}
	else if (!isFPS && isLocalFPS != isFPS)
	{
		APlayerController* PlayerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);
		FViewTargetTransitionParams TransitionParams;

		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::White, "Change Camera Requested to Third Person");

		FollowCamera->AttachTo(CameraBoom, USpringArmComponent::SocketName);
		CameraBoom->TargetArmLength = CameraZoomCurrent;
		bUseControllerRotationPitch = false;
		bUseControllerRotationYaw = false;
		bUseControllerRotationRoll = false;

		PlayerController->SetViewTarget(this, TransitionParams);
		isLocalFPS = isFPS;
	}
}