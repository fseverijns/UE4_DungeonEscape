// Copyright Frank Severijns 2020

#include "ObjectTransformer.h"

#define OUT

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

	Object = GetOwner()->GetRootComponent();
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

void UObjectTransformer::ProcessActivationState(const float DeltaTime)
{
	float Delay = 0.0f;

	if(bActivationState)
	{
		Delay = TransformDelay;
	}
	else
	{
		Delay = ReverseDelay;
	}

	if(DelayTimer < Delay)
	{
		DelayTimer += DeltaTime;
		return;
	}

	if(bActivationState)
	{
		bool bTransformCompleted = false;
		Transform(DeltaTime, OUT bTransformCompleted);	

		if(bTransformCompleted)
		{
			if(bLoop)
			{
				bLoopIsReversing = !bLoopIsReversing;
				bIsReversing = bLoopIsReversing;
			}
			else
			{
				bTransformInProgress = false;
			}
			DelayTimer = 0.0f;
		}
	}
	else
	{
		bLoopIsReversing = false;
		bIsReversing = true;

		bool bTransformCompleted = false;
		Transform(DeltaTime, OUT bTransformCompleted);	

		if(bTransformCompleted)
		{
			bIsReversing = false;
			bTransformInProgress = false;
			DelayTimer = 0.0f;
		}	
	}
}

void UObjectTransformer::Transform(float DeltaTime, bool& out_bTransformCompleted)
{
	// Implemented by derived classes
}

void UObjectTransformer::OnPlayerRespawn()
{
	Super::OnPlayerRespawn();

	if(!bLoop)
	{
		bTransformInProgress = false;
	}
	
	bLoopIsReversing = false;
	bIsReversing = false;
	Speed = 0;

	// Implemented by derived classes
}
