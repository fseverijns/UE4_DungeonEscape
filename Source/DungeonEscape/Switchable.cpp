// Copyright Frank Severijns 2020

#include "Switchable.h"
#include "GameFramework/PlayerController.h"
#include "PlayerRespawner.h"

// Sets default values for this component's properties
USwitchable::USwitchable()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void USwitchable::BeginPlay()
{
	Super::BeginPlay();

	InitializeRespawner();

	ChangeActivationState(bDefaultState, false);

	InitializeAudioComponent();

	RegisterRespawnable();
}

void USwitchable::InitializeRespawner()
{
	Respawner = GetWorld()->GetFirstPlayerController()->GetPawn()->FindComponentByClass<UPlayerRespawner>();
	if(!Respawner || Respawner == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("Could not locate a Player with the Player Respawner component!"));
	}
}

void USwitchable::InitializeAudioComponent()
{
	if(!bUseSound) // Determine if the audio component is required
	{
		return;
	}

	AudioComponent = GetOwner()->FindComponentByClass<UAudioComponent>();
	if(!AudioComponent || AudioComponent == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("%s requires an Audio Component but none is attached!"), *GetName());
		return;
	}

	AudioComponent->bAutoActivate = false;
	if(AudioComponent->IsPlaying())
	{
		AudioComponent->Stop();
	}
}

// Called every frame
void USwitchable::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void USwitchable::OnSwitchStateChanged(const bool bSwitchState)
{
	UE_LOG(LogTemp, Warning, TEXT("%s switch state has changed"), *GetOwner()->GetName());
	ChangeActivationState(bInvertActivation ? !bSwitchState : bSwitchState);
}

void USwitchable::ChangeActivationState(const bool bNewState, bool bPlaySound)
{
	bActivationState = bNewState;

	if(bPlaySound)
	{
		PlayActivationSound();
	}

	// Implemented by derived classes
}

void USwitchable::PlayActivationSound()
{
	if(bUseSound && AudioComponent != nullptr)
	{
		if(bActivationState && ActivationSound != nullptr)
		{
			AudioComponent->SetSound(ActivationSound);
			AudioComponent->Play();
		}
		else if(!bActivationState && DeactivationSound != nullptr)
		{
			AudioComponent->SetSound(DeactivationSound);
			AudioComponent->Play();
		}
	}
}

bool USwitchable::GetCurrentState()
{
	return bActivationState;
}

void USwitchable::RegisterRespawnable()
{	
	if(Respawner != nullptr)
	{
		Respawner->RegisterRespawnable(this);
	}
}

void USwitchable::OnPlayerRespawn()
{	
	ChangeActivationState(bDefaultState, false);

	// Implemented by derivived classes
}

void USwitchable::OnCheckpointReached()
{	
	if(bActivationState != bDefaultState)
	{
		Respawner->UnregisterRespawnable(this);
	}
}

