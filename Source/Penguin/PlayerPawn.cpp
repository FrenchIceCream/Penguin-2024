// Fill out your copyright notice in the Description page of Project Settings.
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include "BuildingSystem/BuildingModeComponent.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"
#include "Components/InputComponent.h"
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

	TargetRotation = SpringArmComp->GetRelativeRotation();if (APlayerController* PLayerController = Cast<APlayerController>(GetController()))
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PLayerController->GetLocalPlayer()))
			Subsystem->AddMappingContext(DefaultMappingContext, 0);
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

	if (APlayerController* PLayerController = Cast<APlayerController>(GetController()))
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PLayerController->GetLocalPlayer()))
		{
			Subsystem->ClearAllMappings();
			Subsystem->AddMappingContext(DefaultMappingContext, 0);
		}
		BuildingModeComponent = UBuildingModeComponent::FindBuildingModeComponent(PLayerController);
	}

	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent))
	{
		//UE_LOG(LogTemp, Warning, TEXT("Has Enhanced Input"));
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &APlayerPawn::Move);
		EnhancedInputComponent->BindAction(RotateAction, ETriggerEvent::Triggered, this, &APlayerPawn::Rotate);
		EnhancedInputComponent->BindAction(RotateKeyboardAction, ETriggerEvent::Started, this, &APlayerPawn::RotateWithKeys);
		EnhancedInputComponent->BindAction(ZoomAction, ETriggerEvent::Triggered, this, &APlayerPawn::SetZoom);

		EnhancedInputComponent->BindAction(BuildDeployAction, ETriggerEvent::Triggered, this, &APlayerPawn::BuildDeploy);
		EnhancedInputComponent->BindAction(BuildCancelAction, ETriggerEvent::Triggered, this, &APlayerPawn::BuildCancel);
	}
}

//==================================	Enhanced input	==================================//

void APlayerPawn::Move(const FInputActionValue &Value)
{
	TargetLocation += SpringArmComp->GetTargetRotation().RotateVector(Value.Get<FVector>()) * FVector(1, 1, 0) * MoveSpeed;
}

void APlayerPawn::Rotate(const FInputActionValue &Value)
{
	TargetRotation = UKismetMathLibrary::ComposeRotators(TargetRotation, FRotator(0, Value.Get<float>() * RotateSpeed * 0.5, 0));
}

void APlayerPawn::RotateWithKeys(const FInputActionValue &Value)
{
	TargetRotation = UKismetMathLibrary::ComposeRotators(TargetRotation, FRotator(0, Value.Get<float>() * 45, 0));
}

void APlayerPawn::SetZoom(const FInputActionValue &Value)
{
	bZoomingIn = Value.Get<bool>();
}

//==================================	Input	==================================//

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


void APlayerPawn::BuildDeploy(const FInputActionValue & Value)
{
	if (!BuildingModeComponent)
		return;
	
	BuildingModeComponent->EnterBuildMode();
}

void APlayerPawn::BuildCancel(const FInputActionValue &Value)
{
	if (!BuildingModeComponent)
		return;

	BuildingModeComponent->ExitBuildMode();
}