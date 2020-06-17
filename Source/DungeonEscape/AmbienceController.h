// Copyright Frank Severijns 2020

#pragma once

#include "CoreMinimal.h"
#include "Components/AudioComponent.h"
#include "GameFramework/Actor.h"
#include "Sound/SoundBase.h"
#include "AmbienceController.generated.h"

UCLASS()
class DUNGEONESCAPE_API AAmbienceController : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AAmbienceController();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Finds the audio component attached to this actor
	void FindAudioComponent();

	// Finds the audio component attached to this actor
	void PlayAmbienceTrack();

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:
	UPROPERTY(EditAnywhere)
	TArray<USoundBase*> AmbienceTracks;
	UAudioComponent* AudioComponent = nullptr;
};
