// Copyright Frank Severijns 2020

#include "DeathCollider.h"
#include "PlayerRespawner.h"
#include "ObjectRespawner.h"

// Sets default values for this component's properties
UDeathCollider::UDeathCollider()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UDeathCollider::BeginPlay()
{
	Super::BeginPlay();

	// Get the player actor
	PlayerActor = GetWorld()->GetFirstPlayerController()->GetPawn();

	// Add the delegate function to execute when the trigger overlaps a player or object
	TriggerActor = Cast<ATriggerBase>(GetOwner());
	if(TriggerActor && TriggerActor != nullptr)
	{
		UPrimitiveComponent* PrimitiveComponent = TriggerActor->FindComponentByClass<UPrimitiveComponent>();
		if(PrimitiveComponent)
		{
			PrimitiveComponent->OnComponentBeginOverlap.AddDynamic(this, &UDeathCollider::OnOverlapBegin);
			UE_LOG(LogTemp, Warning, TEXT("%s OnComponentOverlap delegates are added!"), *GetOwner()->GetName());
		}
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("%s must be a Trigger Actor!"), *GetOwner()->GetName());
	}
}


// Called every frame
void UDeathCollider::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UDeathCollider::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComponent, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	// If this trigger collides with the player actor, tell the PlayerRespawner to kill (respawn) the player character
	if(OtherActor == PlayerActor)
	{
		UPlayerRespawner* Respawner = PlayerActor->FindComponentByClass<UPlayerRespawner>();
		if(Respawner && Respawner != nullptr)
		{
			Respawner->Kill();
		}
	}
	else // check if whatever overlapped this trigger has an object respawner, then reset the object to its respawn location if true
	{
		UObjectRespawner* Respawner = OtherActor->FindComponentByClass<UObjectRespawner>();
		if(Respawner && Respawner != nullptr)
		{
			Respawner->Reset();
		}
	}
	
}

