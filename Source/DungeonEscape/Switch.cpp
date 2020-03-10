// Copyright Frank Severijns 2020


#include "Switch.h"

// Sets default values for this component's properties
USwitch::USwitch()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void USwitch::BeginPlay()
{
	Super::BeginPlay();

	if(AffectedActors.Num() == 0)
	{
		UE_LOG(LogTemp, Warning, TEXT("%s does not specify any affected actors!"), *GetOwner()->GetName());
		return;
	}

	for(AActor* Actor : AffectedActors)
	{
		TArray<USwitchObserver*> Observers;
		Actor->GetComponents<USwitchObserver>(Observers);

		if(Observers.Num() == 0)
		{
			UE_LOG(LogTemp, Warning, TEXT("%s is assigned to %s as an affected actor, but has no Components that derive from USwitchObserver!"), *Actor->GetName(), *GetOwner()->GetName());
			continue;
		}

		SwitchObservers.Append(Observers);
		UE_LOG(LogTemp, Warning, TEXT("%s appended %i Switch Observers!"), *Actor->GetName(), Observers.Num());
	}	
}


// Called every frame
void USwitch::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void USwitch::NotifyObservers(const bool bSwitchState)
{
	bCurrentSwitchState = bSwitchState;
	
	for(USwitchObserver* Observer : SwitchObservers)
	{
		UE_LOG(LogTemp, Warning, TEXT("Notifying observer %s"), *Observer->GetOwner()->GetName());
		Observer->OnSwitchStateChanged(bSwitchState);
	}
}

