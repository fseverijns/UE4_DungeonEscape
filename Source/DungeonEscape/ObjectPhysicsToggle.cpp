// Copyright Frank Severijns 2020

#include "ObjectPhysicsToggle.h"

// Sets default values for this component's properties
UObjectPhysicsToggle::UObjectPhysicsToggle()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UObjectPhysicsToggle::BeginPlay()
{
	Super::BeginPlay();

	Primitive = GetOwner()->FindComponentByClass<UPrimitiveComponent>();
	InitialPosition = GetOwner()->GetActorLocation();
}


// Called every frame
void UObjectPhysicsToggle::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

// Activate or deactive physics based on the switchobserver state
void UObjectPhysicsToggle::ChangeActivationState(const bool bNewState)
{
	Super::ChangeActivationState(bNewState);

	if(Primitive && Primitive != nullptr)
	{
		Primitive->SetSimulatePhysics(bNewState);
		if(bNewState)
		{
			Primitive->AddImpulse(ImpulseAdded, FName("")); // Add impulse
		}
	}
}

// Reset the physics and location when player respawns
void UObjectPhysicsToggle::OnPlayerRespawn()
{
	Super::OnPlayerRespawn();

	Primitive->SetSimulatePhysics(bDefaultState);
	GetOwner()->SetActorLocation(InitialPosition);
}

