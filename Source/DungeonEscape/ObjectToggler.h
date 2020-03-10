// Copyright Frank Severijns 2020

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "GameFramework/Actor.h"
#include "SwitchObserver.h"
#include "ObjectToggler.generated.h"

// Use this class to enable or disable certain aspects of the Actor it is attached to.
// By default, it will completely hide the Actor, prevent collision and stop the attached components from Ticking.
// However, it could be used as a tool to simply stop collision while retaining visibility.
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class DUNGEONESCAPE_API UObjectToggler : public USwitchObserver
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UObjectToggler();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;
	// What to do when the toggle state changes
	virtual void ChangeActivationState(const bool bNewState) override; 

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

private:
	// Whether or not to toggle collision components
	UPROPERTY(EditAnywhere)
	bool bToggleCollision = true;

	// Whether or not to toggle the actor's visibility
	UPROPERTY(EditAnywhere)
	bool bToggleVisibility = true;

	// Whether or not to toggle the actor's component ticks
	UPROPERTY(EditAnywhere)
	bool bToggleTicks = true;

	// The default toggle state
	UPROPERTY(EditAnywhere)
	bool bOnByDefault = true;

	// Automatically resets to the original state after toggling
	UPROPERTY(EditAnywhere)
	bool bAutoReset = false;

	// Delay before automatic reset takes place
	UPROPERTY(EditAnywhere)
	float AutoResetDelay = 2.0f;

	// Keep track of changes to the toggle state
	bool bToggleStateChanged;

	float ResetTimer = 0.f;
};
