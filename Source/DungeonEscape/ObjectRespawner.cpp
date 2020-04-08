// Copyright Frank Severijns 2020


#include "ObjectRespawner.h"

// Sets default values for this component's properties
UObjectRespawner::UObjectRespawner()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UObjectRespawner::BeginPlay()
{
	Super::BeginPlay();

	InitialLocation = GetOwner()->GetActorLocation();
	InitialRotation = GetOwner()->GetActorRotation();
}


// Called every frame
void UObjectRespawner::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UObjectRespawner::Reset()
{
	GetOwner()->SetActorLocation(InitialLocation);
	GetOwner()->SetActorRotation(InitialRotation);
}

