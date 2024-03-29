﻿// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameStateBase.h"
#include "JeninGameState.generated.h"

UCLASS()
class JENIN_API AJeninGameState : public AGameStateBase
{
	GENERATED_BODY()
	AJeninGameState();
	
	TMap<int32, ACharacter*> CharacterIDMap;

	
	UFUNCTION(Server, Reliable)
	void Server_CreateCharacter(ACharacter* NewCharacter);

	int32 GenerateUniqueCharacterID();
	int32 CharacterID_Values;

public:
	UPROPERTY(EditAnywhere)
	bool InDev; 

};
