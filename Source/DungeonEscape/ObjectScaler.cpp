// Copyright Frank Severijns 2020

#include "ObjectScaler.h"

// Sets default values for this component's properties
UObjectScaler::UObjectScaler()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UObjectScaler::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UObjectScaler::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UObjectScaler::Transform(float DeltaTime, bool& out_bTransformCompleted)
{
	Super::Transform(DeltaTime, out_bTransformCompleted);
	
	FVector CurrentScale = Object->GetRelativeScale3D();
	FVector TargetScale = ObjectEndScale;

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
		TargetScale = ObjectStartScale;
	}

	FVector NewScale = FMath::Lerp(CurrentScale, TargetScale, DeltaTime * Speed);

	out_bTransformCompleted = CurrentScale.Equals(TargetScale, CompletionErrorTolerance);

	if(out_bTransformCompleted)
	{
		Speed = 0;
	}

	Object->SetRelativeScale3D(NewScale);
}

void UObjectScaler::OnPlayerRespawn()
{
	Super::OnPlayerRespawn();

	Object->SetRelativeScale3D(bDefaultState ? ObjectEndScale : ObjectStartScale);
}

