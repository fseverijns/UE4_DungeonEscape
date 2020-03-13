// Copyright Frank Severijns 2020


#include "MultiSwitch.h"

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

	for(FSubSwitch SubSwitch : Switches)
	{
		if(!SubSwitch.SwitchActor || SubSwitch.SwitchActor == nullptr)
		{
			UE_LOG(LogTemp, Warning, TEXT("MultiSwitch %s has an unassigned SubSwitch!"), *GetOwner()->GetName());
			return;
		}

		SubSwitch.Switch = SubSwitch.SwitchActor->FindComponentByClass<USwitch>();
		if(!SubSwitch.Switch || SubSwitch.Switch == nullptr)
		{
			UE_LOG(LogTemp, Warning, TEXT("MultiSwitch %s has SubSwitch %s, but the SubSwitch Actor has no derivative of Switch attached!"), *GetOwner()->GetName(), *SubSwitch.SwitchActor->GetName());
			return;
		}
		else if(SubSwitch.Switch == this)
		{
			UE_LOG(LogTemp, Warning, TEXT("SubSwitch assignment error on %s: You cannot assign a MultiSwitch to itself!"), *GetOwner()->GetName());
			return;
		}
	}
}


// Called every frame
void UMultiSwitch::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	bool bSubSwitchStatesCorrect = CheckSubSwitchStates();
	if(bSubSwitchStatesCorrect &&  !bCurrentSwitchState)
	{
		NotifyObservers(true);
	}
	else if(!bSubSwitchStatesCorrect && bCurrentSwitchState)
	{
		NotifyObservers(false);
	}

	bCurrentSwitchState = bSubSwitchStatesCorrect;
}

bool UMultiSwitch::CheckSubSwitchStates()
{
	for(FSubSwitch SubSwitch : Switches)
	{
		if(SubSwitch.Switch->GetSwitchState() != SubSwitch.bDesiredState)
		{
			return false;
		}
	}

	return true;
}

