// Copyright Frank Severijns 2020

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Switchable.h"
#include "ObjectSpinner.generated.h"

/* 	A Switchable derivative. Can be assigned to any Switch component.
*	While activated, it spins the object around the specified axes.
*/
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class DUNGEONESCAPE_API UObjectSpinner : public USwitchable
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UObjectSpinner();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;
	// What to do when the switch state changes
	virtual void ChangeActivationState(const bool bNewState, bool bPlaySound = true) override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	// Rotates the object
	virtual void Spin(float DeltaTime);
	// Reset the object to its initial state
	virtual void OnPlayerRespawn() override;

private:
	// Spin object around X axis
	UPROPERTY(EditAnywhere)
	bool bXAxis;
	// Spin object around Y axis
	UPROPERTY(EditAnywhere)
	bool bYAxis;
	// Spin object around Z axis
	UPROPERTY(EditAnywhere)
	bool bZAxis;

	// Rotation speed
	UPROPERTY(EditAnywhere)
	float SpinSpeed;

	// The root component
	USceneComponent* Object;

	// The initial rotation
	FRotator InitialRotation;	
};
