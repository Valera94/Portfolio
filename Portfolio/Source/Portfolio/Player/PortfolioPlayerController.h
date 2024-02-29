// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "PortfolioPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class PORTFOLIO_API APortfolioPlayerController : public APlayerController
{
	GENERATED_BODY()


public:
	virtual void BeginPlay() override;

	//Press icon ability
	virtual bool InputKey(const FInputKeyParams& Params) override;
	//OldPressedKey icon ability
	FString OldPressKey;
};
