// Copyright Frank Severijns 2020

#include "Switch.h"
#include "Respawnable.h"
#include "Engine/World.h"
#include "GameFramework/Actor.h"
#include "PlayerRespawner.h"
#include "Switchable.h"

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

	InitializeRespawner();

	RegisterRespawnable();

	bDefaultSwitchState = bCurrentSwitchState;

	if(AffectedActors.Num() == 0)
	{
		UE_LOG(LogTemp, Warning, TEXT("%s does not specify any affected actors!"), *GetOwner()->GetName());
		return;
	}

	for(AActor* Actor : AffectedActors)
	{
		if(Actor && Actor != nullptr)
		{
			TArray<USwitchable*> NewSwitchables;
			Actor->GetComponents<USwitchable>(NewSwitchables);

			if(NewSwitchables.Num() == 0)
			{
				UE_LOG(LogTemp, Warning, TEXT("%s is assigned to %s as an affected actor, but has no Components that derive from USwitchable!"), *Actor->GetName(), *GetOwner()->GetName());
				continue;
			}

			Switchables.Append(NewSwitchables);
			UE_LOG(LogTemp, Warning, TEXT("%s appended %i Switchables!"), *GetOwner()->GetName(), NewSwitchables.Num());
		}
	}	
}

void USwitch::InitializeRespawner()
{
	Respawner = GetWorld()->GetFirstPlayerController()->GetPawn()->FindComponentByClass<UPlayerRespawner>();
	if(!Respawner || Respawner == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("Could not locate a Player with the Player Respawner component!"));
	}
}

// Called every frame
void USwitch::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

bool USwitch::GetSwitchState()
{
	return bCurrentSwitchState;
}

void USwitch::NotifySwitchables(const bool bSwitchState)
{
	bCurrentSwitchState = bSwitchState;
	
	for(USwitchable* Switchable : Switchables)
	{
		UE_LOG(LogTemp, Warning, TEXT("Notifying Switchable %s"), *Switchable->GetOwner()->GetName());
		Switchable->OnSwitchStateChanged(bIsToggle ? !Switchable->GetCurrentState() : bSwitchState); // If the switch is a toggle, pass the inverted state of the Switchable, else pass the state of the switch
	}
}

void USwitch::RegisterRespawnable()
{	
	if(Respawner != nullptr)
	{
		Respawner->RegisterRespawnable(this);
	}
}

void USwitch::OnPlayerRespawn()
{	
	bCurrentSwitchState = bDefaultSwitchState;

	// Implemented by derivived classes
}

void USwitch::OnCheckpointReached()
{	
	if(bCurrentSwitchState != bDefaultSwitchState)
	{
		Respawner->UnregisterRespawnable(this);
	}
}

