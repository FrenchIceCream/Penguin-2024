// Fill out your copyright notice in the Description page of Project Settings.


#include "Building.h"

// Sets default values
ABuilding::ABuilding()
{
	PrimaryActorTick.bCanEverTick = true;
	StaticMeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));
	StaticMeshComp->SetupAttachment(RootComponent);

	Entrance = CreateDefaultSubobject<USceneComponent>(TEXT("EntrancePosition"));
	Entrance->SetupAttachment(RootComponent);
}

void ABuilding::BeginPlay()
{
	Super::BeginPlay();
	
}

void ABuilding::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

