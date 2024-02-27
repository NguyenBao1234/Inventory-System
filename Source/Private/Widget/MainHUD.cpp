// Fill out your copyright notice in the Description page of Project Settings.


#include "Widget/MainHUD.h"
#include "Widget/Inventory/ItemActionBox.h"
#include "Widget/Inventory/InventoryUi.h"
#include "Widget/Inventory/ExaminePopup.h"

bool UMainHUD::Initialize()
{
	bool Success = Super::Initialize();
	if(!ensure(ActionBoxWD!=nullptr)) return false;
	if (!ensure(InventoryUIWD != nullptr)) return false;
	if (!ensure(ExamineWD != nullptr)) return false;
	return true;
}



void UMainHUD::NativeConstruct()
{
	Super::NativeConstruct();
}


void UMainHUD::PopupWD_Implementation(bool bPopup)
{
	if (bPopup) AddToViewport();
	else RemoveFromParent();	
}