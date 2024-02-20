// Fill out your copyright notice in the Description page of Project Settings.


#include "JeninGameMode.h"

#include "Characters/JeninCharacter.h"


AJeninGameMode::AJeninGameMode()
{

	playerCount = 0;
}

void AJeninGameMode::BeginPlay()
{
	
	Super::BeginPlay();


	

	
	for (FConstPlayerControllerIterator Iterator = GetWorld()->GetPlayerControllerIterator(); Iterator; ++Iterator)
	{
		AllPlayerControllers.Add(Iterator->Get());
		
	}

	for (APlayerController* Controller : AllPlayerControllers)
	{
		// set location
		
	}
	


	
}

void AJeninGameMode::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	
}

void AJeninGameMode::PostLogin(APlayerController* NewPlayer)
{
	Super::PostLogin(NewPlayer);
	  
	
	AJeninCharacter* chara = Cast<AJeninCharacter>(NewPlayer->GetCharacter());
	if (chara)
	{
		chara->SetActorLocation(SpawnLocations[playerCount]);
		playerCount++;
	}
	
		
}
