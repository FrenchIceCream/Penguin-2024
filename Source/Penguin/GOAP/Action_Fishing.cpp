
#include "Action_Fishing.h"
#include "../BuildingSystem/Building.h"
#include "../Framework/PengGameState.h"
#include "Kismet/GameplayStatics.h"
#include "../MyCharacter.h"
UAction_Fishing::UAction_Fishing()
{
    AddEffect("HasFish", true);
    TargetBuilding = nullptr;
    ShouldBeInRange = true;
}

//Check if we have an available building (fisherman hut)
bool UAction_Fishing::CheckProceduralPrecondition(AMyCharacter* Agent)
{
    if (APengGameState* GameState = Cast<APengGameState>(UGameplayStatics::GetGameState(GetWorld())))
    {
        for (FWorldSelectableData Selectable : GameState->GetPlacedObjects())
        {
            ABuilding* Building = Cast<ABuilding>(Selectable.Object);
            if (Building->BuildingType == EBuildingType::FishermanHut)
            {
                if (!TargetBuilding || FVector::Distance(Agent->GetActorLocation(), Building->GetActorLocation()) < FVector::Distance(Agent->GetActorLocation(), TargetBuilding->GetActorLocation()))
                    TargetBuilding = Building;
            }
        }
    }
    return TargetBuilding != nullptr;
}