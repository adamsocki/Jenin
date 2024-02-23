// Fill out your copyright notice in the Description page of Project Settings.


#include "JeninPlayerState.h"

AJeninPlayerState::AJeninPlayerState()
{
	Units = {};
	Buildings = {};
	InPlay = true;
	ResidentMovementMode = false;

	SelectedUnits = {};
	PrimaryActorTick.bCanEverTick = true; 
}

void AJeninPlayerState::BeginPlay()
{
	Super::BeginPlay();
	
}

void AJeninPlayerState::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
	//UE_LOG(LogTemp, Warning, TEXT("The integer value is:"));

	//UE_LOG(LogTemp, Warning, TEXT("The integer value is: %d"), SelectedUnits.Num());

	if (SelectedUnits.Num() > 0)
	{
		//ResidentMovementMode = true;
	}
	else
	{
		//ResidentMovementMode = true;

	}

	
}



