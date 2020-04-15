// Copyright Frank Severijns 2020

#include "Interacter.h"
#include "KeyItemPickup.h"
#include "InteractSwitch.h"

// Sets default values for this component's properties
UInteracter::UInteracter()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UInteracter::BeginPlay()
{
	Super::BeginPlay();

	// Bind the interact key
	BindInput();
}


// Called every frame
void UInteracter::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

// Bind the interact input to call the respective functions
void UInteracter::BindInput()
{
	InputHandler = GetOwner()->FindComponentByClass<UInputComponent>();
	if(InputHandler)
	{
		InputHandler->BindAction("Interact", IE_Pressed, this, &UInteracter::StartInteract);
		InputHandler->BindAction("Interact", IE_Released, this, &UInteracter::StopInteract);
	}
}

//	Interacts with an object within reach 
void UInteracter::StartInteract()
{
	// First check if there is something in reach
	AActor* Interactible = FindFirstActorInReach();
	
	// If nothing is in reach, do nothing (print a log message for debugging)
	if(!Interactible || Interactible == nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("Did not interact with anything."));
		return;
	}

	// If the actor in reach has an interact switch component, we tell that switch we are interacting
	UInteractSwitch* InteractSwitch = Interactible->FindComponentByClass<UInteractSwitch>();
	if(InteractSwitch && InteractSwitch != nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("Found InteractSwitch %s"), *Interactible->GetName());
		InteractingWith = InteractSwitch;
		InteractSwitch->OnInteractStart();
	}

	// If the actor in reach has a key item pickup component, we pick up that item
	UKeyItemPickup* ItemPickup = Interactible->FindComponentByClass<UKeyItemPickup>();
	if(ItemPickup && ItemPickup != nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("Found Pickup %s"), *Interactible->GetName());
		ItemPickup->PickUp();
	}
}

// If something is being interacted with but we let go of the interact key, stop the interaction 
// (this only works on interact switches that require the player to hold interact)
void UInteracter::StopInteract()
{
	if(InteractingWith && InteractingWith != nullptr)
	{
		InteractingWith->OnInteractStop();
	}
}

// Get an actor within reach
AActor* UInteracter::FindFirstActorInReach() const
{
	AActor* Interactible = nullptr;
	CastRay(OUT Interactible);

	return Interactible;
}

// Cast a ray from the Actor's viewpoint to its reach
void UInteracter::CastRay(AActor* &out_HitActor) const
{
	FVector PlayerViewPointLocation;
	FRotator PlayerViewPointRotation;
	GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(OUT PlayerViewPointLocation, OUT PlayerViewPointRotation);

	FVector LineTraceEnd = PlayerViewPointLocation + PlayerViewPointRotation.Vector() * Reach;

	DrawDebugLine(
		GetWorld(),
		PlayerViewPointLocation,
		LineTraceEnd,
		FColor(0,255,0),
		false,
		5.f,
		0,
		5.f
	);

	FHitResult Hit;
	GetWorld()->LineTraceSingleByObjectType(
		Hit,
		PlayerViewPointLocation,
		LineTraceEnd,
		FCollisionObjectQueryParams(ECollisionChannel::ECC_WorldDynamic),
		FCollisionQueryParams(FName(TEXT("")), false, GetOwner())
	);

	out_HitActor = Hit.GetActor();
}

