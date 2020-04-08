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

	for(FSubSwitchObserver& SubSwitchObserver : SubSwitchObservers)
	{
		if(!SubSwitchObserver.SwitchObserverActor || SubSwitchObserver.SwitchObserverActor == nullptr)
		{
			UE_LOG(LogTemp, Warning, TEXT("MultiSwitch %s has an unassigned SubSwitchObserver!"), *GetOwner()->GetName());
			return;
		}

		SubSwitchObserver.SwitchObserver = SubSwitchObserver.SwitchObserverActor->FindComponentByClass<USwitchObserver>();
		if(!SubSwitchObserver.SwitchObserver || SubSwitchObserver.SwitchObserver == nullptr)
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

	if(!bInitialized)
	{
		return;
	}

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
	for(FSubSwitchObserver SubSwitch : SubSwitchObservers)
	{
		if(SubSwitch.SwitchObserver && SubSwitch.SwitchObserver != nullptr)
		{
			if(SubSwitch.SwitchObserver->GetCurrentState() != SubSwitch.bDesiredState)
			{
				return false;
			}
		}
		else
		{	
			UE_LOG(LogTemp, Warning, TEXT("MultiSwitch %s is trying to evaluate a non-existent switch observer!"), *GetOwner()->GetName());
			return false;
		}
		
	}

	return true;
}

