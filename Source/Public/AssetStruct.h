// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AssetStruct.generated.h"

/**
 * 
 */
USTRUCT(BlueprintType)
struct TPSGAMECPP_API FAssetStruct
{
public:
	GENERATED_BODY()

	UPROPERTY(BlueprintReadWrite)
		FText AssetName;
	UPROPERTY(BlueprintReadWrite)
		bool Bool1;
	UPROPERTY(BlueprintReadWrite)
		bool Bool2;
	UPROPERTY(BlueprintReadWrite)
		bool Bool3;

	FAssetStruct();
	~FAssetStruct();
};
