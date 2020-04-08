// Copyright Frank Severijns 2020

#include "ObjectSpinner.h"

// Sets default values for this component's properties
UObjectSpinner::UObjectSpinner()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UObjectSpinner::BeginPlay()
{
	Super::BeginPlay();

	Object = GetOwner()->GetRootComponent();	

	InitialRotation = Object->GetRelativeRotation();
}


// Called every frame
void UObjectSpinner::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if(bActivationState)
	{
		Spin(DeltaTime);
	}
}

void UObjectSpinner::ChangeActivationState(const bool bNewState)
{
	bActivationState = bNewState;
}

void UObjectSpinner::Spin(float DeltaTime)
{
	FRotator CurrentRotation = Object->GetRelativeRotation();
	FRotator Direction = FRotator(
	bXAxis ? 1 : 0, 
	bYAxis ? 1 : 0, 
	bZAxis ? 1 : 0) * SpinSpeed;

	FRotator NewRotation = FMath::Lerp(CurrentRotation, CurrentRotation + Direction, DeltaTime);

	Object->SetRelativeRotation(NewRotation);
}

void UObjectSpinner::OnPlayerRespawn()
{
	Super::OnPlayerRespawn();

	Object->SetRelativeRotation(InitialRotation);
}

