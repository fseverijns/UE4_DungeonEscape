// Copyright Frank Severijns 2020

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Components/StaticMeshComponent.h"
#include "GameFramework/Actor.h"
#include "GameFramework/PlayerController.h"
#include "Engine/World.h"
#include "Engine/TriggerVolume.h"
#include "SwitchObserver.h"
#include "ObjectTransformer.generated.h"


UCLASS( ClassGroup=(Custom), abstract, meta=(BlueprintSpawnableComponent) )
class DUNGEONESCAPE_API UObjectTransformer : public USwitchObserver
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UObjectTransformer();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;
	// Processes activation logic
	virtual void ProcessActivationState(const float DeltaTime);
	// Start moving the object
	virtual void ChangeActivationState(const bool bNewState) override; 

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

// Editable properties
protected:
	// Automatically activate upon BeginPlay
	UPROPERTY(EditAnywhere)
	bool bAutoActivated; 

	// Whether or not the activation state can be altered while the state change is in progress
	UPROPERTY(EditAnywhere)
	bool bAllowInterrupt = true;

	// Automatically deactivate after activation completes
	UPROPERTY(EditAnywhere)
	bool bAutoReverse; 

	// Delay before the object starts transforming to its activated state
	UPROPERTY(EditAnywhere)
	float TransformDelay = 0.0f;

	// Delay before the object returns to its deactivated state
	UPROPERTY(EditAnywhere)
	float ReverseDelay = 0.0f;

	// The speed at which the object transforms to its activated state
	UPROPERTY(EditAnywhere)
	float TransformSpeed = 1.0f;

	// The speed at which the object returns to its deactivated state
	UPROPERTY(EditAnywhere)
	float ReverseSpeed = 1.0f;

protected:
	// If the player is inside the trigger volume
	bool bPlayerInTrigger = false;
	// Activation state of the object (false = deactivated, true = activated)
	bool bActivationState = false; 
	// Indicates the activation state of the object has changed
	bool bTransformInProgress = false; 
	// Timer that starts after activation/deactivation to implement a delay
	float DelayTimer = 0.0f; 
};
