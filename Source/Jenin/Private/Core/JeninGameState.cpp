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

//void AJeninGameState::Server_SpawnActor_Implementation(AActor* NewActor,  FTransform SpawnTransform)
//{
	//if (NewActor && HasAuthority())
	//{
		//FActorSpawnParameters SpawnParameters;
		//SpawnParameters.Owner = this;
		//SpawnParameters.Instigator = nullptr;		
	//	FRotator Rotation(0.0f, 0.0f, 0.0f);
	//	GetWorld()->SpawnActor<AJeninResidentActor>(SpawnTransform.GetLocation(), Rotation ,SpawnParameters);


		//static ConstructorHelpers::FClassFinder<AActor> BPFinder(TEXT("/Game/App/Actors/BP_JeninResidentActor.BP_JeninResidentActor_C")); 
		//if (BPFinder.Class != nullptr)
		//{
			// 2. Spawn Instance, using the found class
			//FActorSpawnParameters SpawnParams;
			//AActor* SpawnedActor ={};
			//GetWorld()->SpawnActor<AActor>(NewActor, SpawnTransform, SpawnParams);
		//}
	//}
//}

int32 AJeninGameState::GenerateUniqueCharacterID()
{
	CharacterID_Values++;
	return CharacterID_Values;
}


