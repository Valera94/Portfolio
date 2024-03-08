// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "PortfolioPlayerController.h"
#include "GameFramework/Character.h"
#include "Logging/LogMacros.h"
#include "Portfolio/Input/InputConfigData.h"
#include "PortfolioCharacter.generated.h"

class USpringArmComponent;
class UCameraComponent;
class UInputMappingContext;
class UInputAction;
struct FInputActionValue;

DECLARE_LOG_CATEGORY_EXTERN(LogTemplateCharacter, Log, All);

UCLASS(Abstract)
class APortfolioCharacter : public ACharacter
{
	GENERATED_BODY()

protected:

	/** Camera boom positioning the camera behind the character */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<USpringArmComponent> CameraBoom;

	/** Follow camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UCameraComponent> FollowCamera;

public:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<USkeletalMesh> SkeletalMesh;

#pragma region /* *Input System */

protected:


	UPROPERTY(BlueprintReadOnly)
	APortfolioPlayerController* PortfolioPlayerController;

	/** Called for movement input */
	void MoveWASD(const FInputActionValue& Value);

	/** Called for looking input */
	void Look(const FInputActionValue& Value);

	void IA_RightClick(const FInputActionValue& Value);

#pragma endregion

protected:
	APortfolioCharacter();

public:
	UFUNCTION(Server, Reliable)
	void Server_ChangeMesh(USkeletalMesh* NewSkeletalMesh);
	UFUNCTION(NetMulticast, Reliable)
	void NetMulticast_ChangeMesh(USkeletalMesh* NewSkeletalMesh);

protected:
	// APawn interface
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	virtual void BeginPlay() override;

	virtual void PossessedBy(AController* NewController) override;

public:
	/** Returns CameraBoom subobject **/
	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }
	/** Returns FollowCamera subobject **/
	FORCEINLINE class UCameraComponent* GetFollowCamera() const { return FollowCamera; }
};

