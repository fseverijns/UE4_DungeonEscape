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

void UKeyItemInventory::SetItemCollected(EKeyItemId KeyItemId, bool bCollectedState)
{
	bool bItemFound = false;
	for(FKeyItem KeyItem : KeyItems)
	{
		if(KeyItem.KeyItemId == KeyItemId)
		{
			KeyItem.bCollected = bCollectedState;
			bItemFound = true;
		}
	}

	if(!bItemFound)
	{
		KeyItems.Add(FKeyItem(KeyItemId, bCollectedState));
	}
}

bool UKeyItemInventory::HasCollectedItem(EKeyItemId KeyItemId)
{
	for(FKeyItem KeyItem : KeyItems)
	{
		if(KeyItem.KeyItemId == KeyItemId)
		{
			return KeyItem.bCollected;
		}
	}

	return false;
}

