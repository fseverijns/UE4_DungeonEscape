// Copyright Frank Severijns 2020

#pragma once

#include "GameResetter.h"
#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "DungeonEscapeGameInstance.generated.h"

/**
 * 
 */
UCLASS()
class DUNGEONESCAPE_API UDungeonEscapeGameInstance : public UGameInstance
{
	GENERATED_BODY()

public:
	virtual void Init() override;

    virtual void StartGameInstance() override;

    virtual void OnStart() override;

	UGameResetter* GetResetter();

private:
	UGameResetter* Resetter = NewObject<UGameResetter>();

};
