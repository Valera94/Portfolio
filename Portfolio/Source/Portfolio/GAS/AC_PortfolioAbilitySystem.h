// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemComponent.h"
#include "Portfolio/Player/PortfolioPlayerState.h"
#include "AC_PortfolioAbilitySystem.generated.h"

/**
 *
 */
UCLASS()
class PORTFOLIO_API UAC_PortfolioAbilitySystem : public UAbilitySystemComponent
{
	GENERATED_BODY()

public:
	UAC_PortfolioAbilitySystem();

	virtual void BeginPlay() override;

	FORCEINLINE APortfolioPlayerState* GetPlayerState() const { return Cast<APortfolioPlayerState>(AbilityActorInfo.Get()->PlayerController->PlayerState); }

	

	
};
