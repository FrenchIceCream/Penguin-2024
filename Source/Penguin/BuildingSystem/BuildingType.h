#pragma once

#include "CoreMinimal.h"
#include "BuildingType.generated.h"

UENUM(BlueprintType)
enum class EBuildingType : uint8
{
    //SCHOOLS
    FishingSchool  UMETA(DisplayName = "Fishing School"),
    
    //CAREER-RELATED THINGS
    FishermanHut    UMETA(DisplayName = "Fisherman Hut"),
    
    //FOOD-RELATED THINGS
    Tavern          UMETA(DisplayName = "Tavern"),
    Market          UMETA(DisplayName = "Market"),

    //DIFFERENT FACILITIES
    Warehouse       UMETA(DisplayName = "Warehouse"),

};

UENUM()
enum class EBuildState : uint8
{
    NotBuilt  UMETA(DisplayName = "Not Built"),
    InProgress  UMETA(DisplayName = "In Progress"),
    Built  UMETA(DisplayName = "Built"),
    Aborted  UMETA(DisplayName = "Aborted"),
};

USTRUCT()
struct FWorldSelectableData
{
    GENERATED_BODY()
public:

    FWorldSelectableData(): Object(nullptr) {}

    FWorldSelectableData(AActor * object): Object(object) {}

    UPROPERTY()
    AActor* Object;
};