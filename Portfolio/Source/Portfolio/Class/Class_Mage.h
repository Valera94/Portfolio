// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Portfolio/Player/PortfolioCharacterAbility.h"
#include "Class_Mage.generated.h"

UCLASS(Abstract)
class PORTFOLIO_API AClass_Mage : public APortfolioCharacterAbility
{
	GENERATED_BODY()

public:

	// Sets default values for this character's properties
	AClass_Mage();

	virtual void PossessedBy(AController* NewController) override;
	UPROPERTY()
	TObjectPtr<const class UAttribute_Mana> Mana;
};
