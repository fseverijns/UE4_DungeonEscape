// Copyright Frank Severijns 2020

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "PlayerRespawner.generated.h"

// Forward Declarations
class UCheckpoint;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class DUNGEONESCAPE_API UPlayerRespawner : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UPlayerRespawner();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	// Called when the player enters a checkpoint
	void OnCheckpointReached(UCheckpoint* Checkpoint);
	// Kill the player character
	void Kill();

private:
	UCheckpoint* LastCheckpoint;
};
