// Fill out your copyright notice in the Description page of Project Settings.

#include "JeninCharacter.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "JeninPlayerController.h"
#include "Actors/JeninBuilding.h"
#include "Actors/JeninResidentActor.h"
#include "Core/JeninGameState.h"
#include "GameFramework/GameSession.h"
#include "GameFramework/GameStateBase.h"
#include "Kismet/KismetMathLibrary.h"

AJeninCharacter::AJeninCharacter()
{
	PrimaryActorTick.bCanEverTick = true;

	this->CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	this->CameraBoom->SetupAttachment(this->GetMesh());

	this->Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	this->Camera->SetupAttachment(this->CameraBoom);

	IsSpawning = false;

	IsMarqueeSelecting = false;
	
	FireRate = 0.25f;
	IsFiringWeapon = false;

	static ConstructorHelpers::FClassFinder<APawn> BPFinder(TEXT("Blueprint'/Game/App/Actors/BP_JeninResidentActor.BP_JeninResidentActor_C'"));
	if (BPFinder.Class != nullptr)
	{
		ResidentBPClass = BPFinder.Class; 
	}

	static ConstructorHelpers::FClassFinder<APawn> BPFinder2(TEXT("Blueprint'/Game/App/Actors/BP_JeninBuildingActor.BP_JeninBuildingActor_C'"));
	if (BPFinder2.Class != nullptr)
	{
		BuildingBPClass = BPFinder2.Class; 
	}

}



void AJeninCharacter::BeginPlay()
{
	Super::BeginPlay();

	//GetPlayerState()

	JeninGameState = Cast<AJeninGameState>(GetWorld()->GetGameState());
	JeninPlayerState = Cast<AJeninPlayerState>(GetPlayerState());

	
	if (APlayerController* PlayerController = Cast<APlayerController>(Controller))
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(InputContext,0);
		}
	}
	
	
	
}


void AJeninCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

	// @TODO: Fix movement so that it starts off slower and speeds up
	// @TODO: Fix movement so that it Ends faster then speeds down
	// @TODO: Fix movement so that isn't as fast if both forward and lateral are pressed simultaneously 
	// @TODO: Set server vs listen-server movement 

void AJeninCharacter::RotateTriggered(const FInputActionValue& Value)
{
	const FVector2D RotationVector = Value.Get<FVector2D>();
	if (Controller != nullptr)
	{
		const float TurnAmount = RotationVector.X * 3.0f;
		AddControllerYawInput(TurnAmount);
	}
}

void AJeninCharacter::ZoomTriggered(const FInputActionValue& Value)
{
	const float ZoomFloat = Value.Get<float>();
	if (Controller != nullptr && CameraBoom != nullptr)
	{
		float NewArmLength = CameraBoom->TargetArmLength + (ZoomFloat * -40.0f);
		NewArmLength = FMath::Clamp(NewArmLength, 100.0f, 10000.0f); 

		CameraBoom->TargetArmLength = NewArmLength;
	}
}

void AJeninCharacter::MouseLeftClickTriggered(const FInputActionValue& Value)
{
	if (AJeninPlayerController* PlayerController = Cast<AJeninPlayerController>(Controller))
	{
		UE_LOG(LogTemp, Warning, TEXT("Hello"));
		PlayerController->IsMouseTriggered = true;
	}
}

void AJeninCharacter::MouseLeftClickOngoing(const FInputActionValue& Value)
{
	if (AJeninPlayerController* PlayerController = Cast<AJeninPlayerController>(Controller))
	{
		PlayerController->IsMouseTriggered = false;
		PlayerController->IsMouseHeld = true;


		
	}
}

void AJeninCharacter::MouseLeftClickCompleted(const FInputActionValue& Value)
{
	if (AJeninPlayerController* PlayerController = Cast<AJeninPlayerController>(Controller))
	{
		//PlayerController->IsMouseTriggered = false;
		//PlayerController->IsMouseHeld = false;

		PlayerController->IsMouseReleased = true;
	}
	UE_LOG(LogTemp, Warning, TEXT("Released"));
}

