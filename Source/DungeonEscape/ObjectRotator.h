// Copyright Frank Severijns 2020

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "GameFramework/Actor.h"
#include "ObjectTransformer.h"
#include "ObjectRotator.generated.h"

/* 	A Switchable derivative. Can be assigned to any Switch component.
*	When activated/deactivated, it Lerps the rotation from its start and end state (and vice versa).
*/
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class DUNGEONESCAPE_API UObjectRotator : public UObjectTransformer
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UObjectRotator();
	
protected:
	// Called when the game starts
	virtual void BeginPlay() override;
	// Rotates the object
	virtual void Transform(float DeltaTime, bool& out_bTransformCompleted) override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	// Reset the object to its initial state
	virtual void OnPlayerRespawn() override;

private:

private:
	UPROPERTY(EditAnywhere)
	FRotator ObjectStartRotation = FRotator(0,0,0);

	UPROPERTY(EditAnywhere)
	FRotator ObjectEndRotation = FRotator(0,90,0);
};
