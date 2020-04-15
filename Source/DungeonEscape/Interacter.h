// Copyright Frank Severijns 2020

#pragma once

#include "CoreMinimal.h"
#include "Components/InputComponent.h"
#include "Components/PrimitiveComponent.h"
#include "DrawDebugHelpers.h"
#include "Engine/World.h"
#include "GameFramework/Actor.h"
#include "GameFramework/PlayerController.h"
#include "Interacter.generated.h"

// Forward Declarations
class UInteractSwitch;

/*	A component attached to the player that allows it to interact with certain objects in the world.
* 	These "interactible" objects will have a "InteractSwitch" or "KeyItemPickup" component attached.
*/
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class DUNGEONESCAPE_API UInteracter : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UInteracter();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

private:
	// Distance from which the player can interact with objects
	UPROPERTY(EditAnywhere)
	float Reach = 150;

	// Input component that lets us bind the interact buttons
	UInputComponent* InputHandler = nullptr;
	// Switch currently being interacted with
	UInteractSwitch* InteractingWith;	

	// Bind the input to the Interact function
	void BindInput();
	// Interact with an actor
	void StartInteract();
	// Stop interacting with an actor
	void StopInteract();
	// Returns the first actor within reach
	AActor* FindFirstActorInReach() const;
	// Cast a ray from the Actor's viewpoint to its reach
	void CastRay(AActor* &out_HitActor) const;	
};
