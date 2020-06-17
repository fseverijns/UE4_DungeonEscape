// Copyright Frank Severijns 2020

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "GameFramework/Actor.h"
#include "Switch.h"
#include "MultiSwitch.generated.h"

// Forward Declarations
class USwitchable;

// A struct were a Switchable and its desired state is specified
USTRUCT()
struct FSubSwitchable
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere)
	AActor* SwitchableActor = nullptr;
	UPROPERTY(EditAnywhere)
	bool bDesiredState;

	UPROPERTY()
	USwitchable* Switchable = nullptr;
};

/* 	A switch that is activated when all "SubSwitchables" appointed to it are set to a specified state
* 	Used to create, for example, a combination switch where the player must activate and deactivate certain Switchables
*	Note that the SubSwitchables are NOT notified when this switch changes state.
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
	// Validate and initialize the Switchable pointers
	void Initialize();

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

private:
	// The list of Switchables and their desired state
	UPROPERTY(EditAnywhere)
	TArray<FSubSwitchable> SubSwitchables;

	// The component is ready to Tick
	bool bInitialized = false;

	// Checks if all Switchables are at the desired state
	bool CheckSubSwitchStates();
};
