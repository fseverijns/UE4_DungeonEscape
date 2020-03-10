// Copyright Frank Severijns 2020


#include "TriggerSwitch.h"

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

	if(TriggerActivationType == ETriggerActivationType::Weight)
	{
		float Weight = OtherComponent->GetMass();
		AddWeight(Weight);
	}
	else if(TriggerActivationType == ETriggerActivationType::ActorOfType)
	{
		if(OtherActor->IsA<>(ActorType))
		{
			NotifyObservers(true);
		}
	}
	else if(TriggerActivationType == ETriggerActivationType::Actor)
	{
		if(OtherActor == Actor)
		{
			NotifyObservers(true);
		}
	}
	else if(TriggerActivationType == ETriggerActivationType::Player)
	{
		if(OtherActor == GetWorld()->GetFirstPlayerController()->GetParentActor())
		{
			NotifyObservers(true);
		}
	}
	
}

void UTriggerSwitch::OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComponent, int32 OtherBodyIndex)
{
	UE_LOG(LogTemp, Warning, TEXT("OVERLAP END!"));
	if(TriggerActivationType == ETriggerActivationType::Weight)
	{
		float Weight = OtherComponent->GetMass();
		DeductWeight(Weight);
	}
	else if(TriggerActivationType == ETriggerActivationType::ActorOfType)
	{
		if(OtherActor->IsA<>(ActorType))
		{
			NotifyObservers(false);
		}
	}
	else if(TriggerActivationType == ETriggerActivationType::Actor)
	{
		if(OtherActor == Actor)
		{
			NotifyObservers(false);
		}
	}
	else if(TriggerActivationType == ETriggerActivationType::Player)
	{
		if(OtherActor == GetWorld()->GetFirstPlayerController()->GetParentActor())
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