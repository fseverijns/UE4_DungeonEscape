// Copyright Frank Severijns 2020

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Components/AudioComponent.h"
#include "Engine/World.h"
#include "GameFramework/Actor.h"
#include "GameFramework/PlayerController.h"
#include "Respawnable.h"
#include "Sound/SoundBase.h"
#include "KeyItemInventory.h"
#include "KeyItemPickup.generated.h"

// Forward declarations
class UPlayerRespawner;

/*	Add this component to an actor to make it a Key Item that can be picked up by the player, marking the corresponding Key Item as "collected".
*	These are used by the InteractWithKeyItemSwitches to, for example, open a door that requires a key.
*/
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class DUNGEONESCAPE_API UKeyItemPickup : public UActorComponent, public IRespawnable
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UKeyItemPickup();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;
	// Finds the player's respawn component or logs an error if none is found
	virtual void InitializeRespawner();
	// Finds the audio component or logs an error if none is found
	virtual void InitializeAudioComponent();
	// Register the respawnable, making the system aware that this object should reset on player death
	virtual void RegisterRespawnable() override;
	// Reset the object to its original state
	virtual void OnPlayerRespawn() override;
	// Evaluate whether the object is still viable for resetting
	virtual void OnCheckpointReached() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	// When the item is picked up
	void PickUp();

private:
	// The type of Key Item
	UPROPERTY(EditAnywhere)
	EKeyItemId KeyItemId;

	// The particle effect (optional)
	UPROPERTY(EditAnywhere)
	AActor* PickupParticleFX;

	UPROPERTY(EditAnywhere)
	USoundBase* PickupSound;

	// Whether or not the object has been collected
	bool bCollected = false;
	// The audio component used to play sounds
	UAudioComponent* AudioComponent = nullptr;
	//The player respawner used to reset on player death
	UPlayerRespawner* Respawner = nullptr;
};
