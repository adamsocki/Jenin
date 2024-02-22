// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Actors/JeninResidentActor.h"
#include "GameFramework/PlayerState.h"
#include "JeninPlayerState.generated.h"

/**
 * 
 */
UCLASS()
class JENIN_API AJeninPlayerState : public APlayerState
{
	GENERATED_BODY()


	AJeninPlayerState();

protected:
	virtual void BeginPlay() override;

public:
	bool InPlay;
	bool ResidentMovementMode;
	
	TArray<AActor*> Buildings;
	TArray<AJeninResidentActor*> Units;

	TArray<AJeninResidentActor*> SelectedUnits;
};
