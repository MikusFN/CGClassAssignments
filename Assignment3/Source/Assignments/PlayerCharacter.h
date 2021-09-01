// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "PlayerCharacter.generated.h"

UCLASS()
class ASSIGNMENTS_API APlayerCharacter : public ACharacter
{
	GENERATED_BODY()

		/** Camera boom positioning the camera behind the character */
		UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
		class USpringArmComponent* CameraBoom;

	/** Follow camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
		class UCameraComponent* FollowCamera;

	/** Base turn rate, in deg/sec. Other scaling may affect final turn rate. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
		float BaseTurnRate;

	/** Base look up/down rate, in deg/sec. Other scaling may affect final rate. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
		float BaseLookUpRate;



public:
	// Sets default values for this character's properties
	APlayerCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Handles input for moving forward and backward.
	void MoveForward(float Value);

	// Handles input for moving right and left.
	void MoveRight(float Value);


	/** Controls the speed that the camera resets in Third Person Follow mode */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = CameraInternal)
		float CameraZoomCurrent;

	/** Keeps track of when the last movement was */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = CameraInternal)
		float LastMovementTime;

	void HandleYawInput(float turnInput);


public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	void OnAction();

	// Properties
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		bool isFPS;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		bool isLocalFPS;

	void SwitchCamera();

	/** Returns CameraBoom subobject **/
	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }

	/** Returns FollowCamera subobject **/
	FORCEINLINE class UCameraComponent* GetFollowCamera() const { return FollowCamera; }

};
