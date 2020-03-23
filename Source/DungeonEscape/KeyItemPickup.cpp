// Copyright Frank Severijns 2020


#include "KeyItemPickup.h"

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

	// ...
	
}


// Called every frame
void UKeyItemPickup::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UKeyItemPickup::PickUp()
{
	UE_LOG(LogTemp, Warning, TEXT("PickUp"));
	AActor* Player = GetWorld()->GetFirstPlayerController()->GetPawn();
	UKeyItemInventory* Inventory = Player->FindComponentByClass<UKeyItemInventory>();

	if(Inventory && Inventory != nullptr)
	{
		Inventory->SetItemCollected(KeyItemId, true);
		
		GetOwner()->SetActorHiddenInGame(true);
		GetOwner()->SetActorEnableCollision(false);

		if(PickupParticleFX && PickupParticleFX != nullptr)
		{
			PickupParticleFX->SetActorHiddenInGame(true);
		}

		UE_LOG(LogTemp, Warning, TEXT("Item picked up"));
	}
}


