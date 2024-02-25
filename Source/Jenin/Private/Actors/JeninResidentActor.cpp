// Fill out your copyright notice in the Description page of Project Settings.

#include "JeninResidentActor.h"

#include "Blueprint/UserWidget.h"
#include "Components/DecalComponent.h"
#include "UI/JeninMarqueeHUD.h"


void AJeninResidentActor::Server_MoveToDestination_Implementation(FVector destination, float DeltaTime)
{
	//this->SetActorLocation(TransitDestination);

	//MoveToDestination(TransitDestination);

	UE_LOG(LogTemp, Warning, TEXT("MoveResident"));
	UE_LOG(LogTemp, Warning, TEXT("server resident Location: %s"), *destination.ToString());

	FVector DesiredDirection = (destination - GetActorLocation()).GetSafeNormal();
		
	FVector NewVelocity = DesiredDirection * 300.0f;
		
	FVector NewPosition = GetActorLocation() + NewVelocity * DeltaTime;
	SetActorLocation(NewPosition);
}


void AJeninResidentActor::OnSelected()
{
	AJeninMarqueeHUD* MarqueeHUD = Cast<AJeninMarqueeHUD>(GetWorld()->GetFirstPlayerController()->GetHUD());
	if (MarqueeHUD)
	{

		MyUnitWidget = CreateWidget<UJeninUnitWidget>(GetWorld(), UnitWidget);
		MarqueeHUD->OnUnitSelected(MyUnitWidget); 
	}
}

void AJeninResidentActor::OnDeselected()
{
	// TODO @ MOVE ALL Selection logid to this interface logic
	AJeninMarqueeHUD* MarqueeHUD = Cast<AJeninMarqueeHUD>(GetWorld()->GetFirstPlayerController()->GetHUD());
	if (MarqueeHUD)
	{
		MarqueeHUD->OnUnitDeselected(MyUnitWidget); 
	}
}

// Sets default values
AJeninResidentActor::AJeninResidentActor()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// CapsuleCollider = CreateDefaultSubobject<UCapsuleComponent>(TEXT("CapsuleCollider"));
	// RootComponent = CapsuleCollider;
	//
	// // ResidentStaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ResidentMeshComponent"));
	// // ResidentStaticMesh->SetupAttachment(CapsuleCollider);


	// SelectionDecal = CreateDefaultSubobject<UDecalComponent>(TEXT("SelectionDecal"));
	//
	// SelectionDecal->SetupAttachment(RootComponent);
	// Load the Static Mesh Asset
	// static ConstructorHelpers::FObjectFinder<UStaticMesh> MeshAsset(TEXT("StaticMesh'/Game/StarterContent/Shapes/Shape_Pipe_180.Shape_Pipe_180'"));
	// if (MeshAsset.Succeeded())
	// {
	// 	ResidentStaticMesh->SetStaticMesh(MeshAsset.Object);
	// }
	// else
	// {
	// 	// Optional: Handle the case where the mesh was not found
	// }
	
	bReplicates = true;
	IsSelected = false;
	Tags.AddUnique(FName("Selectable"));
	Tags.AddUnique(FName("Unit"));
	MoveResident = false;
	MoveDestination = {};
	
}


void AJeninResidentActor::MoveToDestination(FVector transitDestination)
{

	FVector WorldDirection = (transitDestination - GetActorLocation()).GetSafeNormal();
	transitDestination.Z += 133.9f;
	//UE_LOG(LogTemp, Warning, TEXT("transitDestination Location: %s"), *transitDestination.ToString());
	this->SetActorLocation(transitDestination);
	//this->AddMovementInput(WorldDirection, 1.0, false);
	UE_LOG(LogTemp, Warning, TEXT("movkement"));
}

// Called when the game starts or when spawned
void AJeninResidentActor::BeginPlay()
{
	Super::BeginPlay();
	if (UnitWidget)
	{
		MyUnitWidget = CreateWidget<UJeninUnitWidget>(GetWorld(), UnitWidget);
		MyUnitWidget->ActorReference = this;
		//MyUnitWidget->UnitImageWidget
		if (UnitImage)
		{
			MyUnitWidget->UnitImageWidget->SetBrushFromTexture(UnitImage);

		}
	}
}

// Called every frame
void AJeninResidentActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	if (MoveResident)
	{		
		UE_LOG(LogTemp, Warning, TEXT("Tick resident Location: %s"), *MoveDestination.ToString());
		Server_MoveToDestination(MoveDestination, DeltaTime);
	}
}

void AJeninResidentActor::MoveTo(FVector loc)
{
	UE_LOG(LogTemp, Warning, TEXT("arstarstarst: %s"), *loc.ToString());
	this->SetActorLocation(loc);

	//Server_MoveToDestination(loc);
}



