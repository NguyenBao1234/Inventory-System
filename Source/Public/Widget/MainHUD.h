// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MainHUD.generated.h"

/**
 * 
 */
UCLASS()
class TPSGAMECPP_API UMainHUD : public UUserWidget
{
	GENERATED_BODY()
public:
	UPROPERTY(meta = (BindWidget), BlueprintReadOnly)
		class UItemActionBox* ActionBoxWD;
	UPROPERTY(meta = (BindWidget))
		class UInventoryUI* InventoryUIWD;
	UPROPERTY(meta = (BindWidget), BlueprintReadOnly)
		class UExaminePopup* ExamineWD;
	UFUNCTION(BlueprintNativeEvent)
	void PopupWD(bool bPopUp = true);

protected:
	void NativeConstruct() override;
	bool Initialize() override;

};
