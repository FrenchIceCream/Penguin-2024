// Fill out your copyright notice in the Description page of Project Settings.

#include "BuildingBase.h"
#include "Components/StaticMeshComponent.h"

// Sets default values
ABuildingBase::ABuildingBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void ABuildingBase::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void ABuildingBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ABuildingBase::SetData(UBuildingDataAsset *BuildingDataAsset)
{
	if (BuildingDataAsset)
		BuildingData = BuildingDataAsset;
	
	if (!StaticMeshComp || !BuildingData)
		return;

	if (UStaticMesh* DisplayMesh = Cast<UStaticMesh>(BuildingData->FinalBuildingMesh.LoadSynchronous()))
		StaticMeshComp->SetStaticMesh(DisplayMesh);
}
