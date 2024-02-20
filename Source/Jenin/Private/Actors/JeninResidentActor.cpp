// Fill out your copyright notice in the Description page of Project Settings.


#include "JeninResidentActor.h"


// Sets default values
AJeninResidentActor::AJeninResidentActor()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	CapsuleCollider = CreateDefaultSubobject<UCapsuleComponent>(TEXT("CapsuleCollider"));
	RootComponent = CapsuleCollider;
	
	ResidentStaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ResidentMeshComponent"));
	ResidentStaticMesh->SetupAttachment(CapsuleCollider);

	// Load the Static Mesh Asset
	static ConstructorHelpers::FObjectFinder<UStaticMesh> MeshAsset(TEXT("StaticMesh'/Game/StarterContent/Shapes/Shape_Pipe_180.Shape_Pipe_180'"));
	if (MeshAsset.Succeeded())
	{
		ResidentStaticMesh->SetStaticMesh(MeshAsset.Object);
	}
	else
	{
		// Optional: Handle the case where the mesh was not found
	}

	//MovementComponent = CreateDefaultSubobject<UCharacterMovementComponent>(TEXT("MovementComponent")); 
 
	bReplicates = true;
	IsSelected = false;
	Tags.AddUnique(FName("Selectable"));  
}

// Called when the game starts or when spawned
void AJeninResidentActor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AJeninResidentActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

