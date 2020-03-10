// Copyright Frank Severijns 2020

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/ActorComponent.h"
#include "SwitchObserver.h"
#include "Switch.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class DUNGEONESCAPE_API USwitch : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	USwitch();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;
	void NotifyObservers(const bool bSwitchState);

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

protected:
	// Which actor are affected by the switch (actor must contain at least one ActorComponent deriving from Switch Observer to be affected)
	UPROPERTY(EditAnywhere)
	TArray<AActor*> AffectedActors;

	TArray<USwitchObserver*> SwitchObservers;

	bool bCurrentSwitchState;
};
