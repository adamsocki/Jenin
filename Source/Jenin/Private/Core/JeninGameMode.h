﻿// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "JeninGameMode.generated.h"


UCLASS()
class JENIN_API AJeninGameMode : public AGameModeBase
{
	GENERATED_BODY()


	
public:
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Game | Dev Settings")
	bool DevelopmentMode;
};