void AJeninCharacter::SpawnTriggered(const FInputActionValue& Value)
{
	//AJeninGameState* CurrentGameState = GetWorld()->GetGameState<AJeninGameState>();
	//AJeninResidentActor* NewActor = GetWorld()->SpawnActor<AJeninResidentActor>(AJeninResidentActor::StaticClass()); // Default spawn parameters

	//FTransform SpawnTransform = {};

	FireRate = 1.0f;
	if (!IsSpawning)
	{
		IsSpawning = true;
		UWorld* World = GetWorld();
		World->GetTimerManager().SetTimer(FiringTimer, this, &AJeninCharacter::StopSpawn, FireRate, false);
		SpawnResident(GetActorLocation());
	}
	//CanSpawn = false;
            
	//FVector SpawnLocation = {};
	//SpawnLocation = this->GetActorLocation();
	//SpawnLocation.Z += 130.0f;
	//SpawnTransform.SetLocation(SpawnLocation);
	//CurrentGameState->Server_SpawnActor_Implementation(NewActor, SpawnTransform);
	//CanSpawn = false;
}



void AJeninCharacter::StopSpawn()
{
	IsSpawning = false;
}

void AJeninCharacter::SpawnCompleted(const FInputActionValue& Value)
{
	//CanSpawn = true; 
}

void AJeninCharacter::SpawnBuilding_Implementation(int32 ResidentSpawnCount)
{
	FVector spawnLocation = GetActorLocation() + ( GetActorRotation().Vector()  * 100.0f ) + (GetActorUpVector() * 50.0f);
	FRotator spawnRotation = GetActorRotation();

	FActorSpawnParameters spawnParameters;
	spawnParameters.Instigator = GetInstigator();
	spawnParameters.Owner = this;
	
	//AJeninResidentActor* spawnedProjectile = GetWorld()->SpawnActor<AJeninResidentActor>(spawnLocation, spawnRotation, spawnParameters);

	if (BuildingBPClass)
	{
		AJeninBuilding* SpawnedBuilding = GetWorld()->SpawnActor<AJeninBuilding>(BuildingBPClass, spawnLocation, spawnRotation);
		//JeninPlayerState->Units.Add(SpawnedActor)						

		if (SpawnedBuilding) 
		{
			SpawnedBuilding->SetOwner(this);

			// After Spawn, set bottom of building to ground
			FHitResult HitResult = {};
			FVector StartLocation = SpawnedBuilding->GetActorLocation();
			FVector EndLocation = StartLocation + FVector(0,0,-1000);

			// @TODO: Check to see if Can Spawn at location Such as if it overlaps something.
			
			GetWorld()->LineTraceSingleByChannel(HitResult, StartLocation, EndLocation, ECC_WorldStatic);
			if (HitResult.GetActor()->ActorHasTag("Ground") && HitResult.bBlockingHit)
			{
				FVector GroundLocation = HitResult.Location;
				GroundLocation.Z += 5.0f;
				SpawnedBuilding->SetActorLocation(GroundLocation);
			}
			
			for (int i =0; i < ResidentSpawnCount; i++)
			{
				SpawnResident(SpawnedBuilding->GetActorLocation()); 
			}
		}
	}
}

