// Copyright Frank Severijns 2020

#include "MultiSwitch.h"
#include "Switchable.h"

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

// Check the validity of each SubSwitchable and create pointers to their Switchable components
void UMultiSwitch::Initialize()
{
	for(FSubSwitchable& SubSwitchable : SubSwitchables)
	{
		if(!SubSwitchable.SwitchableActor || SubSwitchable.SwitchableActor == nullptr) // Ensure the actor is not null
		{
			UE_LOG(LogTemp, Warning, TEXT("MultiSwitch %s has an unassigned SubSwitchable!"), *GetOwner()->GetName());
			return;
		}

		SubSwitchable.Switchable = SubSwitchable.SwitchableActor->FindComponentByClass<USwitchable>();
		if(!SubSwitchable.Switchable || SubSwitchable.Switchable == nullptr) // Ensure the actor has a Switchable derived component
		{
			UE_LOG(LogTemp, Warning, TEXT("MultiSwitch %s has SubSwitchable %s, but the SubSwitch Actor has no derivative of Switchable attached!"), *GetOwner()->GetName(), *SubSwitchable.SwitchableActor->GetName());
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

	bool bSubSwitchStatesCorrect = CheckSubSwitchStates(); // Check the subSwitchables states
	if(bSubSwitchStatesCorrect &&  !bCurrentSwitchState) // If the subSwitchables are all in their desired states since the last tick (we don't want to spam this notification), notify the actual Switchables
	{
		NotifySwitchables(true);
	}
	else if(!bSubSwitchStatesCorrect && bCurrentSwitchState) // If the subSwitchables are not in their desired state anymore, notify the actual Switchables
	{
		NotifySwitchables(false);
	}

	bCurrentSwitchState = bSubSwitchStatesCorrect; // Update the switch state based on the state of the subSwitchables
}

// Iterate through the SubSwitchables to determine if they are all in their desired state
bool UMultiSwitch::CheckSubSwitchStates()
{
	for(FSubSwitchable SubSwitch : SubSwitchables)
	{
		if(SubSwitch.Switchable && SubSwitch.Switchable != nullptr)
		{
			if(SubSwitch.Switchable->GetCurrentState() != SubSwitch.bDesiredState)
			{
				return false; // A SubSwitchable was found not in the desired state, return false 
			}
		}
		else // A SubSwitchable is somehow no longer valid (null), return false and log a warning
		{	
			UE_LOG(LogTemp, Warning, TEXT("MultiSwitch %s is trying to evaluate a non-existent Switchable!"), *GetOwner()->GetName());
			return false;
		}
		
	}

	return true; // All SubSwitchables are in their desired state, return true
}

