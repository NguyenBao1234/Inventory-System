// Fill out your copyright notice in the Description page of Project Settings.


#include "ActorNeedItem.h"
#include "TPSGameCPP/ShooterCharacter.h"

AActorNeedItem::AActorNeedItem()
{
}


void AActorNeedItem::OnInteract()
{
	if (bUnlock) OnInteractBP();
}

void AActorNeedItem::SetUpOverlap(bool bOverlapped)
{
	SetUpOverlap_iBP(bOverlapped);
	if (bOverlapped) PlayerChar->ActorNeedItem = this;
	else PlayerChar->ActorNeedItem = nullptr;
}
