// Copyright Frank Severijns 2020

#include "InteractWithItemSwitch.h"

UInteractWithItemSwitch::UInteractWithItemSwitch()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

}


// Called when the game starts
void UInteractWithItemSwitch::BeginPlay()
{
	Super::BeginPlay();
}


// Called every frame
void UInteractWithItemSwitch::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

// Check if player has the Key Item required, then interact if true.
void UInteractWithItemSwitch::OnInteractStart()
{
	UE_LOG(LogTemp, Warning, TEXT("INTERACTING"));
	if(!Inventory || Inventory == nullptr) // First get the Inventory component from the player
	{
		AActor* Player = GetWorld()->GetFirstPlayerController()->GetPawn();
		Inventory = Player->FindComponentByClass<UKeyItemInventory>();
	}

	if(Inventory && Inventory != nullptr)
    {
        if(Inventory->HasCollectedItem(KeyItemId)) // Check if the Key Item is marked as collected in the inventory
		{
			UInteractSwitch::OnInteractStart();
		}
    }
}