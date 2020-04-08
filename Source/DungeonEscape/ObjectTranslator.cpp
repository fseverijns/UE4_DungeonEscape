// Copyright Frank Severijns 2020

#include "ObjectTranslator.h"

// Sets default values for this component's properties
UObjectTranslator::UObjectTranslator()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UObjectTranslator::BeginPlay()
{
	Super::BeginPlay();
}


// Called every frame
void UObjectTranslator::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UObjectTranslator::Transform(float DeltaTime, bool& out_bTransformCompleted)
{
	FVector CurrentLocation = Object->GetRelativeLocation();
	FVector TargetLocation = ObjectEndLocation;

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
		TargetLocation = ObjectStartLocation;
	}

	FVector NewPosition = FMath::Lerp(CurrentLocation, TargetLocation, DeltaTime * Speed);

	out_bTransformCompleted = CurrentLocation.Equals(TargetLocation, CompletionErrorTolerance);

	if(out_bTransformCompleted)
	{
		Speed = 0;
	}

	Object->SetRelativeLocation(NewPosition);
}

void UObjectTranslator::OnPlayerRespawn()
{
	Super::OnPlayerRespawn();

	UE_LOG(LogTemp, Warning, TEXT("RESET %s"), *GetOwner()->GetName());

	Object->SetRelativeLocation(bDefaultState ? ObjectEndLocation : ObjectStartLocation);
}

