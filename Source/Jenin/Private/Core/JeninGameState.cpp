// Fill out your copyright notice in the Description page of Project Settings.


#include "JeninGameState.h"

#include "Actors/JeninResidentActor.h"


AJeninGameState::AJeninGameState()
{
	
	CharacterIDMap = {};
	CharacterID_Values = 0;
}

void AJeninGameState::Server_CreateCharacter_Implementation(ACharacter* NewCharacter)
{
	if (NewCharacter)
	{
		const int32 NewID = GenerateUniqueCharacterID();
		CharacterIDMap.Add(NewID, NewCharacter);
	}
}

int32 AJeninGameState::GenerateUniqueCharacterID()
{
	CharacterID_Values++;
	return CharacterID_Values;
}


