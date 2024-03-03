// Fill out your copyright notice in the Description page of Project Settings.

#include "Kismet/GameplayStatics.h"
#include "../PlayerControl.h"
#include "../Framework/PengGameState.h"
#include "BuildingBase.h"
#include "BuildingModeComponent.h"

// Sets default values for this component's properties
UBuildingModeComponent::UBuildingModeComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UBuildingModeComponent::BeginPlay()
{
	Super::BeginPlay();
	
	verify ((PlayerController = Cast<APlayerControl>(UGameplayStatics::GetPlayerController(GetWorld(), 0))) != nullptr);
	verify ((World = GetWorld()) != nullptr);
}

void UBuildingModeComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (!CurrentBuilding)
		return;
	
	const FVector MouseLocationOnTerrain = PlayerController->GetMouseLocationOnTerrain();
	if (CurrentBuilding->GetActorLocation() != MouseLocationOnTerrain)
		CurrentBuilding->SetActorLocation(MouseLocationOnTerrain);
		
	UpdatePlacementStatus();
}

void UBuildingModeComponent::LoadBuildingData()
{
	verify ((AssetManager = UAssetManager::GetIfValid()) != nullptr);

	const FPrimaryAssetType AssetType("BuildingData");
	TArray<FPrimaryAssetId> BuildingDataAssets;
	AssetManager->GetPrimaryAssetIdList(AssetType, BuildingDataAssets);

	UE_LOG(LogTemp, Error, TEXT("BuildingDataAssets: %d"), BuildingDataAssets.Num());
	if (BuildingDataAssets.Num() > 0)
	{
		const TArray<FName> Bundles;
		const FStreamableDelegate FormationDataLoadedDelegate = FStreamableDelegate::CreateUObject(this, &UBuildingModeComponent::OnBuildingDataLoaded, BuildingDataAssets);
		AssetManager->LoadPrimaryAssets(BuildingDataAssets, Bundles, FormationDataLoadedDelegate);
	}
}

void UBuildingModeComponent::OnBuildingDataLoaded(TArray<FPrimaryAssetId> BuildingAssetsIds)
{
	if (!PlayerController)
		return;
	
	//TODO здесь фильтры можно ввести
	for (int i = 0; i < BuildingAssetsIds.Num(); i++)
	{
		//if (const UBuildingDataAsset* BuildingDataAsset = Cast<UBuildingDataAsset>(AssetManager->GetPrimaryAssetObject(BuildingAssetsIds[i])))
			BuildingItemsData.Add(BuildingAssetsIds[i]);
	}
}


void UBuildingModeComponent::UpdatePlacementStatus()
{
	if (!CurrentBuilding)
		return;

	TArray<AActor*> OverlappingActors;
	CurrentBuilding->GetOverlappingActors(OverlappingActors);
	IsPlacable = OverlappingActors.Num() == 0;
	CurrentBuilding->UpdateOverlayMaterial(IsPlacable);
}

void UBuildingModeComponent::EnterBuildMode()
{
	//UE_LOG(LogTemp, Error, TEXT("EnterBuildMode"));
	if (!CurrentBuilding)
		return;

	//UE_LOG(LogTemp, Error, TEXT("EnterBuildMode2"));

	if (IsPlacable)
	{
		PlaceBuilding(CurrentBuilding->GetBuildingData(), CurrentBuilding->GetTransform());
		ExitBuildMode();
	}
	else
	{
		//TODO сменить цвет материала на красный
	}
}

void UBuildingModeComponent::EnterBuildPlacementMode(UBuildingDataAsset *BuildingDataAsset)
{
//	UE_LOG(LogTemp, Error, TEXT("EnterBuildPlacementMode 1"));
	if (!PlayerController || !BuildingDataAsset || !World)
		return;

	FTransform SpawnTransform;
	SpawnTransform.SetLocation(PlayerController->GetMouseLocationOnTerrain());
	FActorSpawnParameters SpawnParameters;
	SpawnParameters.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

	//UE_LOG(LogTemp, Warning, TEXT("EnterBuildPlacementMode"));

	CurrentBuilding = World->SpawnActor<ABuilding>(BuildingDataAsset->BuildingClass.LoadSynchronous(), SpawnTransform, SpawnParameters);
	if (CurrentBuilding)
		CurrentBuilding->Init(BuildingDataAsset);

	OnBuildModeEnterEvent.Broadcast();
}

void UBuildingModeComponent::ExitBuildMode()
{
	if (!PlayerController)
		return;

	//TODO AddInput

	if (CurrentBuilding)
		CurrentBuilding->Destroy();
}


void UBuildingModeComponent::PlaceBuilding(UBuildingDataAsset *BuildingDataAsset, const FTransform &Position)
{
	UE_LOG(LogTemp, Error, TEXT("Entered PlaceBuilding"));
	if (!BuildingDataAsset)
		return;

	UE_LOG(LogTemp, Error, TEXT("Entered PlaceBuilding 2"));

	FActorSpawnParameters SpawnParameters;
	SpawnParameters.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
	CurrentBuilding = World->SpawnActor<ABuilding>(BuildingDataAsset->BuildingClass.LoadSynchronous(), Position, SpawnParameters);
	if (CurrentBuilding)
	{
		CurrentBuilding->Init(BuildingDataAsset, EBuildState::InProgress);
		CurrentBuilding->OnBuildingBuiltEvent.AddDynamic(this, &UBuildingModeComponent::OnBuildComplete);
	}
}

void UBuildingModeComponent::PlaceBuildingInWorld(UBuildingDataAsset * BuildingDataAsset, const FTransform & Position)
{
	if (!PlayerController || !World)
		return;
	
	FActorSpawnParameters SpawnParameters;
	SpawnParameters.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
	if (const TSubclassOf<AActor> BuiltClass = BuildingDataAsset->FinalBuildingClass.LoadSynchronous())
	{
		if (AActor* BuiltObject = World->SpawnActor<AActor>(BuiltClass, Position, SpawnParameters))
		{
			if (APengGameState* GameState = Cast<APengGameState>(UGameplayStatics::GetGameState(World)))
				GameState->AddPlacedObject(FWorldSelectableData(BuiltObject));

			if (ABuildingBase* Building = Cast<ABuildingBase>(BuiltObject))
				Building->SetData(BuildingDataAsset);
		}
	}
}



void UBuildingModeComponent::OnBuildComplete(const EBuildState NewBuildingState)
{
	if (!CurrentBuilding)
		return;

	if (NewBuildingState == EBuildState::Built)
	{
		PlaceBuildingInWorld(CurrentBuilding->GetBuildingData(), CurrentBuilding->GetTransform());
	}
	else
	{
		CurrentBuilding->Destroy();
	}
}


