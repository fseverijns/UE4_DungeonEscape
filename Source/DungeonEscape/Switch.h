// Copyright Frank Severijns 2020

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/ActorComponent.h"
#include "Respawnable.h"
#include "Switch.generated.h"

// Forward Declarations
class USwitchObserver;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class DUNGEONESCAPE_API USwitch : public UActorComponent, public IRespawnable
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	USwitch();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;
	void NotifyObservers(const bool bSwitchState);
	// Reset the object to its initial state
	virtual void OnPlayerRespawn() override;
	// Evaluate and unregister respawnable
	virtual void OnCheckpointReached() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	// Gets the current switch state
	bool GetSwitchState();

protected:
	// If true, the affected switch observers are not synchronized with the switch state, but instead their state is based on their previous state
	UPROPERTY(EditAnywhere)
	bool bIsToggle = false;

	// Which actor are affected by the switch (actor must contain at least one ActorComponent deriving from Switch Observer to be affected)
	UPROPERTY(EditAnywhere)
	TArray<AActor*> AffectedActors;

	TArray<USwitchObserver*> SwitchObservers;
	bool bCurrentSwitchState;
	bool bDefaultSwitchState;

public:
	// Get switch observers of the specified type
	// This is just to try out template functions, it serves no actual purpose (yet)!
	template <typename T>
	FORCEINLINE TArray<T*> GetObserversOfType()
	{
		TArray<T*> ObserversOfType;
		for(USwitchObserver* SwitchObserver : SwitchObservers)
		{
			T* Observer = Cast<T>(SwitchObserver);
			if(Observer && Observer != nullptr)
			{
				ObserversOfType.Add(Observer);
			}
		}

		return ObserversOfType;
	}
};
