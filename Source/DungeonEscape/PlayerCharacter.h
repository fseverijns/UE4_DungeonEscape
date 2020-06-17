// Copyright Frank Severijns 2020
// Based on the tutorial https://docs.unrealengine.com/en-US/Programming/Tutorials/FirstPersonShooter/2/

#pragma once

#include "CoreMinimal.h"
#include "Components/AudioComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/Controller.h"
#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Sound/SoundBase.h"
#include "PlayerCharacter.generated.h"

UCLASS()
class DUNGEONESCAPE_API APlayerCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	APlayerCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Finds the audio component on the player or logs an error if none is found
	void InitializeAudioComponent();

	// Finds the movement component on the player or logs an error if none is found
	void InitializeMovementComponent();

	// Move the character forward or back
	UFUNCTION()
	void MoveForward(float Axis);

	// Move the character right or left
	UFUNCTION()
	void MoveRight(float Axis);

	// Play a footstep sound
	void PlayFootstepSound();

	// Play the fall sound (player hitting the ground after jumping/falling)
	void PlayFallSound();

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

	// Enable/disable player movement
	void SetPlayerMovementAllowed(const bool bAllowed);

	// Get the weight of the player actor
	float GetWeight();

private:
	// How much time in seconds the player can stand still before sprinting is stopped
	UPROPERTY(EditAnywhere)
	float SprintIdleTime = 1.5f;

	// How fast the player can sprint
	UPROPERTY(EditAnywhere)
	float MaxSprintSpeed = 1200;

	// Weight of the player in Kilograms
	UPROPERTY(EditAnywhere)
	float WeightInKg = 70;

	// Footstep sounds
	UPROPERTY(EditAnywhere)
	TArray<USoundBase*> FootstepSounds;

	// Fall sound
	UPROPERTY(EditAnywhere)
	USoundBase* FallSound;

	// The time between footstep sounds while walking
	UPROPERTY(EditAnywhere)
	float WalkFootstepSoundInterval = 0.75f;

	// The time between footstep sounds while sprinting
	UPROPERTY(EditAnywhere)
	float SprintFootstepSoundInterval = 0.35f;


	// Player has pressed the sprint button
	bool bPressedSprint = false;
	// How long since pressing sprint has the player been idle (non-moving)
	float SprintIdleTimer = 0.0f;
	// Store the max walk speed here to reset the walk speed after sprinting
	float MaxWalkSpeed = 600;
	// Can be set to false to block all player character movement
	bool bMovementAllowed = true;
	// Interval timer between walk sound playback
	float FootstepSoundTimer = 0.0f;
	// If the player character was falling during the last tick
	bool bWasFalling = false;
	// The audio component used to play sounds
	UAudioComponent* AudioComponent = nullptr;
	// The movement component used to check if playing is on the ground
	UCharacterMovementComponent* MovementComponent = nullptr;
};