void AJeninCharacter::SpawnResident_Implementation(FVector SpawnLocation)
{
	//FVector spawnLocation = GetActorLocation() + ( GetActorRotation().Vector()  * 100.0f ) + (GetActorUpVector() * 50.0f);
	FRotator SpawnRotation = GetActorRotation();

	FVector SpawnCenter = SpawnLocation;
	float SpawnRadius = 600.0f;

	FVector RandomOffset = FVector::ZeroVector;
	bool bFoundValidSpawn = false;
	int32 MaxAttempts = 10;

	for (int i = 0; i < MaxAttempts; i++)
	{
		// @TODO: Create logic to attempt spawn 
		// @TODO: Create logic to use size of init building for spawn minimum
		// @TODO: Create logic to set a min and max radius for spawn location

		//if (!GetWorld()->OverLapAnyTestByChannel(PotentialSpawnLocation, FQuat::Identity, ECC_WorldStatic, FCollisionShape::Ha)
		
	}

	RandomOffset.X = FMath::RandPointInCircle(SpawnRadius).X;
	RandomOffset.Y = FMath::RandPointInCircle(SpawnRadius).Y;
	SpawnLocation = SpawnCenter + RandomOffset;

	
	
	FActorSpawnParameters spawnParameters;
	spawnParameters.Instigator = GetInstigator();
	spawnParameters.Owner = this;

	
	//AJeninResidentActor* spawnedProjectile = GetWorld()->SpawnActor<AJeninResidentActor>(spawnLocation, spawnRotation, spawnParameters);

	if (ResidentBPClass)
	{
		AJeninResidentActor* SpawnedResident = GetWorld()->SpawnActor<AJeninResidentActor>(ResidentBPClass, SpawnLocation, SpawnRotation);
		//JeninPlayerState->Units.Add(SpawnedActor);

		

		if (SpawnedResident) 
		{
			SpawnedResident->SetOwner(this);

			UE_LOG(LogTemp, Warning, TEXT("Hello"));
		}
	}
}


void AJeninCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent))
	{
		EnhancedInputComponent->BindAction(this->MoveAction, ETriggerEvent::Triggered, this, &AJeninCharacter::MoveTriggered);
		//EnhancedInputComponent->BindAction(this->MoveLateralAction, ETriggerEvent::Triggered, this, &AJeninCharacter::MoveLateralTriggered);
		EnhancedInputComponent->BindAction(this->RotateAction, ETriggerEvent::Triggered, this, &AJeninCharacter::RotateTriggered);
		EnhancedInputComponent->BindAction(this->ZoomAction, ETriggerEvent::Triggered, this, &AJeninCharacter::ZoomTriggered);

		EnhancedInputComponent->BindAction(this->MouseLeftClickAction, ETriggerEvent::Started, this, &AJeninCharacter::MouseLeftClickTriggered);
		EnhancedInputComponent->BindAction(this->MouseLeftClickAction, ETriggerEvent::Ongoing, this, &AJeninCharacter::MouseLeftClickOngoing);
		EnhancedInputComponent->BindAction(this->MouseLeftClickAction, ETriggerEvent::Completed, this, &AJeninCharacter::MouseLeftClickCompleted);
		
		EnhancedInputComponent->BindAction(this->SpawnAction, ETriggerEvent::Triggered, this, &AJeninCharacter::SpawnTriggered);
		//EnhancedInputComponent->BindAction(this->SpawnAction, ETriggerEvent::Completed, this, &AJeninCharacter::SpawnCompleted);
		//EnhancedInputComponent->BindAction(this->MouseLeftClickAction, ETriggerEvent::Triggered, this, &AJeninCharacter::MouseLeftClickTriggered)
	}
}

void AJeninCharacter::PlayerInit(const FVector PlayerSpawnLocation)
{
	
	SetActorLocation(PlayerSpawnLocation);
	UE_LOG(LogTemp, Warning, TEXT("Hello"));

	if (JeninGameState->InDev)
	{
		SpawnBuilding(4);

		
	}
	
}

void AJeninCharacter::MoveTriggered(const FInputActionValue& Value)
{
	const FVector2D MovementVector = Value.Get<FVector2D>();
	if (Controller != nullptr)
	{
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
		const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

		AddMovementInput(ForwardDirection, MovementVector.Y);
		AddMovementInput(RightDirection, MovementVector.X);
	}
}

void AJeninCharacter::Server_MoveForward_Implementation(float ForwardMovementFloat)
{
	UE_LOG(LogTemp, Warning, TEXT("Hello"));
}


