// Fill out your copyright notice in the Description page of Project Settings.
#pragma once

#include "CoreMinimal.h"
#include "ActorNeedItem.h"
#include "InventoryMaster.h"
#include "InventoryStruct.generated.h"

/**
 * 
 */
class AInventoryMaster;
USTRUCT(BlueprintType)
struct TPSGAMECPP_API FInventoryStruct
{
public:
	GENERATED_BODY()
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		TSet<AActorNeedItem*> CompatitionActors;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		uint8 InteractivePart=0;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		UTexture2D* Icon;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		FText NameItem;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		FText Description;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		FText ExamineData;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		uint8 NumberUses = 0;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		bool bCombinable = false;
	//Item itself belongs to Class
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
		TSubclassOf<AInventoryMaster> InventoryClass;
	//Key: Class Combine to / Value: Class from combine
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
		TMap<TSubclassOf<AInventoryMaster>, TSubclassOf<AInventoryMaster>> CombinationClass;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		bool bInfiniteUse = false;

	FInventoryStruct();
	~FInventoryStruct();
};
