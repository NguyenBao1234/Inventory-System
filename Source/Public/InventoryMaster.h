// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "InteractActor.h"
#include "InventoryMaster.generated.h"

//InventoryMaster not contain ItemProperty, just have virtual function
UCLASS()
class TPSGAMECPP_API AInventoryMaster : public AInteractActor
{
	GENERATED_BODY()
public:
	void OnInteract() override;
	virtual void PickUpItem();
};
