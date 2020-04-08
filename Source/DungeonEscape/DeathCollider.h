// Copyright Frank Severijns 2020

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Components/PrimitiveComponent.h"
#include "Engine/TriggerBase.h"
#include "GameFramework/Actor.h"
#include "GameFramework/PlayerController.h"
#include "DeathCollider.generated.h"

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class DUNGEONESCAPE_API UDeathCollider : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UDeathCollider();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;
	// Called when player enters the trigger volume
	UFUNCTION()
	void OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComponent, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

private:
	// Reset objects with the Object Respawner Component
	UPROPERTY(EditAnywhere)
	bool bResetObjects = true;
	// The trigger actor
	ATriggerBase* TriggerActor;
	// The player actor
	AActor* PlayerActor;
};
