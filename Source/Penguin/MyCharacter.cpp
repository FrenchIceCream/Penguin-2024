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
	// PlayerInputComponent->BindAxis(TEXT("MoveForward"), this, &AMyCharacter::MoveForward);
	// PlayerInputComponent->BindAxis(TEXT("MoveRight"), this, &AMyCharacter::MoveRight);
	// PlayerInputComponent->BindAxis(TEXT("Turn"), this, &AMyCharacter::AddControllerYawInput);
	// PlayerInputComponent->BindAxis(TEXT("LookUp"), this, &AMyCharacter::AddControllerPitchInput);
	// PlayerInputComponent->BindAction(TEXT("Sprint"), IE_Pressed, this, &AMyCharacter::SprintStart);
	// PlayerInputComponent->BindAction(TEXT("Sprint"), IE_Released, this, &AMyCharacter::SprintEnd);
}

// void AMyCharacter::MoveForward(float AxisVal)
// {
// 	const FRotator Rotation = Controller->GetControlRotation();
// 	const FRotator YawRotation(0, Rotation.Yaw, 0);

// 	const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
// 	AddMovementInput(Direction, AxisVal);
// }


// void AMyCharacter::MoveRight(float AxisVal)
// {
// 	const FRotator Rotation = Controller->GetControlRotation();
// 	const FRotator YawRotation(0, Rotation.Yaw, 0);

// 	const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
// 	AddMovementInput(Direction, AxisVal);
// }

// void AMyCharacter::SprintStart()
// {
// 	GetCharacterMovement()->MaxWalkSpeed = SprintSpeed;
// 	LeftFoot->SetStepTime(SprintSpeed);
// 	RightFoot->SetStepTime(SprintSpeed);
// }

// void AMyCharacter::SprintEnd()
// {
// 	GetCharacterMovement()->MaxWalkSpeed = WalkingSpeed;
// 	LeftFoot->SetStepTime(WalkingSpeed);
// 	RightFoot->SetStepTime(WalkingSpeed);
// }
