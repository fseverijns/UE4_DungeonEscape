// Copyright Frank Severijns 2020

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Components/AudioComponent.h"
#include "Engine/World.h"
#include "GameFramework/Actor.h"
#include "Respawnable.h"
#include "Sound/SoundBase.h"
#include "Switchable.generated.h"

// Forward declarations
class UPlayerRespawner;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class DUNGEONESCAPE_API USwitchable : public UActorComponent, public IRespawnable
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	USwitchable();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;
	// What to do when the switch state changes
	virtual void ChangeActivationState(const bool bNewState, bool bPlaySound = true);
	// Finds the player's respawn component or logs an error if none is found
	virtual void InitializeRespawner();
	// Finds the audio component or logs an error if none is found
	virtual void InitializeAudioComponent();
	// Plays activation/deactivation sounds
	virtual void PlayActivationSound();

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	// Called when the switch state has changed
	void OnSwitchStateChanged(const bool bSwitchState);
	// Get the current state of the Switchable
	bool GetCurrentState();
	// Register the respawnable, making the system aware that this object should reset on player death
	virtual void RegisterRespawnable() override;
	// Reset the object to its original state
	virtual void OnPlayerRespawn() override;
	// Evaluate whether the object is still viable for resetting
	virtual void OnCheckpointReached() override;

protected:
	// Whether or not to invert activation state (e.g. leaving trigger instead of entering trigger to activate this)
	UPROPERTY(EditAnywhere)
	bool bInvertActivation = false;

	// The default state of the Switchable (true = active, false = inactive)
	UPROPERTY(EditAnywhere)
	bool bDefaultState = false;

	// Should this Switchable play sounds
	UPROPERTY(EditAnywhere)
	bool bUseSound = false;

	// Sound to play on activation
	UPROPERTY(EditAnywhere)
	USoundBase* ActivationSound = nullptr;

	// Sound to play on deactivation
	UPROPERTY(EditAnywhere)
	USoundBase* DeactivationSound = nullptr;

	// Activation state of the object (false = deactivated, true = activated)
	bool bActivationState = false; 

	// The audio component used to play sounds
	UAudioComponent* AudioComponent = nullptr;

	// The player respawner (used to reset on player deaths)
	UPlayerRespawner* Respawner = nullptr;
	
};
