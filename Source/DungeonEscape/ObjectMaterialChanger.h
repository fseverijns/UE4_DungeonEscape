// Copyright Frank Severijns 2020

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Components/StaticMeshComponent.h"
#include "GameFramework/Actor.h"
#include "Materials/Material.h"
#include "SwitchObserver.h"
#include "ObjectMaterialChanger.generated.h"

/* 	A SwitchObserver derivative. Can be assigned to any Switch component.
*	When activated/deactivated, it changes the material of the mesh to the specified material.
*/
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class DUNGEONESCAPE_API UObjectMaterialChanger : public USwitchObserver
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UObjectMaterialChanger();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	virtual void ChangeActivationState(const bool bNewState) override;
	// Reset the object to its initial state
	virtual void OnPlayerRespawn() override;

private:
	// The material this object gets when activated
	UPROPERTY(EditAnywhere)
	UMaterial* ActivatedMaterial;
	// The material this object gets when activated
	UPROPERTY(EditAnywhere)
	UMaterial* DeactivatedMaterial;

	// The mesh of this actor
	UStaticMeshComponent* Mesh;
};
