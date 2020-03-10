// Copyright Frank Severijns 2020
// Based on the tutorial https://docs.unrealengine.com/en-US/Programming/Tutorials/FirstPersonShooter/2/

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Controller.h"
#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Components/InputComponent.h"
#include "FPSCharacter.generated.h"

UCLASS()
class DUNGEONESCAPE_API AFPSCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AFPSCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Move the character forward or back
	UFUNCTION()
	void MoveForward(float Axis);

	// Move the character right or left
	UFUNCTION()
	void MoveRight(float Axis);

	// Rotate the viewpoint along its Pitch (up and down)
	UFUNCTION()
	void LookVertical(float Axis);

	// Rotate the viewpoint along its Yaw (left and right)
	UFUNCTION()
	void LookHorizontal(float Axis);

	// Make the character jump by setting the jump pressed flag to true
	UFUNCTION()
	void StartJump();

	// Set the jump pressed flag to false
	UFUNCTION()
	void StopJump();

	// Make the character crouch down (or stand up)
	UFUNCTION()
	void ToggleCrouch();

	UFUNCTION()
	void StopCrouch();

	// Make the character sprint by setting the sprint flag to true
	UFUNCTION()
	void StartSprint();

	// Make the character stop sprinting by setting the sprint flag to false
	UFUNCTION()
	void StopSprint();

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

private:
	// How much time in seconds the player can stand still before sprinting is stopped
	UPROPERTY(EditAnywhere)
	float SprintIdleTime = 1.5f;

	// How fast the player can sprint
	UPROPERTY(EditAnywhere)
	float MaxSprintSpeed = 1200;

	bool bPressedSprint;
	float SprintIdleTimer = 0.0f;
	float MaxWalkSpeed = 600;

};
