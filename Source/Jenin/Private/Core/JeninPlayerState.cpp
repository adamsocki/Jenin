// Fill out your copyright notice in the Description page of Project Settings.


#include "JeninPlayerState.h"

AJeninPlayerState::AJeninPlayerState()
{
	Units = {};
	Buildings = {};
	InPlay = true;
	ResidentMovementMode = false;

	SelectedUnits = {};
	
}

void AJeninPlayerState::BeginPlay()
{
	Super::BeginPlay();	
}
