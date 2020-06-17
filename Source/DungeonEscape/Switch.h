// Copyright Frank Severijns 2020

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/ActorComponent.h"
#include "Respawnable.h"
#include "Switch.generated.h"

// Forward Declarations
class USwitchable;
class UPlayerRespawner;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class DUNGEONESCAPE_API USwitch : public UActorComponent, public IRespawnable
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	USwitch();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;
	// Finds the player's respawn component or logs an error if none is found
	virtual void InitializeRespawner();
	// Notifies the Switchables to change their state
	void NotifySwitchables(const bool bSwitchState);

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	// Gets the current switch state
	bool GetSwitchState();
	// Register the respawnable, making the system aware that this object should reset on player death
	virtual void RegisterRespawnable() override;
	// Reset the object to its original state
	virtual void OnPlayerRespawn() override;
	// Evaluate whether the object is still viable for resetting
	virtual void OnCheckpointReached() override;

protected:
	// If true, the affected Switchables are not synchronized with the switch state, but instead their state is based on their previous state
	UPROPERTY(EditAnywhere)
	bool bIsToggle = false;

	// Which actors are affected by the switch (actor must contain at least one ActorComponent deriving from Switchable to be affected)
	UPROPERTY(EditAnywhere)
	TArray<AActor*> AffectedActors;

	TArray<USwitchable*> Switchables;
	bool bCurrentSwitchState;
	bool bDefaultSwitchState;

	// The player respawner (used to reset on player deaths)
	UPlayerRespawner* Respawner = nullptr;

public:
	// Get Switchables of the specified type
	// This is just to try out template functions, it serves no actual purpose (yet)!
	template <typename T>
	FORCEINLINE TArray<T*> GetSwitchablesOfType()
	{
		TArray<T*> SwitchablesOfType;
		for(USwitchable* Switchable : Switchables)
		{
			T* Switchable = Cast<T>(Switchable);
			if(Switchable && Switchable != nullptr)
			{
				SwitchablesOfType.Add(Switchable);
			}
		}

		return SwitchablesOfType;
	}
};
