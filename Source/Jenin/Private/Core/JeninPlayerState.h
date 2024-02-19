// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
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

public:
	bool InPlay;
};
