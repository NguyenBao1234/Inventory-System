// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "TPSGameCPP.h"
#include "InventoryStruct.h"
#include "ShooterCharacter.generated.h"


class APistol;
class ARifle;
class AShotgun;
UCLASS()
class TPSGAMECPP_API AShooterCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AShooterCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float Delta) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	void Interact();
	void AimEnemy();
	void Shoot();
	void Released();
	void reload();
	void ToggleHUD();

	void reloadAnimation();
	void shootAnimation();
	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser)override;

	UFUNCTION(BlueprintPure)
		bool isAlive();

	UFUNCTION(BlueprintPure)
		float GetHealthPercent();

	UFUNCTION(BlueprintPure)
		EGunInHand GetGunInHand();

	// Restore the status player to as the same point save
	void restoreState(FStatePlayer PlayerCacheSave);
	//pick up gun
	UFUNCTION(BlueprintCallable)
	void pickUpPistol();
	UFUNCTION(BlueprintCallable)
	void pickUpRifle();
	UFUNCTION(BlueprintCallable)
	void pickUpShotgun();
	//equip gun
	void unequipAll();
	void equipPistol();
	void equipRifle();
	void equipShotgun();

	//pickUp item
	void pickUpAmmo(EGunInHand AmmoType, uint8 Amount);

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = UI)
		TSubclassOf<class UMainHUD> HUDWidgetTemplate;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
		uint8 SizeInventory = 5;
	class UMainHUD* HUDWD;
	TArray<FInventoryStruct> PickedItems;
	class AActorNeedItem* ActorNeedItem;

private:

	APistol* Pistol;
	ARifle* Rifle;
	AShotgun* Shotgun;
	FStatePlayer currentStatePlayer;

	UPROPERTY(VisibleAnywhere)
		UCameraComponent* CameraTPS;

	UPROPERTY(VisibleAnywhere)
		USpringArmComponent* SpringArm;

	void MoveForward(float Value);
	void MoveRight(float Value);


	UPROPERTY(EditAnywhere, Category = "WPistol")
		TSubclassOf<APistol> PistolBP;
	UPROPERTY(EditAnywhere, Category = "WRifle")
		TSubclassOf<ARifle> RifleBP;
	UPROPERTY(EditAnywhere, Category = "WShotgun")
		TSubclassOf<AShotgun> ShotgunBP;

	UPROPERTY(EditAnywhere, Category = "WPistol")
		UAnimMontage* M_AnimReloadPChar;
	UPROPERTY(EditAnywhere, Category = "WRifle")
		UAnimMontage* M_AnimFireRChar;
	UPROPERTY(EditAnywhere, Category = "WRifle")
		UAnimMontage* M_AnimReloadRChar;
	UPROPERTY(EditAnywhere, Category = "WShotgun")
		UAnimMontage* M_AnimFireSChar;
	UPROPERTY(EditAnywhere, Category = "WShotgun")
		UAnimMontage* M_AnimReloadSChar;
	UPROPERTY(EditAnywhere)
		float MaxHealth = 100;

	UPROPERTY(EditAnywhere)
		uint8 SpeedTransToAim = 1;
	UPROPERTY(EditAnywhere)
		uint8 SpeedRotateControl = 150;
	float DeltaT;
	void UpdateSpringArm();
	bool bAiming = false;

};
