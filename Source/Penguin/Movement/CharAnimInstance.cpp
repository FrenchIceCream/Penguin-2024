// Fill out your copyright notice in the Description page of Project Settings.

#include "CharAnimInstance.h"
#include "../MyCharacter.h"
#include "LegManager.h"
#include "FootComp.h"


UCharAnimInstance::UCharAnimInstance()
{}

//BeginPlay()
void UCharAnimInstance::NativeInitializeAnimation()
{
    Super::NativeInitializeAnimation();
    Char = Cast<AMyCharacter>(TryGetPawnOwner());

    if (!Char)
        return;
    
    LegManager = Cast<ULegManager>(Char->GetComponentByClass(ULegManager::StaticClass()));
    if (LegManager)
    {
        TArray<UFootComp*> Legs;
        Char->GetComponents<UFootComp>(Legs);
        if (Legs.Num() < 2)
        {
            UE_LOG(LogTemp, Error, TEXT("No legs found in AnimInstance"));
        }
        else
        {
            LeftFoot = Legs[0];
            LeftFootPos = LeftFoot->GetFootPosition();
            //UE_LOG(LogTemp, Warning, TEXT("%s"), *Legs[0]->GetName());
            RightFoot = Legs[1];
            RightFootPos = RightFoot->GetFootPosition();
        }
    }
}

//Tick()
void UCharAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
    if (LeftFoot && RightFoot)
    {
        LeftFootPos = LeftFoot->GetFootPosition();
        RightFootPos = RightFoot->GetFootPosition();   

        //LeftFootRot = LeftFoot->GetFootRotation();
        //RightFootRot = RightFoot->GetFootRotation();
    }
}