// Copyright Frank Severijns 2020

#include "PlayerRespawner.h"
#include "Checkpoint.h"

// Sets default values for this component's properties
UPlayerRespawner::UPlayerRespawner()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}

// Called when the game starts
void UPlayerRespawner::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}

// Called every frame
void UPlayerRespawner::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UPlayerRespawner::OnCheckpointReached(UCheckpoint* Checkpoint)
{
	LastCheckpoint = Checkpoint;
}

void UPlayerRespawner::Kill()
{
	if(LastCheckpoint && LastCheckpoint != nullptr)
	{
		LastCheckpoint->RespawnPlayer();
	}
}

