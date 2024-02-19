// Fill out your copyright notice in the Description page of Project Settings.


#include "JeninBuilding.h"


// Sets default values
AJeninBuilding::AJeninBuilding()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	BuildingStaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ResidentMeshComponent"));
	BuildingStaticMesh->SetupAttachment(RootComponent);

	// Load the Static Mesh Asset
	static ConstructorHelpers::FObjectFinder<UStaticMesh> MeshAsset(TEXT("StaticMesh'/Game/StarterContent/Shapes/Shape_Pipe_180.Shape_Pipe_180'"));
	if (MeshAsset.Succeeded())
	{
		BuildingStaticMesh->SetStaticMesh(MeshAsset.Object);
	}

	
	
	bReplicates = true;
	IsSelected = false;

	Tags.AddUnique(FName("Selectable"));  


	
}

// Called when the game starts or when spawned
void AJeninBuilding::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AJeninBuilding::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

