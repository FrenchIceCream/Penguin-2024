// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BuildingType.h"
#include "Engine/AssetManager.h"
#include "Engine/EngineTypes.h"
#include "Building.generated.h"

class UBuildingDataAsset;
class UBoxComponent;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnBuildingBuiltEvent, const EBuildState, BuildingState);

UCLASS()
class PENGUIN_API ABuilding : public AActor
{
	GENERATED_BODY()

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent * StaticMeshComp;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Meta = (AllowPrivateAccess = "true"))
	UBoxComponent * BoxCollider;

public:	
	ABuilding();
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FVector EntrancePos;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	USceneComponent * Entrance;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	EBuildingType BuildingType;

	UPROPERTY()
	UAssetManager * AssetManager;

	UPROPERTY()
	UBuildingDataAsset* BuildingData;

	UPROPERTY()
	float BuildProgression = 0.0f;

	UPROPERTY()
	FTimerHandle HandleBuildTimer;

	UPROPERTY()
	EBuildState BuildingState = EBuildState::NotBuilt;

	UPROPERTY()
	UMaterialInstanceDynamic * OverlayMaterial;

	void Init(UBuildingDataAsset * BuildingDataAsset, const EBuildState NewBuildingState = EBuildState::NotBuilt);

	void RemoveOverlayMaterial();

	UBuildingDataAsset* GetBuildingData() const { return BuildingData; }
	void UpdateOverlayMaterial(const bool CanPlace = true) const;

	FOnBuildingBuiltEvent OnBuildingBuiltEvent;

	void AddActorComponents(TArray<TSoftClassPtr<UActorComponent>> CompClasses);
protected:
	virtual void BeginPlay() override;

	void InitBuildPreview();
	void StartBuilding();
	void EndBuilding();
	void UpdateCollider();
	void SetOverlayMaterial();
	void UpdateBuildProgression();
	void UpdateBuildProgressionMesh();
};
