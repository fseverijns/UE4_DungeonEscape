// Copyright Frank Severijns 2020


#include "KeyItemInventory.h"

// Sets default values for this component's properties
UKeyItemInventory::UKeyItemInventory()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UKeyItemInventory::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UKeyItemInventory::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

// Sets the specified key item's collected state to true or false (when picking up or resetting a key item)
void UKeyItemInventory::SetItemCollected(EKeyItemId KeyItemId, bool bCollectedState)
{
	bool bItemFound = false;
	for(FKeyItem& KeyItem : KeyItems)
	{
		if(KeyItem.KeyItemId == KeyItemId)
		{
			if(bCollectedState)
			{
				UE_LOG(LogTemp, Warning, TEXT("Set item as collected")); 
			}
			else
			{
				UE_LOG(LogTemp, Warning, TEXT("Set item as uncollected")); 
			}	
			KeyItem.bCollected = bCollectedState;
			bItemFound = true;
		}
	}

	if(!bItemFound)
	{
		if(bCollectedState)
		{
			UE_LOG(LogTemp, Warning, TEXT("Set NEW item as collected")); 
		}
		else
		{
			UE_LOG(LogTemp, Warning, TEXT("Set NEW item as uncollected")); 
		}
		KeyItems.Add(FKeyItem(KeyItemId, bCollectedState));
	}
}

// Query the collected state of a Key Item (e.g. to use an InteractWithKeyItemSwitch)
bool UKeyItemInventory::HasCollectedItem(EKeyItemId KeyItemId)
{
	for(FKeyItem& KeyItem : KeyItems)
	{
		if(KeyItem.KeyItemId == KeyItemId)
		{
			if(KeyItem.bCollected)
			{
				UE_LOG(LogTemp, Warning, TEXT("Item is collected")); 
			}	
			return KeyItem.bCollected;
		}
	}

	return false;
}

void UKeyItemInventory::AddCoinsCollected(int Amount)
{
	CoinsCollected += Amount;
}

void UKeyItemInventory::RemoveCoinsCollected(int Amount)
{
	CoinsCollected -= Amount;
}

int UKeyItemInventory::GetCoinsCollected()
{
	return CoinsCollected;
}

