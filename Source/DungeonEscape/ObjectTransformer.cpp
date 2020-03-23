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
		bool TransformCompleted = false;
		Transform(DeltaTime, OUT TransformCompleted);	

		if(TransformCompleted)
		{
			UE_LOG(LogTemp, Warning, TEXT("%s transform completed!"), *GetOwner()->GetName());
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

		bool TransformCompleted = false;
		Transform(DeltaTime, OUT TransformCompleted);	

		if(TransformCompleted)
		{
			bIsReversing = false;
			bTransformInProgress = false;
			DelayTimer = 0.0f;
		}	
	}
}

void UObjectTransformer::Transform(float DeltaTime, bool& out_TransformCompleted)
{
	// Implemented by derived classes
}

