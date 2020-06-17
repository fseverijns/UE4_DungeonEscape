// Copyright Frank Severijns 2020

#include "PlayerRespawner.h"
#include "Respawnable.h"
#include "Checkpoint.h"
#include "Grabber.h"
#include "Interacter.h"

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

	InitializeAudioComponent();	
}

void UPlayerRespawner::InitializeAudioComponent()
{
	AudioComponent = GetOwner()->FindComponentByClass<UAudioComponent>();
	if(!AudioComponent || AudioComponent == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("%s requires an Audio Component but none is attached!"), *GetName());
		return;
	}

	AudioComponent->bAutoActivate = false;
	if(AudioComponent->IsPlaying())
	{
		AudioComponent->Stop();
	}
}

void UPlayerRespawner::InitializeGrabberComponent()
{
	Grabber = GetOwner()->FindComponentByClass<UGrabber>();
	if(!Grabber || Grabber == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("%s requires a Grabber Component but none is attached!"), *GetName());
		return;
	}
}

void UPlayerRespawner::InitializeInteracterComponent()
{
	Interacter = GetOwner()->FindComponentByClass<UInteracter>();
	if(!Interacter || Interacter == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("%s requires an Interacter Component but none is attached!"), *GetName());
		return;
	}
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

	for(IRespawnable* Respawnable : Respawnables)
	{
		Respawnable->OnCheckpointReached();
	}

	for(IRespawnable* Respawnable : RespawnablesToRemove)
	{
		Respawnables.Remove(Respawnable);
	}

	RespawnablesToRemove.Empty();
}

void UPlayerRespawner::Kill()
{
	if(LastCheckpoint && LastCheckpoint != nullptr)
	{
		if(AudioComponent != nullptr && DeathSound != nullptr)
		{
			AudioComponent->SetSound(DeathSound);
			AudioComponent->Play();
		}

		if(Grabber != nullptr)
		{
			Grabber->Release();
		}

		if(Interacter != nullptr)
		{
			Interacter->StopInteract();
		}

		LastCheckpoint->RespawnPlayer();
		
		for(IRespawnable* Respawnable : Respawnables)
		{
			Respawnable->OnPlayerRespawn();
		}
	}
}


void UPlayerRespawner::RegisterRespawnable(IRespawnable* Respawnable)
{
	if(Respawnables.Contains(Respawnable))
	{
		return;
	}

	Respawnables.Add(Respawnable);
}

void UPlayerRespawner::UnregisterRespawnable(IRespawnable* Respawnable)
{
	RespawnablesToRemove.Add(Respawnable);
}

