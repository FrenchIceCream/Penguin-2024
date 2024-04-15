// Fill out your copyright notice in the Description page of Project Settings.


#include "Action_GetFood.h"
#include "../MyCharacter.h"
#include "../BuildingSystem/Building.h"
#include "../Framework/PengGameState.h"
#include "Kismet/GameplayStatics.h"
#include "../ResourceComps/BasicResourceManager.h"

UAction_GetFood::UAction_GetFood()
{
    AddEffect("GetFood", true);
    AddPrecondition("IsHungry", true);
    ActionCost = 1.0f;
    Target = nullptr;
}

void UAction_GetFood::AddFood(AMyCharacter * Agent)
{
    //GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("Выловили рыбу!"));	
    UBasicResourceManager * ResManager = Target->GetComponentByClass<UBasicResourceManager>();
    if (Agent->GetHunger() >= 90 || ResManager->GetResourceCount() == 0)
    {
        //GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, TEXT("Конец getFood"));
        Agent->GetWorld()->GetTimerManager().ClearTimer(TimerHandle);
        IsActionDone = true;
    }

    Agent->SatisfyHunger(15);
    ResManager->SubtractResource();
}

// Check if we have an available building (fisherman hut)
bool UAction_GetFood::CheckProceduralPrecondition(AMyCharacter* Agent)
{
    if (APengGameState* GameState = Cast<APengGameState>(UGameplayStatics::GetGameState(GetWorld())))
    {
        //UE_LOG(LogTemp, Error, TEXT("Your message: %d"), GameState->GetPlacedObjects().Num());
        for (FWorldSelectableData Selectable : GameState->GetPlacedObjects())
        {
            ABuilding* Building = Cast<ABuilding>(Selectable.Object);
            if (Building->BuildingType == EBuildingType::Tavern)
            {
                if (!Target || FVector::Distance(Agent->GetActorLocation(), Building->GetActorLocation()) < FVector::Distance(Agent->GetActorLocation(), Target->GetActorLocation())
                    && Building->GetComponentByClass<UBasicResourceManager>()->GetResourceCount() > 0)
                        Target = Building;
            }
        }
    }
    UE_LOG(LogTemp, Error, TEXT("%d"), Target != nullptr);
    return Target != nullptr;
}

void UAction_GetFood::Reset()
{
    Target = nullptr;
}

bool UAction_GetFood::IsDone()
{
    return IsActionDone;
}

bool UAction_GetFood::Perform(AMyCharacter *Agent)
{
    if (!Agent->GetWorld()->GetTimerManager().IsTimerActive(TimerHandle))
    {
        TimerDelegate.BindUFunction(this, FName("AddFood"), Agent);
        Agent->GetWorld()->GetTimerManager().SetTimer(TimerHandle, TimerDelegate, 5.0f, true, 0.5f);
    }

    return true;
}