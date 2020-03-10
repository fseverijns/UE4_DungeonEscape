// Copyright Frank Severijns 2020

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "GameFramework/Actor.h"
#include "ObjectTransformer.h"
#include "ObjectRotator.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class DUNGEONESCAPE_API UObjectRotator : public UObjectTransformer
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UObjectRotator();
	
protected:
	// Called when the game starts
	virtual void BeginPlay() override;
	// Processes activation logic
	virtual void ProcessActivationState(const float DeltaTime) override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

private:
	void Rotate();

private:
	UPROPERTY(EditAnywhere)
	FRotator ObjectStartRotation = FRotator(0,0,0);

	UPROPERTY(EditAnywhere)
	FRotator ObjectEndRotation = FRotator(0,90,0);

	FRotator ObjectRotation;
	float RotationAlpha = 0.0f;
};
