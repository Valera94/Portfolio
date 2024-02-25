// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayEffect.h"
#include "BaseGameplayEffect.generated.h"

/**
 * 
 */

USTRUCT(BlueprintType)
struct FEffectKeyPair
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	FName Id;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FActiveGameplayEffectHandle EffectHandle;

	FEffectKeyPair();

	FEffectKeyPair(FName Id, FActiveGameplayEffectHandle Handle);

};


UCLASS()
class PORTFOLIO_API UBaseGameplayEffect : public UGameplayEffect
{
	GENERATED_BODY()

public:

	UPROPERTY(BlueprintReadOnly,EditAnywhere,Category="Effects")
	FName EffectId;



};
