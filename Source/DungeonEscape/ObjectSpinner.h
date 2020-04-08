// Copyright Frank Severijns 2020

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "SwitchObserver.h"
#include "ObjectSpinner.generated.h"

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class DUNGEONESCAPE_API UObjectSpinner : public USwitchObserver
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UObjectSpinner();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;
	// What to do when the switch state changes
	virtual void ChangeActivationState(const bool bNewState) override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	// Rotates the object
	virtual void Spin(float DeltaTime);
	// Reset the object to its initial state
	virtual void OnPlayerRespawn() override;

private:
	UPROPERTY(EditAnywhere)
	bool bXAxis;
	UPROPERTY(EditAnywhere)
	bool bYAxis;
	UPROPERTY(EditAnywhere)
	bool bZAxis;

	UPROPERTY(EditAnywhere)
	float SpinSpeed;

	// The root component
	USceneComponent* Object;

	// The initial rotation
	FRotator InitialRotation;	
};
