// Fill out your copyright notice in the Description page of Project Settings.

#include"TPSGameCPP/ShooterCharacter.h"
#include "InventoryActor.h"

AInventoryActor::AInventoryActor()
{
	ItemProperty.InventoryClass = this->GetClass();
}

void AInventoryActor::PickUpItem()
{
	if (PlayerChar)
	{
		UE_LOG(LogTemp, Warning, TEXT("Inventory picked"));
		PlayerChar->PickedItems.Add(ItemProperty);
		Destroy();
	}
}
