// Copyright Frank Severijns 2020

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "GameFramework/Actor.h"
#include "Switch.h"
#include "MultiSwitch.generated.h"

// Forward Declarations
class USwitchObserver;

USTRUCT()
struct FSubSwitchObserver
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere)
	AActor* SwitchObserverActor = nullptr;
	UPROPERTY(EditAnywhere)
	bool bDesiredState;

	UPROPERTY()
	USwitchObserver* SwitchObserver = nullptr;
};

// A switch that is activated when all switchobservers appointed to it are set to a certain state
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class DUNGEONESCAPE_API UMultiSwitch : public USwitch
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UMultiSwitch();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

private:
	UPROPERTY(EditAnywhere)
	TArray<FSubSwitchObserver> SubSwitchObservers;

	bool bCurrentState = false;
	bool bInitialized = false;

	bool CheckSubSwitchStates();
};
