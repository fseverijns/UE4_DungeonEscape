// Copyright Frank Severijns 2020

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "Respawnable.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class URespawnable : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class DUNGEONESCAPE_API IRespawnable
{
	GENERATED_BODY()

	
public:
	// Register the respawnable, making the system aware that this object should reset on player death
	virtual void RegisterRespawnable();
	// Reset the object to its original state
	virtual void OnPlayerRespawn();
	// Evaluate whether the object is still viable for resetting
	virtual void OnCheckpointReached();
};
