// Copyright Frank Severijns 2020

#include "KeyItemPickup.h"
#include "PlayerRespawner.h" 

// Sets default values for this component's properties
UKeyItemPickup::UKeyItemPickup()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UKeyItemPickup::BeginPlay()
{
	Super::BeginPlay();

	InitializeRespawner();
	
	InitializeAudioComponent();

	RegisterRespawnable();
}

void UKeyItemPickup::InitializeRespawner()
{
	Respawner = GetWorld()->GetFirstPlayerController()->GetPawn()->FindComponentByClass<UPlayerRespawner>();
	if(!Respawner || Respawner == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("Could not locate a Player with the Player Respawner component!"));
	}
}

void UKeyItemPickup::InitializeAudioComponent()
{
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
void UKeyItemPickup::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UKeyItemPickup::PickUp()
{
	AActor* Player = GetWorld()->GetFirstPlayerController()->GetPawn(); // Get the player actor
	UKeyItemInventory* Inventory = Player->FindComponentByClass<UKeyItemInventory>(); // Get the inventory component

	// If the inventory component is found, mark the item as collected and hide the actor
	if(Inventory && Inventory != nullptr)
	{
		Inventory->SetItemCollected(KeyItemId, true);
		
		GetOwner()->SetActorHiddenInGame(true);
		GetOwner()->SetActorEnableCollision(false);

		// If a particle effect is associated with this pickup, hide that as well
		if(PickupParticleFX && PickupParticleFX != nullptr)
		{
			PickupParticleFX->SetActorHiddenInGame(true);
		}

		if(AudioComponent && AudioComponent != nullptr && PickupSound != nullptr)
		{
			AudioComponent->SetSound(PickupSound);
			AudioComponent->Play();
		}

		bCollected = true;
		UE_LOG(LogTemp, Warning, TEXT("Item picked up"));
	}
}

void UKeyItemPickup::RegisterRespawnable()
{	
	if(Respawner == nullptr)
	{
		return;
	}

	Respawner->RegisterRespawnable(this);
}

void UKeyItemPickup::OnPlayerRespawn()
{	
	if(!bCollected) // No change, no need to do anything
	{
		return;
	}

	AActor* Player = GetWorld()->GetFirstPlayerController()->GetPawn(); // Get the player actor
	UKeyItemInventory* Inventory = Player->FindComponentByClass<UKeyItemInventory>(); // Get the inventory component

	// If the inventory component is found, reset the item as uncollected and show the actor
	if(Inventory && Inventory != nullptr)
	{
		Inventory->SetItemCollected(KeyItemId, false);
			
		GetOwner()->SetActorHiddenInGame(false);
		GetOwner()->SetActorEnableCollision(true);

		// If a particle effect is associated with this pickup, reset that as well
		if(PickupParticleFX && PickupParticleFX != nullptr)
		{
			PickupParticleFX->SetActorHiddenInGame(false);
		}

		if(AudioComponent && AudioComponent != nullptr && AudioComponent->IsPlaying())
		{
			AudioComponent->Stop();
		}

		bCollected = false;
	}
}

void UKeyItemPickup::OnCheckpointReached()
{
	if(Respawner == nullptr)
	{
		return;
	}

	if(bCollected)
	{
		Respawner->UnregisterRespawnable(this);	
	}
}


