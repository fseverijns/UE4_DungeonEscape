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

/* 	A SwitchObserver derivative. Cannot be used directly, instead use a derived component (such as ObjectRotator)
*	Handles the activation logic.
*/
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
	// Start transforming the object
	virtual void ChangeActivationState(const bool bNewState) override; 
	// Processes activation logic
	virtual void ProcessActivationState(const float DeltaTime);
	// Transform the object
	virtual void Transform(float DeltaTime, bool& out_bTransformCompleted);
	// Reset the object to its initial state
	virtual void OnPlayerRespawn() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

// Editable properties
protected:
	// While active, the object loops between its begin and end states.
	UPROPERTY(EditAnywhere)
	bool bLoop;

	// Whether or not the activation state can be altered while the state change is in progress
	UPROPERTY(EditAnywhere)
	bool bAllowInterrupt = true;

	// Automatically deactivate after activation completes
	UPROPERTY(EditAnywhere)
	bool bAutoReverse; 

	// Delay before the object starts looping
	UPROPERTY(EditAnywhere)
	float LoopStartDelay = 0.0f;

	// Delay before the object starts transforming to its activated state
	UPROPERTY(EditAnywhere)
	float TransformDelay = 0.0f;

	// Delay before the object returns to its deactivated state
	UPROPERTY(EditAnywhere)
	float ReverseDelay = 0.0f;

	// The speed at which the object transforms to its activated state
	UPROPERTY(EditAnywhere)
	float TransformSpeed = 1.0f;

	// How fast the object accelerates to the specified transform speeds (0.0 = instant)
	UPROPERTY(EditAnywhere)
	float Acceleration = 0.0f;

	// When comparing current state to end state, how much difference between states is tolerated
	UPROPERTY(EditAnywhere)
	float CompletionErrorTolerance = 1.0f;

	// Indicates the activation state of the object has changed
	bool bTransformInProgress = false; 
	// Indicates the loop has started
	bool bLoopStarted = false; 
	// Timer that starts after activation/deactivation to implement a delay
	float DelayTimer = 0.0f; 
	// Indicates that the object is reversing as part of a loop (bLoop is true)
	bool bLoopIsReversing;
	// Indicates that the object is reversing
	bool bIsReversing;
	// Current speed of the object;
	float Speed;
	// The scene component
	USceneComponent* Object;
};
