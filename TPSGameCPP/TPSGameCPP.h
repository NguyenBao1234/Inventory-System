// Copyright Nguyen Van Bao, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "TPSGameCPP.generated.h"

USTRUCT(BlueprintType)
struct FGunStruct
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere)
		float fireRange = 40000;
	UPROPERTY(EditAnywhere)
		float DamageBullet = 20;

	uint8 currentAmmo;
	uint8 clipSizeAmmo;
	int16 remainingAmmo;
	//fireRate la so vien dan ban duoc trong 1 giay
	UPROPERTY(EditAnywhere)
		float fireRate = 2;
	UPROPERTY(EditAnywhere)
	float impulseStrength = 0;
	
};

UENUM(BlueprintType)
enum EGunInHand
{
	Hand	UMETA(DisplayName = "Hand"),
	Pistol	UMETA(DisplayName = "Pistol"),
	Rifle	UMETA(DisplayName = "Rifle"),
	Shotgun UMETA(DisplayName = "Shotgun")
};

USTRUCT(BlueprintType)
struct FStatePlayer
{
	GENERATED_USTRUCT_BODY()
		FVector locationAtMap;
		float health=100;
		UPROPERTY(EditAnywhere)
			uint16 SizeInventory = 6;

		UPROPERTY(BlueprintReadOnly)
		TEnumAsByte<EGunInHand> gunInHand {EGunInHand::Hand};
		bool hasPistol = false;
		bool hasRifle = false;
		bool hasShotgun = false;

		FGunStruct pistolState;
		FGunStruct rifleState;
		FGunStruct shotgunState;

};
