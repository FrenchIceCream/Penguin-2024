// Fill out your copyright notice in the Description page of Project Settings.


#include "MyCharacter.h"
#include "Components/SkeletalMeshComponent.h"
#include "GameFramework/Actor.h"
#include "Kismet/GameplayStatics.h"
#include "NavMesh/NavMeshBoundsVolume.h"

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


	// UE_LOG(LogTemp, Warning, TEXT("%f:%f:%f"), GetMesh()->GetSocketTransform(RightSocketName).GetLocation().X, GetMesh()->GetSocketTransform(RightSocketName).GetLocation().Y, GetMesh()->GetSocketTransform(RightSocketName).GetLocation().Z);
	// UE_LOG(LogTemp, Warning, TEXT("%f:%f:%f"), GetMesh()->GetSocketLocation(LeftSocketName).X, GetMesh()->GetSocketLocation(LeftSocketName).Y, GetMesh()->GetSocketLocation(LeftSocketName).Z);
}

void AMyCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AMyCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}