// Fill out your copyright notice in the Description page of Project Settings.


#include "MyCharacter.h"
#include "Components/SkeletalMeshComponent.h"
#include "GameFramework/Actor.h"
#include "Kismet/GameplayStatics.h"
#include "NavMesh/NavMeshBoundsVolume.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Movement/LegManager.h"
#include "Movement/FootComp.h"  
#include "Movement/CharAnimInstance.h"
#include "GOAP/GoalPlanner.h"
#include "GOAP/GoapAgent.h"
#include "Movement/CharController.h"
#include "Components/WidgetComponent.h"
#include "UI/StatsBar.h"
//#include "UI/ThoughtBubble.h"
//=Actions=//
#include "GOAP/Action_Test.h"

// Sets default values
AMyCharacter::AMyCharacter()
{
	PrimaryActorTick.bCanEverTick = true;

	GetCapsuleComponent()->InitCapsuleSize(42, 96);
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = FRotator(0, 100, 0);
	GetCharacterMovement()->AirControl = 0.2;
	GetCharacterMovement()->MaxWalkSpeed = WalkingSpeed;

	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->TargetArmLength = 250;
	CameraBoom->bUsePawnControlRotation = true;

	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
	FollowCamera->bUsePawnControlRotation = true;

	LegManager = CreateDefaultSubobject<ULegManager>(TEXT("LegManager"));

	LeftFoot = CreateDefaultSubobject<UFootComp>(TEXT("LeftFootComp"));
	LeftFoot->SetupAttachment(GetMesh());

	RightFoot = CreateDefaultSubobject<UFootComp>(TEXT("RightFootComp"));
	RightFoot->SetupAttachment(GetMesh());

	LeftFoot->SetStepTime(WalkingSpeed);
	RightFoot->SetStepTime(WalkingSpeed);

	GoalPlanner = CreateDefaultSubobject<UGoalPlanner>(TEXT("GoalPlanner"));
	GoapAgent = CreateDefaultSubobject<UGoapAgent>(TEXT("GoapAgent"));

	StatsBarWidgetComp = CreateDefaultSubobject<UWidgetComponent>(TEXT("StatsBar"));
	StatsBarWidgetComp->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void AMyCharacter::BeginPlay()
{
	Super::BeginPlay();
	LeftFoot->SetWorldLocation(GetMesh()->GetSocketLocation(LeftSocketName));
	RightFoot->SetWorldLocation(GetMesh()->GetSocketLocation(RightSocketName));
	AnimInst = Cast<UCharAnimInstance>(GetMesh()->GetAnimInstance());
	if (!AnimInst)
		UE_LOG(LogTemp, Error, TEXT("No AnimInst"));

	PlayerAI = GetWorld()->SpawnActor<ACharController>(ACharController::StaticClass(), FVector::ZeroVector, FRotator::ZeroRotator);
	PlayerAI->Possess(this);

	// UE_LOG(LogTemp, Warning, TEXT("%f:%f:%f"), GetMesh()->GetSocketTransform(RightSocketName).GetLocation().X, GetMesh()->GetSocketTransform(RightSocketName).GetLocation().Y, GetMesh()->GetSocketTransform(RightSocketName).GetLocation().Z);
	// UE_LOG(LogTemp, Warning, TEXT("%f:%f:%f"), GetMesh()->GetSocketLocation(LeftSocketName).X, GetMesh()->GetSocketLocation(LeftSocketName).Y, GetMesh()->GetSocketLocation(LeftSocketName).Z);
	AddActions();

	GetWorldTimerManager().SetTimer(HungerTimerHandle, this, &AMyCharacter::DecreaseHunger, 1, true);

	UStatsBar *StatsBar = Cast<UStatsBar>(StatsBarWidgetComp->GetUserWidgetObject());
	StatsBar->SetOwnerChar(this);
}

void AMyCharacter::AddActions()
{
	for (TSubclassOf<UAction> ActionClass : ActionsToAdd)
	{
		GoapAgent->AddAction(NewObject<UAction>(this, ActionClass));
	}
}

void AMyCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	//PlayerAI->CheckIfAIWorks();
}

void AMyCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

TMap<FString, bool> AMyCharacter::GetWorldState()
{	
	//TODO WORLD STATE
	TMap<FString, bool> res = TMap<FString, bool>();

	if (Testing)
		res.Add("Testing", true);

    return res;
}

TMap<FString, bool> AMyCharacter::GetGoal()
{
	//TODO GOAL
	TMap<FString, bool> res = TMap<FString, bool>();

	if (Testing)
		res.Add("DoneTesting", true);
	else if (Hunger < 20)
	{
		//UE_LOG(LogTemp, Error, TEXT("Inside GetGoal"));
		res.Add("GetFood", true);
	}

    return res;
}

bool AMyCharacter::MoveToTarget(UAction *Action)
{
	return PlayerAI->MoveToTarget(this, Action);
}


void AMyCharacter::DecreaseHunger()
{
	if (Hunger == 0)
		Die();
	Hunger--;
}

void AMyCharacter::IncreaseHunger()
{
	Hunger = FMath::Clamp(Hunger += 1, 0, 100);
}

void AMyCharacter::Die()
{	
	PlayerAI->UnPossess();
	PlayerAI = nullptr;

	GetWorldTimerManager().ClearTimer(HungerTimerHandle);
	GetMesh()->SetCollisionProfileName(TEXT("Ragdoll"));
	GetMesh()->SetAllBodiesSimulatePhysics(true);
	GetCapsuleComponent()->SetWorldLocation(FVector::ZeroVector);
	GetCapsuleComponent()->SetWorldRotation(FRotator(90.0f, 0.0f, 0.0f));


	FTimerHandle Handle;
	GetWorldTimerManager().SetTimer(Handle, this, &AMyCharacter::DestroyChar, 5.0f, false);
}

void AMyCharacter::DestroyChar()
{
	this->Destroy();
}
