// Fill out your copyright notice in the Description page of Project Settings.

#include "Kismet/GameplayStatics.h"
#include "../PlayerControl.h"
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
}

void UBuildingModeComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
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