// Copyright Frank Severijns 2020

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Components/PrimitiveComponent.h"
#include "GameFramework/Actor.h"
#include "SwitchObserver.h"
#include "ObjectPhysicsToggle.generated.h"

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class DUNGEONESCAPE_API UObjectPhysicsToggle : public USwitchObserver
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UObjectPhysicsToggle();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;	
	virtual void ChangeActivationState(const bool bNewState) override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	// Reset the object to its initial state
	virtual void OnPlayerRespawn() override;

private:
	// Impulse added to the object when physics are enabled
	UPROPERTY(EditAnywhere)
	FVector ImpulseAdded = FVector(0,0,0);

	//The primitive component used to toggle physics
	UPrimitiveComponent* Primitive;

	// Initial object position
	FVector InitialPosition;		
};
