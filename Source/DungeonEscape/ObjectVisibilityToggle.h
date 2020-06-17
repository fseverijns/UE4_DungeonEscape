// Copyright Frank Severijns 2020

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "GameFramework/Actor.h"
#include "Switchable.h"
#include "ObjectVisibilityToggle.generated.h"

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class DUNGEONESCAPE_API UObjectVisibilityToggle : public USwitchable
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UObjectVisibilityToggle();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;
	virtual void ChangeActivationState(const bool bNewState, bool bPlaySound = true) override;
	// Reset the object to its initial state
	virtual void OnPlayerRespawn() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

private: 
	UPROPERTY(EditAnywhere)
	bool bVisibleByDefault = true;
};
