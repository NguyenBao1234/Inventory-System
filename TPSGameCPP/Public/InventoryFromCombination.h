// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "InventoryActor.h"
#include "InventoryFromCombination.generated.h"

/**
 * 
 */
UCLASS()
class TPSGAMECPP_API AInventoryFromCombination : public AInventoryActor
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, Category = "InventoryActor")
	TSubclassOf<class AActorNeedItem> ClassActorNeedItem;
	void PickUpItem() override;
};
