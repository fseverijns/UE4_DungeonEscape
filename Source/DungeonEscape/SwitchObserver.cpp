// Copyright Frank Severijns 2020

#include "SwitchObserver.h"

// Sets default values for this component's properties
USwitchObserver::USwitchObserver()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void USwitchObserver::BeginPlay()
{
	Super::BeginPlay();

	ChangeActivationState(bDefaultState);

	RegisterRespawnable();
}


// Called every frame
void USwitchObserver::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void USwitchObserver::OnSwitchStateChanged(const bool bSwitchState)
{
	UE_LOG(LogTemp, Warning, TEXT("%s switch state has changed"), *GetOwner()->GetName());
	ChangeActivationState(bInvertActivation ? !bSwitchState : bSwitchState);
}

void USwitchObserver::ChangeActivationState(const bool bNewState)
{
	bActivationState = bNewState;
	
	// Implemented by derived classes
}

bool USwitchObserver::GetCurrentState()
{
	return bActivationState;
}

void USwitchObserver::RegisterRespawnable()
{	
	
}

void USwitchObserver::OnPlayerRespawn()
{	
	ChangeActivationState(bDefaultState);

	// Implemented by derivived classes
}

void USwitchObserver::OnCheckpointReached()
{	
	if(bActivationState != bDefaultState)
	{
		
	}
}

