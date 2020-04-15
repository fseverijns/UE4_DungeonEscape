// Copyright Frank Severijns 2020

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "GameFramework/Actor.h"
#include "Switch.h"
#include "MultiSwitch.generated.h"

// Forward Declarations
class USwitchObserver;

// A struct were a Switch Observer and its desired state is specified
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

/* 	A switch that is activated when all "SubSwitchObservers" appointed to it are set to a specified state
* 	Used to create, for example, a combination switch where the player must activate and deactivate certain SwitchObservers
*	Note that the SubSwitchObservers are NOT notified when this switch changes state.
*/
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
	// Validate and initialize the SwitchObserver pointers
	void Initialize();

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

private:
	// The list of switch observers and their desired state
	UPROPERTY(EditAnywhere)
	TArray<FSubSwitchObserver> SubSwitchObservers;

	// The component is ready to Tick
	bool bInitialized = false;

	// Checks if all SwitchObservers are at the desired state
	bool CheckSubSwitchStates();
};
