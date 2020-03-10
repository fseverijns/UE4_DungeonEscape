// Copyright Frank Severijns 2020

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Components/PrimitiveComponent.h"
#include "DrawDebugHelpers.h"
#include "GameFramework/Actor.h"
#include "Looker.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class DUNGEONESCAPE_API ULooker : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	ULooker();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	// Returns the first actor in reach
	AActor* FindFirstObjectInReach() const;

private:
	UPROPERTY(EditAnywhere)
	int32 Reach = 100;

	// Cast a ray from the Actor's viewpoint to its reach
	void CastRay(const AActor* out_HitActor) const;
		
};
