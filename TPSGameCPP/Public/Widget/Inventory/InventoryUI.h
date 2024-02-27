// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "InventoryUI.generated.h"

/**
 * 
 */
UCLASS()
class TPSGAMECPP_API UInventoryUI : public UUserWidget
{
	GENERATED_BODY()
protected:
	virtual bool Initialize() override;
	void NativeConstruct() override;

public:
	UPROPERTY(meta = (BindWidget))
		class UScrollBox* ItemScrollBox;
	
};
