// Copyright Frank Severijns 2020

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "GameFramework/Actor.h"
#include "ObjectTransformer.h"
#include "ObjectTranslator.generated.h"

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class DUNGEONESCAPE_API UObjectTranslator : public UObjectTransformer
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UObjectTranslator();

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
	FVector ObjectStartLocation = FVector(0,0,0);

	UPROPERTY(EditAnywhere)
	FVector ObjectEndLocation = FVector(1,1,1);
};
