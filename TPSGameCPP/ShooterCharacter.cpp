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
	
	PlayerInputComponent->BindAxis(TEXT("MoveForward"), this, &AShooterCharacter::MoveForward);
	PlayerInputComponent->BindAxis(TEXT("MoveRight"), this, &AShooterCharacter::MoveRight);
	PlayerInputComponent->BindAction(TEXT("Shoot"), IE_Pressed, this, &AShooterCharacter::Shoot);
	PlayerInputComponent->BindAction(TEXT("Shoot"), IE_Released, this, &AShooterCharacter::Released);
	PlayerInputComponent->BindAction(TEXT("PistolEquip"), IE_Pressed, this, &AShooterCharacter::equipPistol);
	PlayerInputComponent->BindAction(TEXT("RifleEquip"), IE_Pressed, this, &AShooterCharacter::equipRifle);
	PlayerInputComponent->BindAction(TEXT("ShotgunEquip"), IE_Pressed, this, &AShooterCharacter::equipShotgun);
	PlayerInputComponent->BindAction(TEXT("Reload"), IE_Pressed, this, &AShooterCharacter::reload);
	PlayerInputComponent->BindAction(TEXT("Interact"), IE_Pressed, this, &AShooterCharacter::Interact);
	PlayerInputComponent->BindAction(TEXT("OpenHUD"), IE_Pressed, this, &AShooterCharacter::ToggleHUD);

}



void AShooterCharacter::MoveForward(float Value)
{
	AddMovementInput(GetActorForwardVector() * Value);
}

void AShooterCharacter::MoveRight(float Value)
{
	Value *= GetWorld()->GetDeltaSeconds() * SpeedRotateControl;
	AddActorWorldRotation(FRotator(0,Value,0));
}


void AShooterCharacter::UpdateSpringArm()
{
	float DeltaSecs = GetWorld()->GetDeltaSeconds();
	FRotator YawAimFoward = FMath::RInterpTo(GetControlRotation(), GetActorRotation(),DeltaSecs, SpeedTransToAim);
	GetController()->SetControlRotation(FRotator(GetControlRotation().Pitch, YawAimFoward.Yaw, GetControlRotation().Roll));
	SpringArm->SetWorldLocation(FMath::VInterpTo(SpringArm->GetComponentLocation(), GetActorLocation() + FVector(0,0,87), DeltaSecs, SpeedTransToAim));
}



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




//Event
void AShooterCharacter::pickUpPistol()
{
	Pistol = GetWorld()->SpawnActor<APistol>(PistolBP);
	Pistol->OwnerOfGun = this;
	Pistol->AttachToComponent(GetMesh(), FAttachmentTransformRules::KeepRelativeTransform, TEXT("PistolHolsterSocket"));
	if (currentStatePlayer.hasPistol)
	{
		Pistol->gunState = currentStatePlayer.pistolState;
	}
	Pistol->gunState.remainingAmmo += currentStatePlayer.pistolState.remainingAmmo;
	currentStatePlayer.hasPistol = true;
}

void AShooterCharacter::pickUpRifle()
{
	
	Rifle = GetWorld()->SpawnActor<ARifle>(RifleBP);
	Rifle->OwnerOfGun = this;
	Rifle->AttachToComponent(GetMesh(), FAttachmentTransformRules::KeepRelativeTransform, TEXT("RifleHolsterSocket"));
	if (currentStatePlayer.hasRifle)
	{//do chi nhat duoc 1 lan, nen khi nhat ta se luu nen khi restore chac chan rifleState cua player da duoc cap nhap dung
		Rifle->gunState = currentStatePlayer.rifleState;
	}
	Rifle->gunState.remainingAmmo += currentStatePlayer.rifleState.remainingAmmo;
	currentStatePlayer.hasRifle = true;
}

void AShooterCharacter::pickUpShotgun()
{
	Shotgun = GetWorld()->SpawnActor<AShotgun>(ShotgunBP);
	Shotgun->OwnerOfGun = this;
	Shotgun->AttachToComponent(GetMesh(), FAttachmentTransformRules::KeepRelativeTransform, TEXT("ShotgunHolsterSocket"));
	if (currentStatePlayer.hasShotgun)
	{
		Shotgun->gunState = currentStatePlayer.shotgunState;
	}
	Shotgun->gunState.remainingAmmo += currentStatePlayer.shotgunState.remainingAmmo;
	currentStatePlayer.hasShotgun = true;
}




