// Fill out your copyright notice in the Description page of Project Settings.

#include "Widget/Inventory/ItemActionBox.h"
#include "Components/Button.h"

#include "Kismet/GameplayStatics.h"
#include "TpSGameCPP/ShooterCharacter.h"
#include "Widget/MainHUD.h"
#include "Widget/Inventory/InventoryUI.h"
#include "Widget/Inventory/ItemSlot.h"
#include "Widget/Inventory/ExaminePopup.h"
#include "InventoryStruct.h"
#include "Components/ScrollBox.h"

bool UItemActionBox::Initialize()
{
	bool Success = Super::Initialize();
	if (!Success) return false;

	if (!ensure(Use != nullptr)) return false;
	Use->OnClicked.AddDynamic(this, &UItemActionBox::OnUseClicked);
	if (!ensure(Combine != nullptr)) return false;
	Combine->OnClicked.AddDynamic(this, &UItemActionBox::OnCombineClicked);
	if (!ensure(Examine != nullptr)) return false;
	Examine->OnClicked.AddDynamic(this, &UItemActionBox::OnExamineClicked);
	if (!ensure(Cancel != nullptr)) return false;
	Cancel->OnClicked.AddDynamic(this, &UItemActionBox::OnCancelClicked);
	return true;
}

void UItemActionBox::NativeConstruct()
{
	Super::NativeConstruct();
	HUDWD = Cast<AShooterCharacter>(UGameplayStatics::GetPlayerCharacter(this, 0))->HUDWD;
}

void UItemActionBox::OnUseClicked()
{
	UE_LOG(LogTemp, Display, TEXT("Button 'Use' clicked"));
	if (ItemSlotWD) ItemSlotWD->UseItem();
	PopUpWD(false);
}

void UItemActionBox::OnCombineClicked()
{
	UE_LOG(LogTemp, Display, TEXT("Button 'Combine' clicked"));
	PopUpWD(false);
	if (HUDWD)
	{
		TArray<UWidget*> WDsInScrollBox = HUDWD->InventoryUIWD->ItemScrollBox->GetAllChildren();
		for (UWidget* WidgetChild : WDsInScrollBox)
		{
			UItemSlot* WidgetSlot = Cast<UItemSlot>(WidgetChild);
			if (WidgetSlot) WidgetSlot->bCombining = true;
		}
	}
}

void UItemActionBox::OnExamineClicked()
{
	UE_LOG(LogTemp, Display, TEXT("Button 'Examine' clicked"));
	if (!ItemSlotWD) return;
	if(HUDWD) HUDWD->ExamineWD->PopupExamine(ItemSlotWD->ItemData.ExamineData);
}

void UItemActionBox::OnCancelClicked()
{
	UE_LOG(LogTemp, Display, TEXT("Button 'Cancel' clicked"));
	PopUpWD(false);
}
