// Copyright Frank Severijns 2020


#include "AmbienceController.h"

// Sets default values
AAmbienceController::AAmbienceController()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AAmbienceController::BeginPlay()
{
	Super::BeginPlay();

	FindAudioComponent();
}

void AAmbienceController::FindAudioComponent()
{
	AudioComponent = FindComponentByClass<UAudioComponent>();
	if(!AudioComponent || AudioComponent == nullptr)
	{
		AudioComponent = CreateDefaultSubobject<UAudioComponent>(FName("Audio"));
	}
}

// Called every frame
void AAmbienceController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if(AudioComponent && AudioComponent != nullptr)
	{
		if(!AudioComponent->IsPlaying() && AmbienceTracks.Num() > 0)
		{
			PlayAmbienceTrack();
		}
	}	
}

void AAmbienceController::PlayAmbienceTrack()
{
	int trackIndex = FMath::RandRange(0, AmbienceTracks.Num()-1);
	AudioComponent->SetSound(AmbienceTracks[trackIndex]);
	AudioComponent->SetVolumeMultiplier(0.25f);
	AudioComponent->Play();
}

