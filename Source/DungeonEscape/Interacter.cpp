// Copyright Frank Severijns 2020


#include "Interacter.h"

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

	BindInput();
}


// Called every frame
void UInteracter::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UInteracter::BindInput()
{
	InputHandler = GetOwner()->FindComponentByClass<UInputComponent>();
	if(InputHandler)
	{
		InputHandler->BindAction("Interact", IE_Pressed, this, &UInteracter::StartInteract);
		InputHandler->BindAction("Interact", IE_Released, this, &UInteracter::StopInteract);
	}
}

void UInteracter::StartInteract()
{
	AActor* Interactible = FindFirstActorInReach();
	
	if(!Interactible || Interactible == nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("Did not interact with anything."));
		return;
	}

	UInteractSwitch* InteractSwitch = Interactible->FindComponentByClass<UInteractSwitch>();
	if(InteractSwitch && InteractSwitch != nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("Found %s"), *Interactible->GetName());
		InteractingWith = InteractSwitch;
		InteractSwitch->OnInteractStart();
	}
}

void UInteracter::StopInteract()
{
	if(InteractingWith && InteractingWith != nullptr)
	{
		InteractingWith->OnInteractStop();
	}
}

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

