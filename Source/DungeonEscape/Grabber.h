// Copyright Frank Severijns 2020

#pragma once

#include "CoreMinimal.h"
#include "Components/InputComponent.h"
#include "Components/PrimitiveComponent.h"
#include "DrawDebugHelpers.h"
#include "Engine/World.h"
#include "GameFramework/Actor.h"
#include "GameFramework/PlayerController.h"
#include "PhysicsEngine/PhysicsHandleComponent.h"
#include "Grabber.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class DUNGEONESCAPE_API UGrabber : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UGrabber();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

private:
	// Distance from which the player can grab objects
	UPROPERTY(EditAnywhere)
	int32 Reach = 150;
	// How much weight the player can carry
	UPROPERTY(EditAnywhere)
	int32 MaximumCarryWeight = 20;

	UInputComponent* InputHandler = nullptr;
	UPhysicsHandleComponent* PhysicsHandler = nullptr;
	AActor* ObjectInReach;
	AActor* HeldObject;
	FVector HeldPosition;

	// Find the PhysicsHandleComponent
	void FindPhysicsHandler();
	// Bind the input to the Grab and Release functions
	void BindInput();
	// Grab a physics object
	void Grab();
	// Release the currently held physics object
	void Release();
	// Returns the first actor with physics within reach
	AActor* FindFirstPhysicsObjectInReach() const;
	// Cast a ray from the Actor's viewpoint to its reach
	void CastRay(AActor* &out_HitActor) const;
};
