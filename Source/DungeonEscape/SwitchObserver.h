// Copyright Frank Severijns 2020

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "GameFramework/Actor.h"
#include "Respawnable.h"
#include "SwitchObserver.generated.h"

//~~~~~ Forward Declarations~~~~~
class UCheckpoint;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class DUNGEONESCAPE_API USwitchObserver : public UActorComponent, public IRespawnable
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	USwitchObserver();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;
	// What to do when the switch state changes
	virtual void ChangeActivationState(const bool bNewState);

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	// Called when the switch state has changed
	void OnSwitchStateChanged(const bool bSwitchState);
	// Get the current state of the observer
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

	// The default state of the switch observer (true = active, false = inactive)
	UPROPERTY(EditAnywhere)
	bool bDefaultState = false;

	// Activation state of the object (false = deactivated, true = activated)
	bool bActivationState = false; 
};
