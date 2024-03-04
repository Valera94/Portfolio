// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Portfolio/Player/PortfolioCharacterAbility.h"
#include "Class_Rogue.generated.h"

UCLASS(Abstract)
class PORTFOLIO_API AClass_Rogue : public APortfolioCharacterAbility
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AClass_Rogue();

	UPROPERTY()
	TObjectPtr<const class UAttribute_Energy> Energy;
};
