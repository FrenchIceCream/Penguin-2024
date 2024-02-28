// Fill out your copyright notice in the Description page of Project Settings.

#include "SpawnPoint.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
ASpawnPoint::ASpawnPoint()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	StaticMeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));
	StaticMeshComp->SetupAttachment(RootComponent);
}

void ASpawnPoint::ToggleSpawnWidget(UPrimitiveComponent* Target, FKey ButtonPressed)
{
	IsButtonVisible = !IsButtonVisible;
	IsButtonVisible ? ButtonWidget->SetVisibility(ESlateVisibility::Visible) : ButtonWidget->SetVisibility(ESlateVisibility::Hidden);
}

void ASpawnPoint::SpawnActor()
{
	GetWorld()->SpawnActor<AActor>(ActorToSpawn.LoadSynchronous(), GetActorLocation() + EntrancePos, GetActorRotation());
}

// Called when the game starts or when spawned
void ASpawnPoint::BeginPlay()
{
	Super::BeginPlay();

	verify ((PlayerController = Cast<APlayerControl>(UGameplayStatics::GetPlayerController(GetWorld(), 0))) != nullptr);
	
	if(ButtonWidgetClass)
	{
		//UE_LOG(LogTemp, Warning, TEXT("Has ButtonWidgetClass"));
		ButtonWidget = CreateWidget<UGenericButtonWidget>(GetWorld(), ButtonWidgetClass);

		if (ButtonWidget)
		{
			//UE_LOG(LogTemp, Warning, TEXT("Has Button"));
			ButtonWidget->AddToViewport();
			ButtonWidget->SetVisibility(ESlateVisibility::Hidden);
			ButtonWidget->Button->OnClicked.AddDynamic(this, &ASpawnPoint::SpawnActor);
		}
	}
	
	//StaticMeshComp->OnClicked.AddDynamic(this, &ASpawnPoint::ShowSpawnWidget);
}



// Called every frame
void ASpawnPoint::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (IsButtonVisible)
	{
		FVector2D ScreenPosition;
		bool bIsVisible = UGameplayStatics::ProjectWorldToScreen(PlayerController, GetActorLocation(), ScreenPosition);

		// UE_LOG(LogTemp, Warning, TEXT("%f;%f"), GetActorLocation().X, GetActorLocation().Y);
		// UE_LOG(LogTemp, Warning, TEXT("%f;%f"), ScreenPosition.X, ScreenPosition.Y);
		ButtonWidget->SetPositionInViewport(ScreenPosition /*- FVector2D(ButtonWidget->GetDesiredSize().X / 2, 0)*/, true);
	}
}

