// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "InteractActorB.h"
#include "ActorNeedItem.generated.h"

/**
 * 
 */
UCLASS()
class TPSGAMECPP_API AActorNeedItem : public AInteractActorB
{
	GENERATED_BODY()
public:
	AActorNeedItem();

public:
	UFUNCTION(BlueprintImplementableEvent)
		void InteractWithItem(uint8 InteractivePart);
	UPROPERTY(BlueprintReadWrite,BlueprintReadWrite)
		bool bUnlock;

	void OnInteract() override;

	void SetUpOverlap(bool bOverlapped) override;
	UFUNCTION(BlueprintImplementableEvent)
		void SetUpOverlap_iBP(bool bOverLapped);

};
