// Copyright Frank Severijns 2020


#include "CoinPickup.h"
#include "PlayerRespawner.h"

// Sets default values for this component's properties
UCoinPickup::UCoinPickup()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UCoinPickup::BeginPlay()
{
	Super::BeginPlay();

	InitializeRespawner();

	InitializeAudioComponent();

	RegisterRespawnable();
}

void UCoinPickup::InitializeRespawner()
{
	Respawner = GetWorld()->GetFirstPlayerController()->GetPawn()->FindComponentByClass<UPlayerRespawner>();
	if(!Respawner || Respawner == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("Could not locate a Player with the Player Respawner component!"));
	}
}

void UCoinPickup::InitializeAudioComponent()
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
void UCoinPickup::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UCoinPickup::PickUp()
{
	AActor* Player = GetWorld()->GetFirstPlayerController()->GetPawn(); // Get the player actor
	UKeyItemInventory* Inventory = Player->FindComponentByClass<UKeyItemInventory>(); // Get the inventory component

	// If the inventory component is found, mark the item as collected and hide the actor
	if(Inventory && Inventory != nullptr)
	{
		Inventory->AddCoinsCollected(GoldValue);
		
		GetOwner()->SetActorHiddenInGame(true);
		GetOwner()->SetActorEnableCollision(false);

		if(AudioComponent && AudioComponent != nullptr && PickupSound != nullptr)
		{
			AudioComponent->SetSound(PickupSound);
			AudioComponent->Play();
		}

		bCollected = true;
		UE_LOG(LogTemp, Warning, TEXT("Gold picked up"));
	}
}

void UCoinPickup::RegisterRespawnable()
{	
	if(Respawner == nullptr)
	{
		return;
	}

	Respawner->RegisterRespawnable(this);
}

void UCoinPickup::OnPlayerRespawn()
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
		Inventory->RemoveCoinsCollected(GoldValue);
			
		GetOwner()->SetActorHiddenInGame(false);
		GetOwner()->SetActorEnableCollision(true);

		if(AudioComponent && AudioComponent != nullptr && AudioComponent->IsPlaying())
		{
			AudioComponent->Stop();
		}

		bCollected = false;
	}
}

void UCoinPickup::OnCheckpointReached()
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

