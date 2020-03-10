// Copyright Frank Severijns 2020

#include "ObjectRotator.h"

// Sets default values for this component's properties
UObjectRotator::UObjectRotator()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UObjectRotator::BeginPlay()
{
	Super::BeginPlay();

	USceneComponent* Object = GetOwner()->GetRootComponent();

	Object->SetRelativeRotation(ObjectStartRotation);
}


// Called every frame
void UObjectRotator::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

void UObjectRotator::ProcessActivationState(const float DeltaTime)
{	
	if(bTransformInProgress)
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
			RotationAlpha += DeltaTime * TransformSpeed;
			if(RotationAlpha > 1)
			{
				bTransformInProgress = false;
				DelayTimer = 0.0f;
				RotationAlpha = 1;
			}	
		}
		else
		{
			RotationAlpha -= DeltaTime * ReverseSpeed;
			if(RotationAlpha < 0)
			{
				bTransformInProgress = false;
				DelayTimer = 0.0f;
				RotationAlpha = 0;
			}	
		}

		Rotate();	
	}
}

void UObjectRotator::Rotate()
{
	USceneComponent* Object = GetOwner()->GetRootComponent();

	FRotator NewRotation = FMath::Lerp(ObjectStartRotation, ObjectEndRotation, RotationAlpha);

	Object->SetRelativeRotation(NewRotation);
}

