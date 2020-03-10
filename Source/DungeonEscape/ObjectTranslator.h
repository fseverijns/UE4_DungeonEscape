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

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	// Processes activation logic
	virtual void ProcessActivationState(const float DeltaTime) override;

private:
	void Translate();

private:
	UPROPERTY(EditAnywhere)
	FVector ObjectStartPosition = FVector(0,0,0);

	UPROPERTY(EditAnywhere)
	FVector ObjectEndPosition = FVector(1,1,1);

	FVector ObjectPosition;
	float TranslationAlpha = 0.0f;		
};
