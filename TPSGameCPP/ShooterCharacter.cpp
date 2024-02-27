// Fill out your copyright notice in the Description page of Project Settings.


#include "ShooterCharacter.h"
#include "Pistol.h"
#include "Rifle.h"
#include "ShotGun.h"
#include "ShooterGameModeBase.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Kismet/GameplayStatics.h"
#include "DrawDebugHelpers.h"

#include "Blueprint/UserWidget.h"
#include "Widget/MainHUD.h"

#include "InteractActor.h"
#include "ActorNeedItem.h"


// Sets default values
AShooterCharacter::AShooterCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	SpringArm = CreateDefaultSubobject<USpringArmComponent>("SpringArm");
	CameraTPS = CreateDefaultSubobject<UCameraComponent>("CameraFollow");
	SpringArm->SetupAttachment(RootComponent);
	
	CameraTPS->SetupAttachment(SpringArm);
	bUseControllerRotationYaw = false;
	
}

// Called when the game starts or when spawned
void AShooterCharacter::BeginPlay()
{
	Super::BeginPlay();
	DeltaT = GetWorld()->GetDeltaSeconds();
}

// Called every frame
void AShooterCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	UpdateSpringArm();
}

// Called to bind functionality to input
void AShooterCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	
	/*PlayerInputComponent->BindAxis(TEXT("MoveForward"), this, &AShooterCharacter::MoveForward);
	PlayerInputComponent->BindAxis(TEXT("MoveRight"), this, &AShooterCharacter::MoveRight);
	PlayerInputComponent->BindAction(TEXT("Shoot"), IE_Pressed, this, &AShooterCharacter::Shoot);
	PlayerInputComponent->BindAction(TEXT("Shoot"), IE_Released, this, &AShooterCharacter::Released);
	PlayerInputComponent->BindAction(TEXT("PistolEquip"), IE_Pressed, this, &AShooterCharacter::equipPistol);
	PlayerInputComponent->BindAction(TEXT("RifleEquip"), IE_Pressed, this, &AShooterCharacter::equipRifle);
	PlayerInputComponent->BindAction(TEXT("ShotgunEquip"), IE_Pressed, this, &AShooterCharacter::equipShotgun);
	PlayerInputComponent->BindAction(TEXT("Reload"), IE_Pressed, this, &AShooterCharacter::reload);*/
	PlayerInputComponent->BindAction(TEXT("Interact"), IE_Pressed, this, &AShooterCharacter::Interact);
	PlayerInputComponent->BindAction(TEXT("OpenHUD"), IE_Pressed, this, &AShooterCharacter::ToggleHUD);

}

/*void AShooterCharacter::MoveRight(float Value)
{
	Value *= GetWorld()->GetDeltaSeconds() * SpeedRotateControl;
	AddActorWorldRotation(FRotator(0,Value,0));
}*/





void AShooterCharacter::Interact()
{
	UClass* ActorFilter = AInteractActor::StaticClass();
	TArray<TEnumAsByte<EObjectTypeQuery>> ObjectQuery;
	TArray<AActor*> IgnoreActors;
	UWorld* ThisWorld = GetWorld();
	TArray<AActor*> OutActors;

	DrawDebugBox(GetWorld(), GetActorLocation(), FVector(88, 88, 88), FColor::Green, false, 2, 0, 2);
	bool interactable = UKismetSystemLibrary::BoxOverlapActors(this, GetActorLocation(), FVector(88, 88, 88), ObjectQuery, ActorFilter, IgnoreActors, OutActors);
	if (interactable)
	{
		for (AActor* ActorElement : OutActors)
		{
			AInteractActor* InteractActor = Cast<AInteractActor>(ActorElement);
			if (InteractActor) InteractActor->OnInteract();
		}
	}
}

//Deleted old information that is not related to functionality


//widget 

void AShooterCharacter::ToggleHUD()
{
	if (HUDWidgetTemplate)
	{
		APlayerController* PlayerController = UGameplayStatics::GetPlayerController(this, 0);
		if (!HUDWD) HUDWD = CreateWidget<UMainHUD>(GetWorld(), HUDWidgetTemplate);
		else UE_LOG(LogTemp, Display, TEXT("--'HUD k bi xoa'"))
		if (!HUDWD->IsInViewport())
		{
			HUDWD->PopupWD();
			FInputModeGameAndUI GnUMode;
			GnUMode.SetWidgetToFocus(HUDWD->GetCachedWidget());
			PlayerController->SetInputMode(GnUMode);			
			PlayerController->bShowMouseCursor = true;
		}
		else {
			HUDWD->PopupWD(false);
			FInputModeGameOnly GameMode;
			PlayerController->SetInputMode(GameMode);
			PlayerController->bShowMouseCursor = false;
		}
	}

}
