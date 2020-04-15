// Copyright Frank Severijns 2020


#include "ObjectMaterialChanger.h"

// Sets default values for this component's properties
UObjectMaterialChanger::UObjectMaterialChanger()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UObjectMaterialChanger::BeginPlay()
{
	Super::BeginPlay();

	// Get the Mesh component (log a warning if there is no mesh component)
	Mesh = GetOwner()->FindComponentByClass<UStaticMeshComponent>();
	if(!Mesh || Mesh == nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("Cannot change Material of %s, because it does not have a Static Mesh Component!"), *GetOwner()->GetName());
		return;
	}
}


// Called every frame
void UObjectMaterialChanger::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

// Change the material to based on the state of the SwitchObserver.
void UObjectMaterialChanger::ChangeActivationState(const bool bNewState)
{
	Super::ChangeActivationState(bNewState);

	if(Mesh && Mesh != nullptr)
	{
		Mesh->SetMaterial(0, bActivationState ? ActivatedMaterial : DeactivatedMaterial);
	}
}

// Reset the material to the default state
void UObjectMaterialChanger::OnPlayerRespawn()
{
	if(Mesh && Mesh != nullptr)
	{
		Mesh->SetMaterial(0, bDefaultState ? ActivatedMaterial : DeactivatedMaterial);
	}
}

