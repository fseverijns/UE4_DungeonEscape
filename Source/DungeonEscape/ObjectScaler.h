// Copyright Frank Severijns 2020

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "GameFramework/Actor.h"
#include "ObjectTransformer.h"
#include "ObjectScaler.generated.h"

/* 	A Switchable derivative. Can be assigned to any Switch component.
*	When activated/deactivated, it Lerps the scale from its start and end state (and vice versa).
*/
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class DUNGEONESCAPE_API UObjectScaler : public UObjectTransformer
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UObjectScaler();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;
	// Translates the object
	virtual void Transform(float DeltaTime, bool& out_bTransformCompleted) override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	// Reset the object to its initial state
	virtual void OnPlayerRespawn() override;
	

private:
	void Translate();

private:
	UPROPERTY(EditAnywhere)
	FVector ObjectStartScale = FVector(1,1,1);

	UPROPERTY(EditAnywhere)
	FVector ObjectEndScale = FVector(2,2,2);
};
