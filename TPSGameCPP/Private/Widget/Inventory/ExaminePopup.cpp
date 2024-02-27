// Fill out your copyright notice in the Description page of Project Settings.


#include "Widget/Inventory/ExaminePopup.h"
#include "Components/TextBlock.h"


bool UExaminePopup::Initialize()
{
	if(!Super::Initialize()) return false;
	if (!ensure(ExamineText != nullptr)) return false;
	return true;
}

void UExaminePopup::PopupExamine_Implementation(FText& ExamineInfor)
{
	ExamineText->SetText(ExamineInfor);
	SetVisibility(ESlateVisibility::Visible);
}

void UExaminePopup::PopDownWD_Implementation()
{
	SetVisibility(ESlateVisibility::Hidden);
}
