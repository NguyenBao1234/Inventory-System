// Fill out your copyright notice in the Description page of Project Settings.

#include "InventoryMaster.h"


void AInventoryMaster::OnInteract()
{
	PickUpItem();
}

void AInventoryMaster::PickUpItem()
{
	UE_LOG(LogTemp, Display, TEXT("Pick up Master"));
}
