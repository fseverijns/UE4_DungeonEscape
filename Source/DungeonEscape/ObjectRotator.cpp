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
}


// Called every frame
void UObjectRotator::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

void UObjectRotator::Transform(float DeltaTime, bool& out_TransformCompleted)
{
	USceneComponent* Object = GetOwner()->GetRootComponent();
	
	FRotator CurrentRotation = Object->GetRelativeRotation();
	FRotator TargetRotation = ObjectEndRotation;

	if(Acceleration == 0.0f)
	{
		Speed = TransformSpeed;
	}
	else
	{
		Speed += FMath::Clamp(Acceleration * DeltaTime, 0.01f, TransformSpeed);
	}

	if(bIsReversing)
	{
		TargetRotation = ObjectStartRotation;
	}

	FRotator NewRotation = FMath::Lerp(CurrentRotation, TargetRotation, DeltaTime * Speed);

	out_TransformCompleted = CurrentRotation.Equals(TargetRotation, CompletionErrorTolerance);

	if(out_TransformCompleted)
	{
		Speed = 0;
	}

	Object->SetRelativeRotation(NewRotation);
}

