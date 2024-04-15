// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "BuildingType.h"
#include "BuildingDataAsset.generated.h"

UCLASS()
class PENGUIN_API UBuildingDataAsset : public UPrimaryDataAsset
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Configuration")
	FText TitleText;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Configuration")
	TSoftObjectPtr<UTexture2D> Image;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Data Settings")
	FPrimaryAssetType DataType;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Data Settings")
	EBuildingType BuildingType;

	virtual FPrimaryAssetId GetPrimaryAssetId() const override { return FPrimaryAssetId(DataType, GetFName()); }

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Classes")
	TArray<TSoftClassPtr<UActorComponent>> ComponentsToAdd;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Classes")
	TSoftClassPtr<AActor> BuildingClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Classes")
	TSoftClassPtr<AActor> FinalBuildingClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Display")
	TArray<TSoftObjectPtr<UStaticMesh>> BuildingMeshes;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Display")
	TSoftObjectPtr<UStaticMesh> FinalBuildingMesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Materials")
	TSoftObjectPtr<UMaterialInstance> PlaceMaterial;
};
