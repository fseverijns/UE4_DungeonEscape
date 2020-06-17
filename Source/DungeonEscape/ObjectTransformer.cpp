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

	// Go through activation logic only if transform is in progress
	if(bTransformInProgress)
	{
		ProcessActivationState(DeltaTime);
	}
}


void UObjectTransformer::ChangeActivationState(const bool bNewState, bool bPlaySound)
{
	if(!bAllowInterrupt && bTransformInProgress) // Check if the object can and is being deactivated, or if it cannot be interrupted
	{
		return;
	}

	if(bActivationState != bNewState) // If the new activation state is different from the current state
	{
		bTransformInProgress = true;

		bLoopStarted = false;
		bIsReversing = false;
		DelayTimer = 0.0f; // reset the delay timer
	}

	bActivationState = bNewState;

	if(bPlaySound)
	{
		Super::PlayActivationSound();
	}
}

// Go through activation logic (only when bTransformInProgress is true!)
void UObjectTransformer::ProcessActivationState(const float DeltaTime)
{
	float Delay = GetDelayTime();

	// Do not proceed until the DelayTimer exceeds the delay
	if(DelayTimer < Delay)
	{
		DelayTimer += DeltaTime;
		return;
	}

	if(bActivationState) // If the Switchable is activated, perform the transform function
	{
		bool bTransformCompleted = false;
		Transform(DeltaTime, OUT bTransformCompleted);	

		if(bTransformCompleted) // When completed, check if it needs to loop (reverse without deactivating)
		{
			if(AudioComponent != nullptr && AudioComponent->IsPlaying()) // Stop the audio
			{
				//AudioComponent->Stop();
			}

			if(bLoop)
			{
				bLoopStarted = true;
				bLoopIsReversing = !bLoopIsReversing;
				bIsReversing = bLoopIsReversing;

				LoopSoundTimer = 0.0f;
				bLoopSoundPlayed = false;
			}
			else // If it does not need to loop, transform is no longer in progress
			{
				bTransformInProgress = false;
			}
			DelayTimer = 0.0f; // reset the delay timer
		}
	}
	else // If the Switchable is de-activated, reverse to its deactivated state
	{
		bLoopIsReversing = false;
		bIsReversing = true;

		bool bTransformCompleted = false;
		Transform(DeltaTime, OUT bTransformCompleted);	

		if(bTransformCompleted)
		{
			bLoopStarted = false;
			bIsReversing = false;
			bTransformInProgress = false;
			DelayTimer = 0.0f; // reset the delay timer
		}	
	}
}

float UObjectTransformer::GetDelayTime()
{
	float Delay = 0.0f;

	// Determine which delay to use
	if(bActivationState) // If the Switchable is activated, use the transform delay
	{
		Delay = TransformDelay;
	}
	else // Else use the reverse delay
	{
		Delay = ReverseDelay;
	}

	// If we need to loop, add the loop start delay
	if(bLoop && !bLoopStarted)
	{
		Delay += LoopStartDelay;
	}

	return Delay;
}

// Transforms the object. Specifics (translation, rotation, etc.) are done by derived classes. Should return true through the out parameter when transform is completed.
void UObjectTransformer::Transform(float DeltaTime, bool& out_bTransformCompleted)
{
	if(bUseSound && bLoop && AudioComponent != nullptr && LoopSound != nullptr) // if a sound should be played during the loop
	{
		LoopSoundTimer += DeltaTime;
		
		if(LoopSoundTimer > LoopSoundStartDelay && !bLoopSoundPlayed)
		{
			AudioComponent->SetSound(LoopSound);

			if(bRandomizeLoopSoundPitch)
			{
				AudioComponent->SetPitchMultiplier(FMath::RandRange(-1.f, 1.f));
			}

			AudioComponent->Play();

			bLoopSoundPlayed = true;
		}
	}
	// Implemented by derived classes
}

// Reset variables to the default state when player respawns
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
