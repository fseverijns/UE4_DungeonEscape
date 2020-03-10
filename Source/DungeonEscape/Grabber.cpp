// Copyright Frank Severijns 2020

#include "Engine/World.h"
#include "GameFramework/PlayerController.h"
#include "Grabber.h"

#define OUT

// Sets default values for this component's properties
UGrabber::UGrabber()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UGrabber::BeginPlay()
{
	Super::BeginPlay();

	FindPhysicsHandler();
	BindInput();
}

void UGrabber::FindPhysicsHandler()
{
	PhysicsHandler = GetOwner()->FindComponentByClass<UPhysicsHandleComponent>();
	if(PhysicsHandler)
	{
		UE_LOG(LogTemp, Warning, TEXT("%s has PhysicsHandleComponent"), *GetOwner()->GetName());
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("%s has no PhysicsHandleComponent attached!"), *GetOwner()->GetName());
	}
}

void UGrabber::BindInput()
{
	InputHandler = GetOwner()->FindComponentByClass<UInputComponent>();
	if(InputHandler)
	{
		InputHandler->BindAction("Interact", IE_Pressed, this, &UGrabber::Grab);
		InputHandler->BindAction("Interact", IE_Released, this, &UGrabber::Release);
	}
}

// Called every frame
// TODO: Refactor! Split up in multiple functions
void UGrabber::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if(PhysicsHandler)
	{
		FVector PlayerViewPointLocation;
		FRotator PlayerViewPointRotation;
		GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(OUT PlayerViewPointLocation, OUT PlayerViewPointRotation);

		HeldPosition = PlayerViewPointLocation + PlayerViewPointRotation.Vector() * (Reach/2);

		PhysicsHandler->SetTargetLocation(HeldPosition);
		PhysicsHandler->SetTargetRotation(FRotator(0,0,0));
	}
}

void UGrabber::Grab()
{
	UE_LOG(LogTemp, Warning, TEXT("Interact pressed"));

	ObjectInReach = FindFirstPhysicsObjectInReach();

	if(!ObjectInReach || ObjectInReach == nullptr)
	{
		return;
	}

	UE_LOG(LogTemp, Warning, TEXT("Grabbing %s"), *ObjectInReach->GetName());

	UPrimitiveComponent* PrimitiveComponent = ObjectInReach->FindComponentByClass<UPrimitiveComponent>();

	if(PrimitiveComponent)
	{
		if(PhysicsHandler && PrimitiveComponent->GetMass() <= MaximumCarryWeight && !HeldObject)
		{
			PhysicsHandler->GrabComponentAtLocation(PrimitiveComponent, FName(""), HeldPosition); // Grab the object
			HeldObject = ObjectInReach;
		}
	}
}

AActor* UGrabber::FindFirstPhysicsObjectInReach() const
{
	AActor* PhysicsObject = nullptr;
	CastRay(OUT PhysicsObject);

	return PhysicsObject;
}

void UGrabber::CastRay(AActor* &out_HitActor) const
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
		FCollisionObjectQueryParams(ECollisionChannel::ECC_PhysicsBody),
		FCollisionQueryParams(FName(TEXT("")), false, GetOwner())
	);

	out_HitActor = Hit.GetActor();
}

void UGrabber::Release()
{
	UE_LOG(LogTemp, Warning, TEXT("Interact released"));

	if(!HeldObject)
	{
		return;
	}

	PhysicsHandler->ReleaseComponent();
	HeldObject = nullptr;
}

