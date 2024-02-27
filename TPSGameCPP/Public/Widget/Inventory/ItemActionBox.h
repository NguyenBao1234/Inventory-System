// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ItemActionBox.generated.h"

/**
 * 
 */
class UButton;
UCLASS()
class TPSGAMECPP_API UItemActionBox : public UUserWidget
{
	GENERATED_BODY()

protected:
	virtual bool Initialize() override;
	void NativeConstruct() override;
public:
	UPROPERTY(meta = (BindWidget))
		UButton* Use;
	UPROPERTY(meta = (BindWidget))
		UButton* Combine;
	UPROPERTY(meta = (BindWidget))
		UButton* Examine;
	UPROPERTY(meta = (BindWidget))
		UButton* Cancel;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
		class UItemSlot* ItemSlotWD;

	UFUNCTION()
	void OnUseClicked();
	UFUNCTION()
	void OnCombineClicked();
	UFUNCTION()
	void OnExamineClicked();
	UFUNCTION()
	void OnCancelClicked();
	
	//true = popup ; false = remove
	UFUNCTION(BlueprintImplementableEvent,Blueprintcallable)
		void PopUpWD(bool bPopUp = true);

private:
	//HUDWD need be point to HUDWD of Player
	class UMainHUD* HUDWD;
};
