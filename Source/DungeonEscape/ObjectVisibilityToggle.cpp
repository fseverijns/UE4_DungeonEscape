// Copyright Frank Severijns 2020

#include "ObjectVisibilityToggle.h"

// Sets default values for this component's properties
UObjectVisibilityToggle::UObjectVisibilityToggle()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UObjectVisibilityToggle::BeginPlay()
{
	Super::BeginPlay();

	GetOwner()->SetActorHiddenInGame(!bVisibleByDefault);
	GetOwner()->SetActorEnableCollision(bVisibleByDefault);
}


// Called every frame
void UObjectVisibilityToggle::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UObjectVisibilityToggle::ChangeActivationState(const bool bNewState)
{
	GetOwner()->SetActorHiddenInGame(bNewState);
	GetOwner()->SetActorEnableCollision(!bNewState);
}

void UObjectVisibilityToggle::OnPlayerRespawn()
{
	GetOwner()->SetActorHiddenInGame(!bVisibleByDefault);
	GetOwner()->SetActorEnableCollision(bVisibleByDefault);
}

