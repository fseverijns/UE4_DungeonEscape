// Copyright Frank Severijns 2020

#include "InteractSwitch.h"

UInteractSwitch::UInteractSwitch()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UInteractSwitch::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UInteractSwitch::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UInteractSwitch::OnInteractStart()
{
	NotifyObservers(!bCurrentSwitchState);
}

void UInteractSwitch::OnInteractStop()
{
	if(bDetectInteractRelease)
	{
		NotifyObservers(!bCurrentSwitchState);
	}
}