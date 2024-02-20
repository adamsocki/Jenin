// Fill out your copyright notice in the Description page of Project Settings.

#include "JeninCharacter.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "JeninPlayerController.h"
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

	static ConstructorHelpers::FClassFinder<AActor> BPFinder(TEXT("Blueprint'/Game/App/Actors/BP_JeninResidentActor.BP_JeninResidentActor_C'"));
	if (BPFinder.Class != nullptr)
	{
		ResidentBPClass = BPFinder.Class; 
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

	
	AActor* owner = GetOwner();
	
	if(owner)
	{
		UE_LOG(LogTemp, Warning, TEXT("The Actor's name is %s"), *owner->GetName());
		
		//Create Default Unit & Building Setup
		FVector spawnLocation = owner->GetActorLocation() + ( owner->GetActorRotation().Vector()  * 100.0f ) + (owner->GetActorUpVector() * 50.0f);
		FRotator spawnRotation = owner->GetActorRotation();
		
		FActorSpawnParameters spawnParameters;
		spawnParameters.Instigator = GetInstigator();
		spawnParameters.Owner = this;
		
		//AJeninResidentActor* spawnedProjectile = GetWorld()->SpawnActor<AJeninResidentActor>(spawnLocation, spawnRotation, spawnParameters);

		
		if (ResidentBPClass && JeninGameState->InDev)
		{
			SpawnResident();
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
		SpawnResident();
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

void AJeninCharacter::SpawnResident_Implementation()
{
	FVector spawnLocation = GetActorLocation() + ( GetActorRotation().Vector()  * 100.0f ) + (GetActorUpVector() * 50.0f);
	FRotator spawnRotation = GetActorRotation();

	FActorSpawnParameters spawnParameters;
	spawnParameters.Instigator = GetInstigator();
	spawnParameters.Owner = this;
	
	//AJeninResidentActor* spawnedProjectile = GetWorld()->SpawnActor<AJeninResidentActor>(spawnLocation, spawnRotation, spawnParameters);

	if (ResidentBPClass)
	{
		AJeninResidentActor* SpawnedActor = GetWorld()->SpawnActor<AJeninResidentActor>(ResidentBPClass, spawnLocation, spawnRotation);
		//JeninPlayerState->Units.Add(SpawnedActor);

		if (SpawnedActor) 
		{
			SpawnedActor->SetOwner(this); 
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


