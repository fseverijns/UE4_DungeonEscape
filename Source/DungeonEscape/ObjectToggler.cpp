// Copyright Frank Severijns 2020


#include "ObjectToggler.h"

// Sets default values for this component's properties
UObjectToggler::UObjectToggler()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UObjectToggler::BeginPlay()
{
	Super::BeginPlay();

	// Because we need the TickComponent function to count towards the auto-reset delay, check if these settings aren't conflicting.
	if(bToggleTicks && bAutoReset)
	{
		UE_LOG(LogTemp, Warning, TEXT("%s ObjectToggler is set to disable ticks and to automatically reset. To automatically reset, the actor must be able to Tick its components!"), *GetOwner()->GetName()) // Since these settings are incompatible, log a warning
	}

	// If the toggles should automatically reset, there should be a delay (otherwise toggling will essentially have no effect at all)
	if(bAutoReset && AutoResetDelay == 0.f)
	{
		UE_LOG(LogTemp, Warning, TEXT("%s ObjectToggler is set to auto reset, but it has no delay. Without a delay, the toggle essentially does nothing!"), *GetOwner()->GetName()) // Since these settings are nonsensical, log a warning
	}

	if(bOnByDefault)
	{
		ChangeActivationState(true);
	}
	else
	{
		ChangeActivationState(false);
	}
	
}


// Called every frame
void UObjectToggler::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// If any of the toggles were changed
	if(bAutoReset && bToggleStateChanged)
	{
		ResetTimer += DeltaTime;

		if(ResetTimer >= AutoResetDelay)
		{
			ChangeActivationState(bOnByDefault); // Reset to the default state
		}
	}
}

void UObjectToggler::ChangeActivationState(const bool bNewState)
{	
	bToggleStateChanged = false; 
	if(bToggleCollision)
	{
		GetOwner()->SetActorEnableCollision(bNewState);
	}
	if(bToggleVisibility)
	{
		GetOwner()->SetActorHiddenInGame(bNewState);
	}
	if(bToggleTicks)
	{
		GetOwner()->SetActorTickEnabled(bNewState);
	}

	// If the new state is not the default state
	if(bNewState != bOnByDefault) 
	{
		ResetTimer = 0.f;
		bToggleStateChanged = true;
	}
}

