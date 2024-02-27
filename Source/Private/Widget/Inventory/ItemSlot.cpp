// Fill out your copyright notice in the Description page of Project Settings.


#include "Widget/Inventory/ItemSlot.h"
#include <Components/Button.h>
#include "TPSGameCPP/ShooterCharacter.h"

#include "Blueprint/WidgetLayoutLibrary.h"
#include "Components/CanvasPanelSlot.h"
#include "GameFramework/PlayerController.h"
#include <Kismet/GameplayStatics.h>
#include <Engine/World.h>

#include <TimerManager.h>
#include "Widget/MainHUD.h"
#include "Widget/Inventory/ItemActionBox.h"
#include "Widget/Inventory/InventoryUI.h"
#include <Components/ScrollBox.h>


bool UItemSlot::Initialize()
{
	bool Success = Super::Initialize();
	if (!Success) return false;
	if (!ensure(SlotButton != nullptr)) return false;
	SlotButton->OnClicked.AddDynamic(this, &UItemSlot::ClickSlotButton);
	return true;
}

void UItemSlot::NativeConstruct()
{
	Super::NativeConstruct();
	PlayerOwner = Cast<AShooterCharacter>(UGameplayStatics::GetPlayerCharacter(this, 0));
	if (PlayerOwner->PickedItems.IsValidIndex(IndexSlot)) ItemData = PlayerOwner->PickedItems[IndexSlot];
	else { ItemData = {}; ItemData.Icon = NULL; }
}


void UItemSlot::ClickSlotButton()
{
	UE_LOG(LogTemp, Display, TEXT("Clicked item"));
	if (!bCombining)
	{
		UE_LOG(LogTemp, Display, TEXT("show box action"));
		if (PlayerOwner)
		{
			FVector2D MousePos = UWidgetLayoutLibrary::GetMousePositionOnViewport(this);
			UWidgetLayoutLibrary::SlotAsCanvasSlot(PlayerOwner->HUDWD->ActionBoxWD)->SetPosition(MousePos);
			UItemActionBox* ItemActionBoxWD = PlayerOwner->HUDWD->ActionBoxWD;
			ItemActionBoxWD->SetVisibility(ESlateVisibility::Visible);
			ItemActionBoxWD->PopUpWD();
			ItemActionBoxWD->ItemSlotWD = this;
		}
		return;
	}
	CombineItem();
}



void UItemSlot::UseItem()
{
	if (PlayerOwner->ActorNeedItem != nullptr)
	{
		if (ItemData.CompatitionActors.Contains(PlayerOwner->ActorNeedItem))
		{
			PlayerOwner->ActorNeedItem->InteractWithItem(ItemData.InteractivePart);
			ReduceItem();
			RefreshSlot();
		}
	}
}

void UItemSlot::CombineItem()
{
	if (!IsAvailableSpace())
	{
		CombineFailed();
		return;
	}
	TSubclassOf<AInventoryMaster> ClassCombine = PlayerOwner->HUDWD->ActionBoxWD->ItemSlotWD->ItemData.InventoryClass;//never Class = None
	if (ItemData.CombinationClass.Contains(ClassCombine))
	{
		TSubclassOf<AInventoryMaster>* ClassFromCombine = ItemData.CombinationClass.Find(ClassCombine);
		AInventoryMaster* ActorFromCombine = Cast<AInventoryMaster>(GetWorld()->SpawnActor(ClassFromCombine->Get()));

		//Remove 2 items combine if possible
		UItemSlot* MainItemSlot = PlayerOwner->HUDWD->ActionBoxWD->ItemSlotWD;
		MainItemSlot->ReduceItem();
		if (MainItemSlot->ItemData.bInfiniteUse) ReduceItem();
		else {
			if (IndexSlot > MainItemSlot->IndexSlot)
			{
				PlayerOwner->PickedItems.RemoveAt(IndexSlot - 1);
			}
			else PlayerOwner->PickedItems.RemoveAt(IndexSlot);
		}
		//Pick Item from combine
		ActorFromCombine->PickUpItem();		
		RefreshSlot();
		//combine finished
		CombineFailed();
	}
	else CombineFailed();
}



void UItemSlot::CombineFailed()
{
	TArray<UWidget*> WDsInScrollBox = PlayerOwner->HUDWD->InventoryUIWD->ItemScrollBox->GetAllChildren();
	for (UWidget* WidgetChild : WDsInScrollBox)
	{
		UItemSlot* WDSlotItem= Cast<UItemSlot>(WidgetChild);
		if(WDSlotItem) WDSlotItem->bCombining = false;
		UE_LOG(LogTemp, Display, TEXT("Combining end"));
	}
}

bool UItemSlot::IsAvailableSpace()
{
	if (PlayerOwner->SizeInventory > PlayerOwner->PickedItems.Num()) return true;
	FInventoryStruct ItemCombineData = PlayerOwner->HUDWD->ActionBoxWD->ItemSlotWD->ItemData;
	if (!ItemData.bInfiniteUse)
	{
		return ItemData.NumberUses > 2;
	}
	if (!ItemCombineData.bInfiniteUse)
	{
		return ItemCombineData.NumberUses > 2;
	}
	return false;
}

void UItemSlot::ReduceItem()
{
	if (ItemData.bInfiniteUse) return;
	uint8 Number = PlayerOwner->PickedItems[IndexSlot].NumberUses -= 1;
	if (Number < 1) PlayerOwner->PickedItems.RemoveAt(IndexSlot);
}

void UItemSlot::RefreshSlot()
{
	//refresh state visual
	PlayerOwner->HUDWD->RemoveFromViewport();
	FTimerHandle TH_VisibleHUDWD;
	GetWorld()->GetTimerManager().SetTimer(TH_VisibleHUDWD, this, &UItemSlot::AddHUDWDtoViewPort, 0.04, false);
}

void UItemSlot::AddHUDWDtoViewPort()
{
	PlayerOwner->HUDWD->AddToViewport();
	PlayerOwner->HUDWD->ActionBoxWD->SetVisibility(ESlateVisibility::Hidden);
}