void AShooterCharacter::unequipAll()
{
	currentStatePlayer.gunInHand = EGunInHand::Hand;
	if (currentStatePlayer.hasPistol)
	{
		if (Pistol)  Pistol->AttachToComponent(GetMesh(), FAttachmentTransformRules::KeepRelativeTransform, TEXT("PistolHolsterSocket"));  
	}
	if (currentStatePlayer.hasRifle)
	{
		if (Rifle) Rifle->AttachToComponent(GetMesh(), FAttachmentTransformRules::KeepRelativeTransform, TEXT("RifleHolsterSocket"));
	}
	if (currentStatePlayer.hasShotgun)
	{
		if(Shotgun) Shotgun->AttachToComponent(GetMesh(), FAttachmentTransformRules::KeepRelativeTransform, TEXT("ShotgunHolsterSocket"));
	}
}

void AShooterCharacter::equipPistol()
{
	if (currentStatePlayer.gunInHand != EGunInHand::Pistol)
	{
		if (Pistol)
		{
			unequipAll();
			currentStatePlayer.gunInHand = EGunInHand::Pistol;
			Pistol->AttachToComponent(GetMesh(), FAttachmentTransformRules::KeepRelativeTransform, TEXT("GunSocket"));
		}
	}
	else unequipAll();

}

void AShooterCharacter::equipRifle()
{
	
	if (currentStatePlayer.gunInHand != EGunInHand::Rifle)
	{
		if (Rifle)
		{
			unequipAll();
			currentStatePlayer.gunInHand = EGunInHand::Rifle;
			Rifle->AttachToComponent(GetMesh(), FAttachmentTransformRules::KeepRelativeTransform, TEXT("GunSocket"));
		}
	}
	else unequipAll();
}

void AShooterCharacter::equipShotgun()
{
		
	if (currentStatePlayer.gunInHand != EGunInHand::Shotgun)
	{
		if (Shotgun)
		{
			unequipAll();
			currentStatePlayer.gunInHand = EGunInHand::Shotgun;
			Shotgun->AttachToComponent(GetMesh(), FAttachmentTransformRules::KeepRelativeTransform, TEXT("GunSocket"));
		}
	}
	else unequipAll();
}

void AShooterCharacter::pickUpAmmo(EGunInHand AmmoType, uint8 Amount)
{
	switch (AmmoType)
	{
	case EGunInHand::Pistol:if(Pistol) Pistol->gunState.remainingAmmo += Amount;
		currentStatePlayer.pistolState.remainingAmmo += Amount;
		break;
	case EGunInHand::Rifle: if(Rifle) Rifle->gunState.remainingAmmo += Amount;
		currentStatePlayer.rifleState.remainingAmmo += Amount;
		break;
	case EGunInHand::Shotgun:if(Shotgun) Shotgun->gunState.remainingAmmo += Amount;
		currentStatePlayer.shotgunState.remainingAmmo += Amount;
		break;
	default:
		break;
	}
}

//game play
void AShooterCharacter::AimEnemy()
{
	UWorld* ThisWorld = GetWorld();
	FHitResult hitSweepResult;
	FVector StartTrace = GetActorLocation() + FVector(0,0,50);
	FVector EndTrace = StartTrace + GetActorForwardVector();
	FCollisionShape Sphere = FCollisionShape::MakeSphere(50);
	bool hasSeenEnemy = ThisWorld->SweepSingleByChannel(hitSweepResult,StartTrace,EndTrace, FQuat::Identity, ECC_GameTraceChannel1,Sphere);
}

void AShooterCharacter::Released()
{
	if (currentStatePlayer.gunInHand != EGunInHand::Hand)
	{
		switch (currentStatePlayer.gunInHand)
		{
		case EGunInHand::Pistol:
			Pistol->ReleasedTrigger();
			break;
		case EGunInHand::Rifle:
			Rifle->ReleasedTrigger();
			break;
		case EGunInHand::Shotgun:
			Shotgun->ReleasedTrigger();
			break;
		default:
			break;
		}
	}
}

