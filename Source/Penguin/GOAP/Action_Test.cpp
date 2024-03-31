
#include "Action_Test.h"
#include "Kismet/GameplayStatics.h"
#include "../MyCharacter.h"
#include "TimerManager.h"

UAction_Test::UAction_Test()
{
    AddPrecondition("Testing", true);
    AddEffect("DoneTesting", true);
    ActionCost = 0.5f;
}

void UAction_Test::TestFunction(AMyCharacter *Agent)
{
    GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("Performing Test Action"));	
    TimerCalls--;
    UE_LOG(LogTemp, Warning, TEXT("Your message: %d"), TimerCalls);
    if (TimerCalls == 0)
    {
        GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, TEXT("Done Testing"));
        Agent->GetWorld()->GetTimerManager().ClearTimer(TimerHandle);
        DoneTesing = true;
    }
}

bool UAction_Test::CheckProceduralPrecondition(AMyCharacter *Agent)
{
    TArray<AActor*> FoundActors;
    UGameplayStatics::GetAllActorsOfClassWithTag(Agent->GetWorld(), AActor::StaticClass(), FName("TestPoint"), FoundActors);

    //UE_LOG(LogTemp, Warning, TEXT("Found %d actors"), FoundActors.Num());

    for (AActor* FoundActor : FoundActors)
    {
        if (!Target || FVector::Distance(Agent->GetActorLocation(), FoundActor->GetActorLocation()) < FVector::Distance(Agent->GetActorLocation(), Target->GetActorLocation()))
            Target = FoundActor;
    }

    return Target != nullptr;
}

bool UAction_Test::Perform(AMyCharacter *Agent)
{
    if (!Agent->GetWorld()->GetTimerManager().IsTimerActive(TimerHandle) && TimerCalls > 0)
    {
        TimerDelegate.BindUFunction(this, FName("TestFunction"), Agent);
        Agent->GetWorld()->GetTimerManager().SetTimer(TimerHandle, TimerDelegate, 2.0f, true, 0.5f);
    }

    return true;
}

void UAction_Test::Reset()
{
    Target = nullptr;
}
