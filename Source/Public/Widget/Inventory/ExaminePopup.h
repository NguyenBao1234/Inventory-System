// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ExaminePopup.generated.h"

/**
 * 
 */
UCLASS()
class TPSGAMECPP_API UExaminePopup : public UUserWidget
{
	GENERATED_BODY()
protected:
	virtual bool Initialize() override;
	UPROPERTY(meta = (BindWidget))
		class UTextBlock* ExamineText;

public:
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
		void PopupExamine(FText& ExamineInfor);
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
		void PopDownWD();

};
