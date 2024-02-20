// Fill out your copyright notice in the Description page of Project Settings.


#include "JeninPlayerController.h"


#include "EnhancedInputComponent.h"
#include "JeninCharacter.h"
#include "Core/JeninPlayerState.h"
#include "UI/JeninMarqueeHUD.h"

AJeninPlayerController::AJeninPlayerController()
{
	IsMouseTriggered = false;
	IsMouseHeld = false;
	//Add Input Mapping Context
	if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer()))
	{
		Subsystem->AddMappingContext(DefaultMappingContext, 0);
	}
}
void AJeninPlayerController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}
void AJeninPlayerController::BeginPlay()
{
	Super::BeginPlay();
	this->bShowMouseCursor = true;
	this->bEnableClickEvents = true; // Allows clicks 
	this->bEnableMouseOverEvents = true; // Allows mouse-over events
	FInputModeGameAndUI InputMode;
	InputMode.SetHideCursorDuringCapture(false);
	this->SetInputMode(InputMode);
}
void AJeninPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(InputComponent))
	{
		// Setup mouse input events
		// EnhancedInputComponent->BindAction(SetDestinationClickAction, ETriggerEvent::Started, this, &AJeninPlayerController::OnInputStarted);
		// EnhancedInputComponent->BindAction(SetDestinationClickAction, ETriggerEvent::Triggered, this, &AJeninPlayerController::OnSetDestinationTriggered);
		// EnhancedInputComponent->BindAction(SetDestinationClickAction, ETriggerEvent::Completed, this, &AJeninPlayerController::OnSetDestinationReleased);
		// EnhancedInputComponent->BindAction(SetDestinationClickAction, ETriggerEvent::Canceled, this, &AJeninPlayerController::OnSetDestinationReleased);
		EnhancedInputComponent->BindAction(this->CameraMoveAction, ETriggerEvent::Triggered, this, &AJeninPlayerController::OnCameraMoveTriggered);
		EnhancedInputComponent->BindAction(this->ZoomAction, ETriggerEvent::Triggered, this, &AJeninPlayerController::OnZoomTriggered);
		EnhancedInputComponent->BindAction(this->RotateAction, ETriggerEvent::Triggered, this, &AJeninPlayerController::OnRotateTriggered);
		
		EnhancedInputComponent->BindAction(this->MouseLeftClickAction, ETriggerEvent::Started, this, &AJeninPlayerController::OnMouseLeftClickStarted);
		EnhancedInputComponent->BindAction(this->MouseLeftClickAction, ETriggerEvent::Triggered, this, &AJeninPlayerController::OnMouseLeftClickTriggered);
		EnhancedInputComponent->BindAction(this->MouseLeftClickAction, ETriggerEvent::Completed, this, &AJeninPlayerController::OnMouseLeftClickCompleted);
		
		EnhancedInputComponent->BindAction(this->SetResidentDestinationClickAction, ETriggerEvent::Triggered, this, &AJeninPlayerController::OnSetResidentDestinationTriggered);
		}
	else
	{
	//	UE_LOG(LogTemplateCharacter, Error, TEXT("'%s' Failed to find an Enhanced Input Component! This template is built to use the Enhanced Input system. If you intend to use the legacy system, then you will need to update this C++ file."), *GetNameSafe(this));
	}
}
void AJeninPlayerController::OnMouseLeftClickStarted(const FInputActionValue& Value)
{
	
	AJeninMarqueeHUD* MarqueeHUD = GetHUD<AJeninMarqueeHUD>();
	if (MarqueeHUD)
	{
		FVector2D MousePosition = {};

		GetMousePosition(MousePosition.X, MousePosition.Y);
		UE_LOG(LogTemp, Warning, TEXT("ControllerMouse Location: %s"), *MousePosition.ToString());

		MarqueeHUD->MarqueePressed(MousePosition);
		UE_LOG(LogTemp, Warning, TEXT("Start"));

	}
}
void AJeninPlayerController::OnMouseLeftClickTriggered(const FInputActionValue& Value)
{
	AJeninMarqueeHUD* MarqueeHUD = GetHUD<AJeninMarqueeHUD>();
	if (MarqueeHUD)
	{
		FVector2D MousePosition = {};
		GetMousePosition(MousePosition.X, MousePosition.Y);
		MarqueeHUD->MarqueeHeld(MousePosition);
	}
}
void AJeninPlayerController::OnMouseLeftClickCompleted(const FInputActionValue& Value)
{
	AJeninMarqueeHUD* MarqueeHUD = GetHUD<AJeninMarqueeHUD>();
	if (MarqueeHUD)
	{
		FVector2D MousePosition = {};
		GetMousePosition(MousePosition.X, MousePosition.Y);
		MarqueeHUD->MarqueeReleased(MousePosition);
	}
}
void AJeninPlayerController::OnSetResidentDestinationTriggered(const FInputActionValue& Value)
{
	if(AJeninPlayerState* JeninPlayerState = GetPlayerState<AJeninPlayerState>())
	{
		if (JeninPlayerState->ResidentMovementMode)
		{
			// @TODO: MOVE RESIDENT LOGIC
		}
	}
}

void AJeninPlayerController::OnCameraMoveTriggered(const FInputActionValue& Value)
{
	const FVector2D MovementVector = Value.Get<FVector2D>();
	APawn* ControlledPawn = GetPawn();
	if (ControlledPawn != nullptr)
	{
		const FRotator Rotation = ControlledPawn->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
		const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

		ControlledPawn->AddMovementInput(ForwardDirection, MovementVector.Y);
		ControlledPawn->AddMovementInput(RightDirection, MovementVector.X);
	}
}

void AJeninPlayerController::OnZoomTriggered(const FInputActionValue& Value)
{
	const float ZoomFloat = Value.Get<float>();
	APawn* ControlledPawn = GetPawn();
	if (AJeninCharacter* JeninCharacter = Cast<AJeninCharacter>(ControlledPawn))
	{
		float NewArmLength = JeninCharacter->CameraBoom->TargetArmLength + (ZoomFloat * -40.0f);
		NewArmLength = FMath::Clamp(NewArmLength, 100.0f, 10000.0f); 
		JeninCharacter->CameraBoom->TargetArmLength = NewArmLength;
	}
}
void AJeninPlayerController::OnRotateTriggered(const FInputActionValue& Value)
{
	const FVector2D RotationVector = Value.Get<FVector2D>();
	APawn* ControlledPawn = GetPawn();
	if (AJeninCharacter* JeninCharacter = Cast<AJeninCharacter>(ControlledPawn))
	{
		const float TurnAmount = RotationVector.X * 3.0f;
		JeninCharacter->AddControllerYawInput(TurnAmount);
	}
}
