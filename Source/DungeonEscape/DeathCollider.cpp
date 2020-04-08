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

	PlayerActor = GetWorld()->GetFirstPlayerController()->GetPawn();

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
	if(OtherActor == PlayerActor)
	{
		UPlayerRespawner* Respawner = PlayerActor->FindComponentByClass<UPlayerRespawner>();
		if(Respawner && Respawner != nullptr)
		{
			Respawner->Kill();
		}
	}
	else if(bResetObjects)
	{
		UObjectRespawner* Respawner = OtherActor->FindComponentByClass<UObjectRespawner>();
		if(Respawner && Respawner != nullptr)
		{
			Respawner->Reset();
		}
	}
	
}

