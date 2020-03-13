// Copyright Frank Severijns 2020

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "GameFramework/Actor.h"
#include "Switch.h"
#include "MultiSwitch.generated.h"

USTRUCT()
struct FSubSwitch
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere)
	AActor* SwitchActor;
	UPROPERTY(EditAnywhere)
	bool bDesiredState;

	USwitch* Switch = nullptr;

	FSubSwitch()
	{
		SwitchActor = nullptr;
		bDesiredState = false;
	}
};

// A switch that is activated when all switches appointed to it are set to a certain state
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class DUNGEONESCAPE_API UMultiSwitch : public USwitch
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UMultiSwitch();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

private:
	UPROPERTY(EditAnywhere)
	TArray<FSubSwitch> Switches;

	bool bCurrentState = false;

	bool CheckSubSwitchStates();
};
