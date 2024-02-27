// Fill out your copyright notice in the Description page of Project Settings.

#include "InteractActor.h"
#include<GameFramework/PlayerController.h>
#include<TPSGameCPP/ShooterCharacter.h>	

// Sets default values
AInteractActor::AInteractActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	BoxTrigger = CreateDefaultSubobject<UBoxComponent>("BoxTrigger");
	HintWD = CreateDefaultSubobject<UWidgetComponent>("Hint Widget");
	SceneRoot = CreateDefaultSubobject<USceneComponent>("Scene");
	RootComponent = SceneRoot;

	BoxTrigger->SetupAttachment(SceneRoot);
	HintWD->SetupAttachment(SceneRoot);

	HintWD->SetWidgetSpace(EWidgetSpace::Screen);
	HintWD->SetDrawAtDesiredSize(true);
	HintWD->SetVisibility(false);
	HintWD->SetRelativeLocation(FVector(0, 0, 40));

	OnActorBeginOverlap.AddDynamic(this, &AInteractActor::OnPlayerOverlap);
	OnActorEndOverlap.AddDynamic(this, &AInteractActor::EndPlayerOverlap);
}

// Called when the game starts or when spawned
void AInteractActor::BeginPlay()
{
	Super::BeginPlay();
	PlayerController = GetWorld()->GetFirstPlayerController();
}

// Called every frame
void AInteractActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}



void AInteractActor::OnInteract()
{
	UE_LOG(LogTemp, Display, TEXT("actor has been interacted"));
}

void AInteractActor::SetUpOverlap(bool bOverlapped)
{
	UE_LOG(LogTemp, Display, TEXT("Set Up for Overlap/Out"));
}

void AInteractActor::OnPlayerOverlap(AActor* OverlappedActor, AActor* OtherActor)
{
	PlayerChar = Cast<AShooterCharacter>(OtherActor);
	if (!PlayerChar) return;
	if (PlayerController)
	{
		EnableInput(PlayerController);
		if (HintWD) HintWD->SetVisibility(true);
		UE_LOG(LogTemp, Display, TEXT("BeginOverLap Shooter Char"));
		SetUpOverlap();
	}
	
}

void AInteractActor::EndPlayerOverlap(AActor* OverlappedActor, AActor* OtherActor)
{
	PlayerChar = Cast<AShooterCharacter>(OtherActor);
	if (!PlayerChar) return;
	if (PlayerController)
	{
		DisableInput(PlayerController);
		if (HintWD) HintWD->SetVisibility(false);
		UE_LOG(LogTemp, Display, TEXT("EndOverLap ShooterChar"));
		SetUpOverlap(false);
	}
}

