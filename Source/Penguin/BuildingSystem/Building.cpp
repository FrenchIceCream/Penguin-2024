// Fill out your copyright notice in the Description page of Project Settings.

#include "Building.h"
#include "Components/BoxComponent.h"
#include "BuildingDataAsset.h"

// Sets default values
ABuilding::ABuilding()
{
	PrimaryActorTick.bCanEverTick = false;

	BoxCollider = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxCollider"));
	RootComponent = BoxCollider;
	BoxCollider->SetCollisionProfileName("OverlapAll");

	StaticMeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));
	StaticMeshComp->SetupAttachment(RootComponent);
	StaticMeshComp->SetCollisionProfileName("OverlapAll");

	//TODO вынести в дата ассет
	Entrance = CreateDefaultSubobject<USceneComponent>(TEXT("EntrancePosition"));
	Entrance->SetupAttachment(RootComponent);
}

void ABuilding::BeginPlay()
{
	Super::BeginPlay();
}

void ABuilding::Init(UBuildingDataAsset *BuildingDataAsset, const EBuildState NewBuildingState)
{
	if (!BuildingDataAsset) 
		return;

	BuildingState = NewBuildingState;
	BuildingData = BuildingDataAsset;

	if (BuildingState == EBuildState::InProgress)
	{
		StartBuilding();
	}
	else
	{
		InitBuildPreview();
	}
}

void ABuilding::UpdateOverlayMaterial(const bool CanPlace) const
{
	if (!OverlayMaterial)
		return;
	OverlayMaterial->SetScalarParameterValue(FName("Status"), CanPlace ? 1.0f : 0.0f);
}

void ABuilding::InitBuildPreview()
{
	if (!BuildingData || !StaticMeshComp || !BoxCollider) 
		return;

	if (UStaticMesh* PreviewMesh = Cast<UStaticMesh>(BuildingData->FinalBuildingMesh.LoadSynchronous()))
	{
		StaticMeshComp->SetStaticMesh(PreviewMesh);
		UpdateCollider();
		SetOverlayMaterial();
	}
}


void ABuilding::StartBuilding()
{
	BuildProgression = 0.0f;
	UpdateBuildProgression();

	//TODO таймер
	GetWorldTimerManager().SetTimer(HandleBuildTimer, this, &ABuilding::UpdateBuildProgression, 2.0f, true, 2.0f);

	BuildingState = EBuildState::InProgress;	
}


void ABuilding::EndBuilding()
{
	UE_LOG(LogTemp, Warning, TEXT("EndBuilding"));
	GetWorldTimerManager().ClearTimer(HandleBuildTimer);

	if (BuildingState != EBuildState::Built)
		BuildingState = EBuildState::Aborted;

	 OnBuildingBuiltEvent.Broadcast(BuildingState);
}

void ABuilding::UpdateCollider()
{
	if (!StaticMeshComp || !BoxCollider) 
		return;
	
	FVector MinMeshBounds, MaxMeshBounds;
	StaticMeshComp->GetLocalBounds(MinMeshBounds, MaxMeshBounds);

	BoxCollider->SetBoxExtent(FVector
	(
		FMath::RoundToInt(MaxMeshBounds.X + 10.f),
		FMath::RoundToInt(MaxMeshBounds.Y + 10.f),
		FMath::RoundToInt(MaxMeshBounds.Z + 10.f)
	), 
	true);

	//todo поворот?
}

void ABuilding::SetOverlayMaterial()
{
	if (!BuildingData)
		return;
	
	const FSoftObjectPath AssetPath = BuildingData->PlaceMaterial.ToSoftObjectPath();
	if (UMaterialInstance* OverlayMat = Cast<UMaterialInstance>(AssetPath.TryLoad()))
	{
		OverlayMaterial = UMaterialInstanceDynamic::Create(OverlayMat, this);
		if (OverlayMaterial)
		{
			TArray<UStaticMeshComponent*> Components;
			GetComponents<UStaticMeshComponent>(Components);
			for (int i = 0; i < Components.Num(); i++)
				Components[i]->SetOverlayMaterial(OverlayMaterial);
		}
	}

}

void ABuilding::UpdateBuildProgressionMesh()
{
	//UE_LOG(LogTemp, Warning, TEXT("UpdateBuildProgressionMesh1"));
	if (!BuildingData || !StaticMeshComp)
		return;
	
	//UE_LOG(LogTemp, Warning, TEXT("UpdateBuildProgressionMes2"));

	const int32 BuildMeshIndex = FMath::FloorToInt32(BuildProgression * BuildingData->BuildingMeshes.Num());
	if (BuildingData->BuildingMeshes.IsValidIndex(BuildMeshIndex))
	{
		//UE_LOG(LogTemp, Warning, TEXT("Valid Index"));
		if (UStaticMesh* DisplayMesh = BuildingData->BuildingMeshes[BuildMeshIndex].LoadSynchronous())
		{
			UE_LOG(LogTemp, Warning, TEXT("Display Mesh"));
			StaticMeshComp->SetStaticMesh(DisplayMesh);
		}
	}
}


void ABuilding::UpdateBuildProgression()
{
	if (!StaticMeshComp)
		return;	

	BuildProgression += 1.0f / BuildingData->BuildingMeshes.Num();
	
	UE_LOG(LogTemp, Warning, TEXT("Number of Building Meshes: %d, Progression: %f"), BuildingData->BuildingMeshes.Num(), BuildProgression);

	if (BuildProgression >= 1.0f)
	{
		if (UStaticMesh* DisplayMesh = BuildingData->FinalBuildingMesh.LoadSynchronous())
			StaticMeshComp->SetStaticMesh(DisplayMesh);
		BuildingState = EBuildState::Built;
		EndBuilding();
	}
	else
	{
		UpdateBuildProgressionMesh();
	}
}