// Copyright Epic Games, Inc. All Rights Reserved.


#include "PenguinGameModeBase.h"
#include "GameFramework/Actor.h"

APenguinGameModeBase::APenguinGameModeBase()
{
	PrimaryActorTick.bCanEverTick = true;
}

void APenguinGameModeBase::BeginPlay()
{
	Super::BeginPlay();
}

void APenguinGameModeBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}