void AShooterCharacter::Shoot()
{
	if (currentStatePlayer.gunInHand != EGunInHand::Hand)
	{
		switch (currentStatePlayer.gunInHand)
		{
		case EGunInHand::Pistol:
			Pistol->HoldTrigger();
			break;
		case EGunInHand::Rifle:if (Rifle->gunState.currentAmmo > 0)
		{
			Rifle->HoldTrigger();
		}
			break;
		case EGunInHand::Shotgun:if (Shotgun->gunState.currentAmmo > 0)
		{
			Shotgun->HoldTrigger();
		}
			break;
		default://tuong tac thuong
			break;
		}
	}

}



void AShooterCharacter::reload()
{
	
		if (currentStatePlayer.gunInHand != EGunInHand::Hand)
	{
		switch (currentStatePlayer.gunInHand)
		{
		case EGunInHand::Pistol:if (Pistol->gunState.remainingAmmo > 0) {
			reloadAnimation();
			Pistol->Reload();
			}
			break;
		case EGunInHand::Rifle:if (Rifle->gunState.remainingAmmo > 0) {
			reloadAnimation();
			Rifle->Reload();
			}
			break;
		case EGunInHand::Shotgun:if (Shotgun->gunState.remainingAmmo > 0) {
			reloadAnimation();
			Shotgun->Reload();
			}
			break;
		default:
			break;
		}
	}
}


void AShooterCharacter::reloadAnimation()
{
	switch (currentStatePlayer.gunInHand)
		{
		case EGunInHand::Pistol:if (Pistol->gunState.remainingAmmo > 0) {
			if(M_AnimReloadPChar) PlayAnimMontage(M_AnimReloadPChar);
			}
			break;
		case EGunInHand::Rifle:if (Rifle->gunState.remainingAmmo > 0) {
			if(M_AnimReloadPChar) PlayAnimMontage(M_AnimReloadRChar);
			}
			break;
		case EGunInHand::Shotgun:if (Shotgun->gunState.remainingAmmo > 0) {
			if(M_AnimReloadSChar) PlayAnimMontage(M_AnimReloadSChar);
			}
			break;
		default:
			break;
		}
}

void AShooterCharacter::shootAnimation()
{
	switch (currentStatePlayer.gunInHand)
	{
	case EGunInHand::Pistol:
		break;
	case EGunInHand::Rifle:	
		if (M_AnimFireRChar) PlayAnimMontage(M_AnimFireRChar);
		break;
	case EGunInHand::Shotgun:
		if (M_AnimFireSChar) PlayAnimMontage(M_AnimFireSChar);
		break;
	default:
		break;
	}
}

float AShooterCharacter::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	float DamageReceive = Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);
	DamageReceive = FMath::Min(currentStatePlayer.health, DamageReceive);
	currentStatePlayer.health -= DamageReceive;
	UE_LOG(LogTemp, Display, TEXT("Health con lai la %f"), currentStatePlayer.health);
	if (currentStatePlayer.health == 0)
	{
		AShooterGameModeBase* ShGameMode = Cast<AShooterGameModeBase>(GetWorld()->GetAuthGameMode());
		if (ShGameMode)
		{
			ShGameMode->PawnKilled(this);
		}
		SetActorEnableCollision(false);
		DetachFromControllerPendingDestroy();
	}
	return 0;
}



//Get State

bool AShooterCharacter::isAlive()
{
		return currentStatePlayer.health > 0;
}

float AShooterCharacter::GetHealthPercent()
{
	float Percent = currentStatePlayer.health / MaxHealth;
	return Percent;
}

EGunInHand AShooterCharacter::GetGunInHand()
{
	EGunInHand GunHolding = currentStatePlayer.gunInHand;
	return GunHolding;
}


void AShooterCharacter::restoreState(FStatePlayer PlayerCacheSave)
{
	currentStatePlayer = PlayerCacheSave;
	this->SetActorLocation(currentStatePlayer.locationAtMap);
	if (currentStatePlayer.hasPistol) pickUpPistol();
	if (currentStatePlayer.hasRifle) pickUpRifle();
	if (currentStatePlayer.hasShotgun) pickUpShotgun();
}


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
