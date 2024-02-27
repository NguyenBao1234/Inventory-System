// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"

#include "Components/WidgetComponent.h"
#include "Components/BoxComponent.h"
#include "InteractActor.generated.h"

UCLASS()
class TPSGAMECPP_API AInteractActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AInteractActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	UPROPERTY(BlueprintReadOnly)
	class AShooterCharacter* PlayerChar;


public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual void OnInteract();
	virtual void SetUpOverlap(bool bOverlapped = true);

	UFUNCTION()
	void OnPlayerOverlap(AActor* OverlappedActor, AActor* OtherActor);
	UFUNCTION()
	void EndPlayerOverlap(AActor* OverlappedActor, AActor* OtherActor);

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		UWidgetComponent* HintWD;
private:
	UPROPERTY(VisibleAnywhere)
		USceneComponent* SceneRoot;
	UPROPERTY(VisibleAnywhere)
		UBoxComponent* BoxTrigger;
	class APlayerController* PlayerController;
};
