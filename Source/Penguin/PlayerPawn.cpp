// Fill out your copyright notice in the Description page of Project Settings.
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include "PlayerPawn.h"

// Sets default values
APlayerPawn::APlayerPawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootSceneComponent"));
	SpringArmComp = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArmComponent"));
	CameraComp = CreateDefaultSubobject<UCameraComponent>(TEXT("CameraComponent"));

	SpringArmComp->SetupAttachment(RootComponent);
	CameraComp->SetupAttachment(SpringArmComp,USpringArmComponent::SocketName);

	SpringArmComp->SetRelativeLocationAndRotation(FVector(0.0f, 0.0f, 300.0f), FRotator(CameraAngle, 0.0f, 0.0f));
	SpringArmComp->bDoCollisionTest = false;
}

// Called when the game starts or when spawned
void APlayerPawn::BeginPlay()
{
	Super::BeginPlay();	

	TargetRotation = SpringArmComp->GetRelativeRotation();
}

// Called every frame
void APlayerPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	Zoom(DeltaTime);
	SetActorLocation(UKismetMathLibrary::VInterpTo(GetActorLocation(), TargetLocation, DeltaTime, MoveSpeed));
	SpringArmComp->SetRelativeRotation(UKismetMathLibrary::RInterpTo(SpringArmComp->GetRelativeRotation(), TargetRotation, DeltaTime, RotateSpeed));	
}

// Called to bind functionality to input
void APlayerPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAction("ZoomIn", IE_Pressed, this, &APlayerPawn::ZoomIn);
	PlayerInputComponent->BindAction("ZoomIn", IE_Released, this, &APlayerPawn::ZoomOut);
	
	PlayerInputComponent->BindAxis("MoveForward", this, &APlayerPawn::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &APlayerPawn::MoveRight);
	PlayerInputComponent->BindAxis("RotateHorizontal", this, &APlayerPawn::RotateHorizontal);

	PlayerInputComponent->BindAction("Rotate", IE_Pressed, this, &APlayerPawn::EnableRotate);
	PlayerInputComponent->BindAction("Rotate", IE_Released, this, &APlayerPawn::DisableRotate);
	PlayerInputComponent->BindAction("RotateLeft", IE_Pressed, this, &APlayerPawn::RotateRight);
	PlayerInputComponent->BindAction("RotateRight", IE_Pressed, this, &APlayerPawn::RotateLeft);
}

void APlayerPawn::MoveForward(float AxisValue)
{
	if (AxisValue == 0)
		return;

	TargetLocation = TargetLocation + SpringArmComp->GetForwardVector() * FVector(1, 1, 0) * AxisValue * MoveSpeed;
}

void APlayerPawn::MoveRight(float AxisValue)
{
	if (AxisValue == 0)
		return;
	TargetLocation = TargetLocation + SpringArmComp->GetRightVector() * AxisValue * MoveSpeed;
}

void APlayerPawn::Zoom(float DeltaTime)
{
	if (bZoomingIn)
        ZoomFactor += DeltaTime / 0.35f;         //Zoom in over 0.35 a second
    else
        ZoomFactor -= DeltaTime / 0.25f;        //Zoom out over a quarter of a second

    ZoomFactor = FMath::Clamp<float>(ZoomFactor, 0.0f, 1.0f);

    CameraComp->FieldOfView = FMath::Lerp<float>(90.0f, 60.0f, ZoomFactor);
    SpringArmComp->TargetArmLength = FMath::Lerp<float>(MaxZoom, MinZoom, ZoomFactor);
}

void APlayerPawn::ZoomIn()
{
    bZoomingIn = true;
}

void APlayerPawn::ZoomOut()
{
    bZoomingIn = false;
}

void APlayerPawn::EnableRotate()
{
	bRotate = true;
}

void APlayerPawn::DisableRotate()
{
	bRotate = false;
}

void APlayerPawn::RotateLeft()
{
	TargetRotation = UKismetMathLibrary::ComposeRotators(TargetRotation, FRotator(0, -45, 0));
}

void APlayerPawn::RotateRight()
{
	TargetRotation = UKismetMathLibrary::ComposeRotators(TargetRotation, FRotator(0, 45, 0));
}

void APlayerPawn::RotateHorizontal(float AxisValue)
{
	if (AxisValue == 0)
	return;

	if (bRotate)
		TargetRotation = UKismetMathLibrary::ComposeRotators(TargetRotation, FRotator(0, AxisValue * RotateSpeed * 0.5, 0));
}