// Copyright Frank Severijns 2020

#include "TriggerSwitch.h"
#include "PlayerCharacter.h"

UTriggerSwitch::UTriggerSwitch()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
}


// Called when the game starts
void UTriggerSwitch::BeginPlay()
{
	Super::BeginPlay();

	TriggerActor = Cast<ATriggerBase>(GetOwner());
	if(TriggerActor && TriggerActor != nullptr)
	{
		UPrimitiveComponent* PrimitiveComponent = TriggerActor->FindComponentByClass<UPrimitiveComponent>();
		if(PrimitiveComponent)
		{
			PrimitiveComponent->OnComponentBeginOverlap.AddDynamic(this, &UTriggerSwitch::OnOverlapBegin);

			if(bDetectTriggerExit)
			{
				PrimitiveComponent->OnComponentEndOverlap.AddDynamic(this, &UTriggerSwitch::OnOverlapEnd);
			}
			
			UE_LOG(LogTemp, Warning, TEXT("%s OnComponentOverlap delegates are added!"), *GetOwner()->GetName());
		}
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("%s must be a Trigger Actor!"), *GetOwner()->GetName());
	}
}


// Called every frame
void UTriggerSwitch::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UTriggerSwitch::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComponent, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	UE_LOG(LogTemp, Warning, TEXT("OVERLAP BEGIN!"));

	if(TriggerActivationType == ETriggerActivationType::Weight) // Activated by weight
	{
		float Weight = 0.0f;
		APlayerCharacter* PlayerCharacter = Cast<APlayerCharacter>(OtherActor); // Because Player Actor physics are disabled, we need to get its weight from the PlayerCharacter class
		if(PlayerCharacter && PlayerCharacter != nullptr) // If the overlapping actor is the player we get the weight
		{
			Weight = PlayerCharacter->GetWeight();
		}
		else // The actor is not the player, get weight from the physics component
		{
			Weight = OtherComponent->GetMass();
		}
		AddWeight(Weight);
	}
	else if(TriggerActivationType == ETriggerActivationType::ActorOfType) // Activated by a type of Actor
	{
		if(OtherActor->IsA<>(ActorType))
		{
			NotifyObservers(true);
		}
	}
	else if(TriggerActivationType == ETriggerActivationType::Actor) // Activated by a specific Actor
	{
		if(OtherActor == Actor)
		{
			NotifyObservers(true);
		}
	}
	else if(TriggerActivationType == ETriggerActivationType::Player) // Activated by the player actor
	{
		if(OtherActor == GetWorld()->GetFirstPlayerController()->GetPawn())
		{
			NotifyObservers(true);
		}
	}
	
}

void UTriggerSwitch::OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComponent, int32 OtherBodyIndex)
{
	UE_LOG(LogTemp, Warning, TEXT("OVERLAP END!"));
	if(TriggerActivationType == ETriggerActivationType::Weight) // Deactivated by weight
	{
		float Weight = 0.0f;
		APlayerCharacter* PlayerCharacter = Cast<APlayerCharacter>(OtherActor); // Because Player Actor physics are disabled, we need to get its weight from the PlayerCharacter class
		if(PlayerCharacter && PlayerCharacter != nullptr) // If the overlapping actor is the player we get the weight
		{
			Weight = PlayerCharacter->GetWeight();
		}
		else // The actor is not the player, get weight from the physics component
		{
			Weight = OtherComponent->GetMass();
		}
		DeductWeight(Weight);
	} 
	else if(TriggerActivationType == ETriggerActivationType::ActorOfType) // Deactivated by a type of Actor
	{
		if(OtherActor->IsA<>(ActorType))
		{
			NotifyObservers(false);
		}
	}
	else if(TriggerActivationType == ETriggerActivationType::Actor) // Deactivated by a specific Actor
	{
		if(OtherActor == Actor)
		{
			NotifyObservers(false);
		}
	}
	else if(TriggerActivationType == ETriggerActivationType::Player) // Deactivated by the player actor
	{
		if(OtherActor == GetWorld()->GetFirstPlayerController()->GetPawn())
		{
			NotifyObservers(false);
		}
	}
}

//Add a weight that has just entered the trigger
void UTriggerSwitch::AddWeight(float Weight)
{	
	float NewWeight = CurrentWeight + Weight;

	// Notify the switch's observers if the new weight equals or exceeds the weight threshold
	if(CurrentWeight < WeightThreshold && NewWeight >= WeightThreshold)
	{
		NotifyObservers(true);
	}

	CurrentWeight = NewWeight;
}

//Deduct a weight that has just left the trigger
void UTriggerSwitch::DeductWeight(float Weight)
{
	float NewWeight = CurrentWeight - Weight;

	// Notify the switch's observers if the new weight is below the weight threshold
	if(CurrentWeight >= WeightThreshold && NewWeight < WeightThreshold)
	{
		NotifyObservers(false);
	}

	CurrentWeight = NewWeight;
}