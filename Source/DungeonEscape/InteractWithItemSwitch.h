// Copyright Frank Severijns 2020

#pragma once

#include "CoreMinimal.h"
#include "Engine/World.h"
#include "GameFramework/Actor.h"
#include "GameFramework/PlayerController.h"
#include "KeyItemInventory.h"
#include "InteractSwitch.h"
#include "InteractWithItemSwitch.generated.h"

/* 	Derivate of Interact Switch. Notifies Switchables to change their state.
*	Responds to player interacting with the actor (by pressing interact key).
*	The player needs a Key Item in order to interact.
*/
UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class DUNGEONESCAPE_API UInteractWithItemSwitch : public UInteractSwitch
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this component's properties
	UInteractWithItemSwitch();
	
protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	// Check if conditions for interaction are present
	bool InteractAllowed();

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	
	// Called when player interacts with switch
	virtual void OnInteractStart() override;

	// Called when player interacts with switch
	virtual void OnInteractStop() override;

protected:
	// The Key Item required to interact
	UPROPERTY(EditAnywhere)
	EKeyItemId KeyItemId = EKeyItemId::LeverHandle;

	UKeyItemInventory* Inventory = nullptr;
};
