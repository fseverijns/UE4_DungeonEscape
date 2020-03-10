// Copyright Frank Severijns 2020

#pragma once

#include "CoreMinimal.h"
#include "Switch.h"
#include "InteractSwitch.generated.h"

/**
 * 
 */
UCLASS()
class DUNGEONESCAPE_API UInteractSwitch : public USwitch
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UInteractSwitch();
	
protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

};
