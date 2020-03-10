// Copyright Frank Severijns 2020


#include "ObjectTranslator.h"

// Sets default values for this component's properties
UObjectTranslator::UObjectTranslator()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UObjectTranslator::BeginPlay()
{
	Super::BeginPlay();

	USceneComponent* Object = GetOwner()->GetRootComponent();

	Object->SetRelativeLocation(ObjectStartPosition);	
}


// Called every frame
void UObjectTranslator::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UObjectTranslator::ProcessActivationState(const float DeltaTime)
{
	if(bTransformInProgress)
	{
		float Delay = 0.0f;

		if(bActivationState)
		{
			Delay = TransformDelay;
		}
		else
		{
			Delay = ReverseDelay;
		}

		if(DelayTimer < Delay)
		{
			DelayTimer += DeltaTime;
			return;
		}

		if(bActivationState)
		{
			TranslationAlpha += DeltaTime * TransformSpeed;
			if(TranslationAlpha > 1)
			{
				bTransformInProgress = false;
				DelayTimer = 0.0f;
				TranslationAlpha = 1;
			}	
		}
		else
		{
			TranslationAlpha -= DeltaTime * ReverseSpeed;
			if(TranslationAlpha < 0)
			{
				bTransformInProgress = false;
				DelayTimer = 0.0f;
				TranslationAlpha = 0;
			}	
		}

		Translate();	
	}
}

void UObjectTranslator::Translate()
{
	USceneComponent* Object = GetOwner()->GetRootComponent();

	FVector NewPosition = FMath::Lerp(ObjectStartPosition, ObjectEndPosition, TranslationAlpha);

	Object->SetRelativeLocation(NewPosition);
}


