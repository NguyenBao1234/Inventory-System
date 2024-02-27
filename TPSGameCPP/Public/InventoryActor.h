// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "InventoryMaster.h"
#include "InventoryStruct.h"
#include "InventoryActor.generated.h"

//InventoryActor contained ItemProperty
UCLASS()
class TPSGAMECPP_API AInventoryActor : public AInventoryMaster
{
	GENERATED_BODY()
public:
	// Sets default values for this actor's properties
	AInventoryActor();
public:
	UPROPERTY(EditAnywhere)
	FInventoryStruct ItemProperty;

	virtual void PickUpItem() override;
};
