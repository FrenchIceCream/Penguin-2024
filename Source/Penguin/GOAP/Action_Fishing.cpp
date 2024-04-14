
#include "Action_Fishing.h"
#include "../BuildingSystem/Building.h"
#include "../Framework/PengGameState.h"
#include "Kismet/GameplayStatics.h"
#include "../MyCharacter.h"
#include "../UnitTypes/Fisherman.h"

UAction_Fishing::UAction_Fishing()
{
    AddEffect("HasFish", true);
    AddPrecondition("NeedsFish", true);
    ActionCost = 5.0f;
    Target = nullptr;
}

void UAction_Fishing::AddFish(AMyCharacter * Agent)
{
    GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("Выловили рыбу!"));	
    Cast<AFisherman>(Agent)->AddCaughtFish();
    TimerCalls--;
    //UE_LOG(LogTemp, Warning, TEXT("Your message: %d"), TimerCalls);
    if (TimerCalls == 0)
    {
        GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, TEXT("Больше не можем выловить"));
        Agent->GetWorld()->GetTimerManager().ClearTimer(TimerHandle);
        IsActionDone = true;
    }
}

// Check if we have an available building (fisherman hut)
bool UAction_Fishing::CheckProceduralPrecondition(AMyCharacter* Agent)
{
    if (APengGameState* GameState = Cast<APengGameState>(UGameplayStatics::GetGameState(GetWorld())))
    {
        //UE_LOG(LogTemp, Error, TEXT("Your message: %d"), GameState->GetPlacedObjects().Num());
        for (FWorldSelectableData Selectable : GameState->GetPlacedObjects())
        {
            ABuilding* Building = Cast<ABuilding>(Selectable.Object);
            if (Building->BuildingType == EBuildingType::FishermanHut)
            {
                if (!Target || FVector::Distance(Agent->GetActorLocation(), Building->GetActorLocation()) < FVector::Distance(Agent->GetActorLocation(), Target->GetActorLocation()))
                    Target = Building;
            }
        }
    }
    UE_LOG(LogTemp, Error, TEXT("%d"), Target != nullptr);
    return Target != nullptr;
}

void UAction_Fishing::Reset()
{
    Target = nullptr;
}

bool UAction_Fishing::IsDone()
{
    return IsActionDone;
}

bool UAction_Fishing::Perform(AMyCharacter *Agent)
{
    if (!Agent->GetWorld()->GetTimerManager().IsTimerActive(TimerHandle) && TimerCalls > 0)
    {
        TimerDelegate.BindUFunction(this, FName("AddFish"), Agent);
        Agent->GetWorld()->GetTimerManager().SetTimer(TimerHandle, TimerDelegate, 3.0f, true, 0.5f);
    }

    return true;
}
