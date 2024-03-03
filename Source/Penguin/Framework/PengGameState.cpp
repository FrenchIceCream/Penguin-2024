// Fill out your copyright notice in the Description page of Project Settings.


#include "PengGameState.h"

APengGameState::APengGameState()
{
    PrimaryActorTick.bCanEverTick = true;
}

void APengGameState::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
}

void APengGameState::BeginPlay()
{
    Super::BeginPlay();
}
