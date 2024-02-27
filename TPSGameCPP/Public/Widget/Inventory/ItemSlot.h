// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "InventoryStruct.h"
#include "Blueprint/UserWidget.h"
#include "ItemSlot.generated.h"

/**
 * 
 */
UCLASS()
class TPSGAMECPP_API UItemSlot : public UUserWidget
{
	GENERATED_BODY()

protected:
	virtual bool Initialize() override;
	void NativeConstruct() override;
	class AShooterCharacter* PlayerOwner;

public:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
		FInventoryStruct ItemData;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
		bool bCombining;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		uint8 IndexSlot;
	UFUNCTION()
	void ClickSlotButton();
	void UseItem();
	void ReduceItem();
	void RefreshSlot();
private:
	
	bool IsAvailableSpace();
	void CombineItem();
	void CombineFailed();
	UPROPERTY(meta = (BindWidget))
		class UButton* SlotButton;

	void AddHUDWDtoViewPort();
	
};
