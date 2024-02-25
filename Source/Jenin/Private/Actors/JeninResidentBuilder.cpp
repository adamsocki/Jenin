// Fill out your copyright notice in the Description page of Project Settings.


#include "JeninResidentBuilder.h"


// Sets default values
AJeninResidentBuilder::AJeninResidentBuilder()
{
	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void AJeninResidentBuilder::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AJeninResidentBuilder::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// Called to bind functionality to input
void AJeninResidentBuilder::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

