// Copyright Frank Severijns 2020

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "KeyItemInventory.generated.h"

// The Key Items
UENUM()
enum class EKeyItemId : uint8
{
	LeverHandle,
	PrisonKey,
	CrudeTool,
	ThroneRoomKey,
	MagicCrystal
};

// Struct where Key Items can be marked as collected
USTRUCT()
struct FKeyItem
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere)
	EKeyItemId KeyItemId;
	UPROPERTY(EditAnywhere)
	bool bCollected;

	FKeyItem()
	{
	}
	
	FKeyItem(EKeyItemId Id, bool bCol)
	{
		KeyItemId = Id;
		bCollected = bCol;
	}
};

/* The player's "inventory", where Key Items are marked as collected and where the collected items can be queried.
*/
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class DUNGEONESCAPE_API UKeyItemInventory : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UKeyItemInventory();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	// Set the specified key item's collected state to true or false
	void SetItemCollected(EKeyItemId KeyItemId, bool bCollectedState);
	// Gets the collected state of the specified key item
	bool HasCollectedItem(EKeyItemId KeyItemId);

private:
	TArray<FKeyItem> KeyItems;
};
