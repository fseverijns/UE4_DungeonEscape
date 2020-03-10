// Copyright Frank Severijns 2020


#include "ObjectTransformer.h"

// Sets default values for this component's properties
UObjectTransformer::UObjectTransformer()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UObjectTransformer::BeginPlay()
{
	Super::BeginPlay();

	if(bAutoActivated)
	{
		ChangeActivationState(true);
	}
}


// Called every frame
void UObjectTransformer::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// Go through activation logic
	if(bTransformInProgress)
	{
		ProcessActivationState(DeltaTime);
	}
}

void UObjectTransformer::ProcessActivationState(const float DeltaTime)
{
	// Implemented by derived classes
}

void UObjectTransformer::ChangeActivationState(const bool bNewState)
{
	if(!bAllowInterrupt && bTransformInProgress) // Check if the object can and is being deactivated, or if it cannot be interrupted
	{
		return;
	}

	if(bActivationState != bNewState) // If the new activation state is different from the current state
	{
		bTransformInProgress = true;
	}

	bActivationState = bNewState;
}

