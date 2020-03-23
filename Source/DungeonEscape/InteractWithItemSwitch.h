// Copyright Frank Severijns 2020

#pragma once

#include "CoreMinimal.h"
#include "Engine/World.h"
#include "GameFramework/Actor.h"
#include "GameFramework/PlayerController.h"
#include "KeyItemInventory.h"
#include "InteractSwitch.h"
#include "InteractWithItemSwitch.generated.h"

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

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	
	// Called when player interacts with switch
	virtual void OnInteractStart() override;

protected:
	UPROPERTY(EditAnywhere)
	EKeyItemId KeyItemId = EKeyItemId::LeverHandle;

	UKeyItemInventory* Inventory = nullptr;
};
