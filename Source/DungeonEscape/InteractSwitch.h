// Copyright Frank Severijns 2020

#pragma once

#include "CoreMinimal.h"
#include "Switch.h"
#include "InteractSwitch.generated.h"

/* 	Derivate of Switch. Notifies Switchables to change their state.
*	Responds to player interacting with the actor (by pressing interact key).
*/
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) ) 
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
	
	// Called when player interacts with switch
	virtual void OnInteractStart();

	// Called when player stops interacting with switch (only when Detect Interact Release is enabled)
	virtual void OnInteractStop();

protected:
	// Switch should respond when the Interact button is released
	UPROPERTY(EditAnywhere)
	bool bDetectInteractRelease;
};
