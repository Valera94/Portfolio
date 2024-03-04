// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Portfolio/Player/PortfolioCharacterAbility.h"
#include "Class_Warrior.generated.h"

UCLASS(Abstract)
class PORTFOLIO_API AClass_Warrior : public APortfolioCharacterAbility
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AClass_Warrior();

	UPROPERTY()
	TObjectPtr<const class UAttributeSet_Rage> Rage;
};
