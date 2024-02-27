// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "InteractActor.h"
#include "InteractActorB.generated.h"

/**
 * 
 */
UCLASS()
class TPSGAMECPP_API AInteractActorB : public AInteractActor
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintImplementableEvent)
		void OnInteractBP();
	void OnInteract() override;
};
