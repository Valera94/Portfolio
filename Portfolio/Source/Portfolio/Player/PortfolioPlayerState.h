// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include <GameplayEffectTypes.h>
#include "GameFramework/PlayerState.h"
#include "PortfolioPlayerState.generated.h"

/**
 *
 */

UENUM()
enum class EAttributeInformation :uint8
{
	Health,
	Mana,
	Energy,
};

UCLASS()
class PORTFOLIO_API APortfolioPlayerState : public APlayerState
{
	GENERATED_BODY()

public:
	
};
