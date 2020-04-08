// Copyright Frank Severijns 2020

#include "GameResetter.h"
#include "Components/ActorComponent.h"
#include "GameFramework/Actor.h"
#include "Respawnable.h"
#include "Engine/World.h"

void UGameResetter::RegisterRespawnable(IRespawnable* Respawnable, FString Name)
{
	if(Respawnables.Contains(Respawnable))
	{
		UE_LOG(LogTemp, Warning, TEXT("Trying to register Respawnable %s, but it is already registered!"), *Name);
		return;
	}

	Respawnables.Add(Respawnable);

	UE_LOG(LogTemp, Warning, TEXT("Registered %s. (%i respawnables registered.)"), *Name, Respawnables.Num());
}

void UGameResetter::ResetRespawnables()
{
	for(IRespawnable* Respawnable : Respawnables)
	{
		if(Respawnable && Respawnable != nullptr)
		{
			Respawnable->OnPlayerRespawn();
		}
	}
}

void UGameResetter::OnPlayerCheckpointReached()
{
    for(IRespawnable* Respawnable : Respawnables)
    {
        Respawnable->OnCheckpointReached();
    }
}

void UGameResetter::UnregisterRespawnable(IRespawnable* Respawnable)
{
	Respawnables.Remove(Respawnable);
}
