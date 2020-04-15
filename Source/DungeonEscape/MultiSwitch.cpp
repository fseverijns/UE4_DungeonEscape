// Copyright Frank Severijns 2020

#include "MultiSwitch.h"
#include "SwitchObserver.h"

// Sets default values for this component's properties
UMultiSwitch::UMultiSwitch()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UMultiSwitch::BeginPlay()
{
	Super::BeginPlay();

	Initialize();
}

// Check the validity of each SubSwitchObserver and create pointers to their SwitchObserver components
void UMultiSwitch::Initialize()
{
	for(FSubSwitchObserver& SubSwitchObserver : SubSwitchObservers)
	{
		if(!SubSwitchObserver.SwitchObserverActor || SubSwitchObserver.SwitchObserverActor == nullptr) // Ensure the actor is not null
		{
			UE_LOG(LogTemp, Warning, TEXT("MultiSwitch %s has an unassigned SubSwitchObserver!"), *GetOwner()->GetName());
			return;
		}

		SubSwitchObserver.SwitchObserver = SubSwitchObserver.SwitchObserverActor->FindComponentByClass<USwitchObserver>();
		if(!SubSwitchObserver.SwitchObserver || SubSwitchObserver.SwitchObserver == nullptr) // Ensure the actor has a SwitchObserver derived component
		{
			UE_LOG(LogTemp, Warning, TEXT("MultiSwitch %s has SubSwitchObserver %s, but the SubSwitch Actor has no derivative of SwitchObserver attached!"), *GetOwner()->GetName(), *SubSwitchObserver.SwitchObserverActor->GetName());
			return;
		}
	}

	bInitialized = true;
}


// Called every frame
void UMultiSwitch::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if(!bInitialized) // Do not tick if initialization is incomplete
	{
		return;
	}

	bool bSubSwitchStatesCorrect = CheckSubSwitchStates(); // Check the subswitchobservers states
	if(bSubSwitchStatesCorrect &&  !bCurrentSwitchState) // If the subswitchobservers are all in their desired states since the last tick (we don't want to spam this notification), notify the actual observers
	{
		NotifyObservers(true);
	}
	else if(!bSubSwitchStatesCorrect && bCurrentSwitchState) // If the subswitchobservers are not in their desired state anymore, notify the actual observers
	{
		NotifyObservers(false);
	}

	bCurrentSwitchState = bSubSwitchStatesCorrect; // Update the switch state based on the state of the subswitchobservers
}

// Iterate through the SubSwitchObservers to determine if they are all in their desired state
bool UMultiSwitch::CheckSubSwitchStates()
{
	for(FSubSwitchObserver SubSwitch : SubSwitchObservers)
	{
		if(SubSwitch.SwitchObserver && SubSwitch.SwitchObserver != nullptr)
		{
			if(SubSwitch.SwitchObserver->GetCurrentState() != SubSwitch.bDesiredState)
			{
				return false; // A SubSwitchObserver was found not in the desired state, return false 
			}
		}
		else // A SubSwitchObserver is somehow no longer valid (null), return false and log a warning
		{	
			UE_LOG(LogTemp, Warning, TEXT("MultiSwitch %s is trying to evaluate a non-existent switch observer!"), *GetOwner()->GetName());
			return false;
		}
		
	}

	return true; // All SubSwitchObservers are in their desired state, return true
}

