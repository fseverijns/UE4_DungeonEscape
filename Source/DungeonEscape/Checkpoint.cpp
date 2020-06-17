// Copyright Frank Severijns 2020

#include "Checkpoint.h"
#include "PlayerRespawner.h"
#include "Respawnable.h"

// Sets default values for this component's properties
UCheckpoint::UCheckpoint()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
}


// Called when the game starts
void UCheckpoint::BeginPlay()
{
	Super::BeginPlay();

	PlayerActor = GetWorld()->GetFirstPlayerController()->GetPawn();

	// Add the OnComponentOverlap delegate function, to execute code when the player enters the checkpoint trigger
	TriggerActor = Cast<ATriggerBase>(GetOwner());
	if(TriggerActor && TriggerActor != nullptr)
	{
		UPrimitiveComponent* PrimitiveComponent = TriggerActor->FindComponentByClass<UPrimitiveComponent>();
		if(PrimitiveComponent)
		{
			PrimitiveComponent->OnComponentBeginOverlap.AddDynamic(this, &UCheckpoint::OnOverlapBegin);
			UE_LOG(LogTemp, Warning, TEXT("%s OnComponentOverlap delegates are added!"), *GetOwner()->GetName());
		}
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("%s must be a Trigger Actor!"), *GetOwner()->GetName());
	}


	RespawnLocation = GetOwner()->GetActorLocation();
}


// Called every frame
void UCheckpoint::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UCheckpoint::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComponent, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	// Ignore the player entering this checkpoint if they already entered it before
	if(bPlayerEnteredCheckpoint)
	{
		return;
	}

	// If the actor entering this checkpoint is the player, tell the respawner component to use this checkpoint
	UPlayerRespawner* Respawner = OtherActor->FindComponentByClass<UPlayerRespawner>();
	if(Respawner && Respawner != nullptr)
	{
		bPlayerEnteredCheckpoint = true;
		Respawner->OnCheckpointReached(this);
	}
}

// Teleport the player to the respawn location (the location of this checkpoint)
void UCheckpoint::RespawnPlayer()
{
	if(PlayerActor && PlayerActor != nullptr)
	{
		PlayerActor->SetActorLocation(RespawnLocation);
	}
}

