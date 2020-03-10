// Copyright Frank Severijns 2020

#pragma once

#include "CoreMinimal.h"
#include "Components/PrimitiveComponent.h"
#include "Engine/TriggerBase.h"
#include "GameFramework/Actor.h"
#include "GameFramework/PlayerController.h"
#include "Switch.h"
#include "TriggerSwitch.generated.h"

UENUM(BlueprintType)
enum class ETriggerActivationType: uint8 
{
	Weight,
	Player,
	Actor,
	ActorOfType
};

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class DUNGEONESCAPE_API UTriggerSwitch : public USwitch
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UTriggerSwitch();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	// When a component enters the trigger
	UFUNCTION()
	void OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComponent, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	// When a component exits the trigger
	UFUNCTION()
	void OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComponent, int32 OtherBodyIndex);	

private:
	//Add a weight that has just entered the trigger
	void AddWeight(float Weight);
	//Deduct a weight that has just left the trigger
	void DeductWeight(float Weight);

	// Which type of activation the trigger will respond to
	UPROPERTY(EditAnywhere)
	ETriggerActivationType TriggerActivationType;

	// The minimum weight threshold the trigger responds to (Weight activation only)
	UPROPERTY(EditAnywhere)
	float WeightThreshold;

	// Which type of Actor the trigger responds to (ActorOfType activation only)
	UPROPERTY(EditAnywhere)
	TSubclassOf<AActor> ActorType;

	// Which Actor the trigger responds to (Actor activation only)
	UPROPERTY(EditAnywhere)
	AActor* Actor;

	// Whether or not to respond to something leaving the trigger 
	UPROPERTY(EditAnywhere)
	bool bDetectTriggerExit;

	// The trigger actor
	ATriggerBase* TriggerActor;

	// The current weight inside this trigger
	float CurrentWeight = 0;
};
