// Copyright Frank Severijns 2020

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Components/PrimitiveComponent.h"
#include "Engine/TriggerBase.h"
#include "GameFramework/Actor.h"
#include "GameFramework/PlayerController.h"
#include "Checkpoint.generated.h"

// Forward Declarations
class IRespawnable;
class UPlayerRespawner;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class DUNGEONESCAPE_API UCheckpoint : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UCheckpoint();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;
	// Called when player enters the trigger volume
	UFUNCTION()
	void OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComponent, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	// Called when player character dies
	void RespawnPlayer();
	

private:
	// The trigger actor
	ATriggerBase* TriggerActor;
	// Has player entered the checkpoint
	bool bPlayerEnteredCheckpoint = false;
	// The respawn coordinates
	FVector RespawnLocation;
	// The player rotation at respawn
	FRotator RespawnRotation;
	// The player actor
	AActor* PlayerActor;
};
