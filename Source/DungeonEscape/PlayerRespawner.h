// Copyright Frank Severijns 2020

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Components/AudioComponent.h"
#include "Sound/SoundBase.h"
#include "PlayerRespawner.generated.h"

// Forward Declarations
class UCheckpoint;
class IRespawnable;
class UGrabber;
class UInteracter;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class DUNGEONESCAPE_API UPlayerRespawner : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UPlayerRespawner();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	// Finds the required components or log an error if none are found
	virtual void InitializeAudioComponent();
	virtual void InitializeGrabberComponent();
	virtual void InitializeInteracterComponent();

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	// Called when the player enters a checkpoint
	void OnCheckpointReached(UCheckpoint* Checkpoint);
	// Kill the player character
	void Kill();
	// Registers a respawnable object, notifying it when the player respawns
	void RegisterRespawnable(IRespawnable* Respawnable);
	// Unregisters a respawnable object, stopping notifications when player respawns
	void UnregisterRespawnable(IRespawnable* Respawnable);

private:
	// Sound played upon player character dying
	UPROPERTY(EditAnywhere)
	USoundBase* DeathSound = nullptr;

	// The audio component attached to the player
	UAudioComponent* AudioComponent = nullptr;
	// The Grabber component attached to the player
	UGrabber* Grabber = nullptr;
	// The Interacter component attached to the player
	UInteracter* Interacter = nullptr;
	// The last checkpoint the player has reached
	UCheckpoint* LastCheckpoint = nullptr;
	// List of respawnable objects
	TArray<IRespawnable*> Respawnables;
	// List of respawnables marked for removal
	TArray<IRespawnable*> RespawnablesToRemove;
};
