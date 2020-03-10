// Copyright Frank Severijns 2020


#include "Weight.h"

// Sets default values for this component's properties
UWeight::UWeight()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UWeight::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UWeight::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

int32 UWeight::GetWeight()
{
	return Weight;
}

