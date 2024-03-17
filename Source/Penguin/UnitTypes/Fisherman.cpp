// Fill out your copyright notice in the Description page of Project Settings.


#include "Fisherman.h"

void AFisherman::CatchFish()
{
    UE_LOG(LogTemp, Warning, TEXT("Catching Fish!"));
    AddCaughtFish();
}
