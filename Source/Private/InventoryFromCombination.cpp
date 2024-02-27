// Fill out your copyright notice in the Description page of Project Settings.

#include "InventoryFromCombination.h"
#include "TPSGameCPP/ShooterCharacter.h"
#include"ActorNeedItem.h"
#include<Kismet/GameplayStatics.h>


void AInventoryFromCombination::PickUpItem()
{
	if (!ClassActorNeedItem)
	{
		UE_LOG(LogTemp, Warning, TEXT("Item hasn't contained Class ActorNeedItem"));return;
	}
	TArray<AActor*> ActorsNeedItem;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ClassActorNeedItem, ActorsNeedItem);
	for (AActor* ActorElement : ActorsNeedItem)
	{
		AActorNeedItem* ActorNeedItem = Cast<AActorNeedItem>(ActorElement);
		if (!ActorNeedItem->bUnlock) ItemProperty.CompatitionActors.Add(ActorNeedItem);
	}
	UE_LOG(LogTemp, Warning, TEXT("Item: added ActorNeedItem to TSet"));
	PlayerChar->PickedItems.Add(ItemProperty);
	Destroy();
}
