// Fill out your copyright notice in the Description page of Project Settings.


#include "Widget/Inventory/InventoryUI.h"
#include <Components/ScrollBox.h>

bool UInventoryUI::Initialize()
{
    if (!Super::Initialize()) return false;
    if (!ensure(ItemScrollBox != nullptr)) return false;
    return true;
}

void UInventoryUI::NativeConstruct()
{
    Super::NativeConstruct();
    UE_LOG(LogTemp, Display, TEXT("InventoryUI has Constructed"));
}
