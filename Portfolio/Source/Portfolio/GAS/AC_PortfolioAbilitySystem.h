// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemComponent.h"
#include "AC_PortfolioAbilitySystem.generated.h"

class UBaseGameplayEffect;
class UAttributeSet_General;


/**
 *
 */
UCLASS()
class PORTFOLIO_API UAC_PortfolioAbilitySystem : public UAbilitySystemComponent
{
	GENERATED_BODY()

protected:

	//FORCEINLINE APortfolioPlayerState* GetPlayerState() const { return Cast<APortfolioPlayerState>(AbilityActorInfo.Get()->PlayerController->PlayerState); }

public:

	virtual void BeginPlay() override;

	UPROPERTY(BlueprintReadOnly,Category="Custom|InformationSpawn")
	TArray<TObjectPtr<UAttributeSet_General>>ArrAttribute;
};
