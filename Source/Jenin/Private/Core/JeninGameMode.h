// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Characters/JeninPlayerController.h"
#include "GameFramework/GameModeBase.h"
#include "JeninGameMode.generated.h"


UCLASS()
class JENIN_API AJeninGameMode : public AGameModeBase
{
	GENERATED_BODY()

	AJeninGameMode();

	
public:
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Game | Dev Settings")
	bool DevelopmentMode;

	virtual void BeginPlay() override;

	virtual void PostLogin(APlayerController* NewPlayer) override;

	UPROPERTY()
	TArray<APlayerController*> AllPlayerControllers;
	int32 playerCount;

	UPROPERTY(EditAnywhere)
	TArray<FVector> SpawnLocations;
};



