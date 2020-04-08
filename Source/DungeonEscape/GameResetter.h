// Copyright Frank Severijns 2020

#pragma once

#include "CoreMinimal.h"
#include "GameResetter.generated.h"

// Forward Declarations
class IRespawnable;

UCLASS()
class DUNGEONESCAPE_API UGameResetter : public UObject
{
	GENERATED_BODY()

public:
	UGameResetter();
	~UGameResetter();

	// Registers a respawnable so it resets on player death
	void RegisterRespawnable(IRespawnable* Respawnable, FString Name = "Respawnable");
	// Resets the respawnables to their original state
	void ResetRespawnables();
	// When the player reaches a checkpoint
	void OnPlayerCheckpointReached();
	// Unregisters a respawnable so its state no longer changes on player death
	void UnregisterRespawnable(IRespawnable* Respawnable);
	

private:
	// Array of respawnables to reset on player death
	TArray<IRespawnable*> Respawnables;
};
