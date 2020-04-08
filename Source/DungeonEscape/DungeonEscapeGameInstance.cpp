// Copyright Frank Severijns 2020

#include "DungeonEscapeGameInstance.h"
#include "GameResetter.h"

void UDungeonEscapeGameInstance::Init()
{
    Super::Init();

    UE_LOG(LogTemp, Warning, TEXT("Init, path = %s"), *GetPathName());
}

void UDungeonEscapeGameInstance::StartGameInstance()
{
    Super::StartGameInstance();

    UE_LOG(LogTemp, Warning, TEXT("StartGameInstance, path = %s"), *GetPathName());
}

void UDungeonEscapeGameInstance::OnStart()
{
    Super::OnStart();

    UE_LOG(LogTemp, Warning, TEXT("OnStart, path = %s"), *GetPathName());
}

UGameResetter* UDungeonEscapeGameInstance::GetResetter()
{
    return Resetter;
}


