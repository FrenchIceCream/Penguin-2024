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
