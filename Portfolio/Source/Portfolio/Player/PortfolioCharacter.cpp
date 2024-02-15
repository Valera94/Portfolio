// Copyright Epic Games, Inc. All Rights Reserved.

#include "PortfolioCharacter.h"
#include "Engine/LocalPlayer.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/Controller.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputActionValue.h"
#include "Engine/AssetManager.h"
#include "Engine/StreamableManager.h"
#include "GameFramework/GameModeBase.h"
#include "Kismet/GameplayStatics.h"


DEFINE_LOG_CATEGORY(LogTemplateCharacter);

//////////////////////////////////////////////////////////////////////////
// APortfolioCharacter

APortfolioCharacter::APortfolioCharacter()
{

	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);

	// Don't rotate when the controller rotates. Let that just affect the camera.
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	// Configure character movement
	GetCharacterMovement()->bOrientRotationToMovement = true; // Character moves in the direction of input...	
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 500.0f, 0.0f); // ...at this rotation rate

	// Note: For faster iteration times these variables, and many more, can be tweaked in the Character Blueprint
	// instead of recompiling to adjust them
	GetCharacterMovement()->JumpZVelocity = 700.f;
	GetCharacterMovement()->AirControl = 0.35f;
	GetCharacterMovement()->MaxWalkSpeed = 500.f;
	GetCharacterMovement()->MinAnalogWalkSpeed = 20.f;
	GetCharacterMovement()->BrakingDecelerationWalking = 2000.f;
	GetCharacterMovement()->BrakingDecelerationFalling = 1500.0f;

	// Create a camera boom (pulls in towards the player if there is a collision)
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->TargetArmLength = 400.0f; // The camera follows at this distance behind the character	
	CameraBoom->bUsePawnControlRotation = true; // Rotate the arm based on the controller

	// Create a follow camera
	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName); // Attach the camera to the end of the boom and let the boom adjust to match the controller orientation
	FollowCamera->bUsePawnControlRotation = false; // Camera does not rotate relative to arm

	// Note: The skeletal mesh and anim blueprint references on the Mesh component (inherited from Character) 
	// are set in the derived blueprint asset named ThirdPersonCharacter (to avoid direct content references in C++)
}

void APortfolioCharacter::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);


}



void APortfolioCharacter::BeginPlay()
{
	// Call the base class  
	Super::BeginPlay();

}


void APortfolioCharacter::Server_ChangeMesh_Implementation(USkeletalMesh* NewSkeletalMesh)
{
	NetMulticast_ChangeMesh(NewSkeletalMesh);
}

void APortfolioCharacter::NetMulticast_ChangeMesh_Implementation(USkeletalMesh* NewSkeletalMesh)
{
	GetMesh()->SetSkeletalMesh(NewSkeletalMesh);
}

#pragma region /* *Input System */


void APortfolioCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	check(InputMappingContext)

		//Add Input Mapping Context
		if (APlayerController* PlayerController = Cast<APlayerController>(Controller))
		{
			if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
			{
				Subsystem->AddMappingContext(InputMappingContext, 0);
			}
		}


	// Set up action bindings
	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent)) {

		// Moving
		EnhancedInputComponent->BindAction(InputConfigData->InputMoveWASD, ETriggerEvent::Triggered, this, &APortfolioCharacter::MoveWASD);

		// Looking
		EnhancedInputComponent->BindAction(InputConfigData->TurnMouse, ETriggerEvent::Triggered, this, &APortfolioCharacter::Look);
	}

}


void APortfolioCharacter::MoveWASD(const FInputActionValue& Value)
{
	// input is a Vector2D
	FVector2D MovementVector = Value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		if (MovementVector != FVector2D::Zero())
		{
			//ChangeStatusInput
			InputConfigData->ChangeStatusInput(EWhatWasPressed::WWP_WASDClick, EClickStatus::CS_Pressed);

			// find out which way is forward
			const FRotator Rotation = Controller->GetControlRotation();
			const FRotator YawRotation(0, Rotation.Yaw, 0);

			// get forward vector
			const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X) * InputConfigData->MultiplyScaleLookAxis;

			// get right vector 
			const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y) * InputConfigData->MultiplyScaleLookAxis;

			// add movement 
			AddMovementInput(ForwardDirection, MovementVector.Y);
			AddMovementInput(RightDirection, MovementVector.X);
		}
		else
		{
			//ChangeStatusInput
			InputConfigData->ChangeStatusInput(EWhatWasPressed::WWP_WASDClick, EClickStatus::CS_UnPressed);
		}
	}
}

void APortfolioCharacter::Look(const FInputActionValue& Value)
{
	// input is a Vector2D
	FVector2D LookAxisVector = Value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		if (LookAxisVector != FVector2D::Zero())
		{

			//ChangeStatusInput
			InputConfigData->ChangeStatusInput(EWhatWasPressed::WWP_TurnMouse, EClickStatus::CS_Pressed);

			// add yaw and pitch input to controller
			AddControllerYawInput(LookAxisVector.X * InputConfigData->MultiplyScaleLookAxis);
			AddControllerPitchInput(LookAxisVector.Y * InputConfigData->MultiplyScaleLookAxis * -1);
		}
		else
		{
			//ChangeStatusInput
			InputConfigData->ChangeStatusInput(EWhatWasPressed::WWP_TurnMouse, EClickStatus::CS_UnPressed);
		}
	}
}

#pragma endregion