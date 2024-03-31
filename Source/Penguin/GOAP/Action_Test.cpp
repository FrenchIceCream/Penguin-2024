
#include "Action_Test.h"
#include "Kismet/GameplayStatics.h"
#include "../MyCharacter.h"

UAction_Test::UAction_Test()
{
    AddPrecondition("Testing", true);
    AddEffect("DoneTesting", true);
    ActionCost = 0.5f;
}

void UAction_Test::TestFunction()
{
    GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("Performing Test Action"));	
    TimerCalls--;

    if (TimerCalls == 0)
        DoneTesing = true;
}

bool UAction_Test::CheckProceduralPrecondition(AMyCharacter *Agent)
{
    TArray<AActor*> FoundActors;
    UGameplayStatics::GetAllActorsOfClassWithTag(GetWorld(), AActor::StaticClass(), FName("TestPoint"), FoundActors);

    for (AActor* FoundActor : FoundActors)
    {
        if (!Target || FVector::Distance(Agent->GetActorLocation(), FoundActor->GetActorLocation()) < FVector::Distance(Agent->GetActorLocation(), Target->GetActorLocation()))
            Target = FoundActor;
    }

    return Target != nullptr;
}

bool UAction_Test::Perform(AMyCharacter *Agent)
{
    if (!GetWorld()->GetTimerManager().IsTimerActive(TimerHandle))
        GetWorld()->GetTimerManager().SetTimer(TimerHandle, this, &UAction_Test::TestFunction, 2.0f, true, 0.5f);

    return true;
}