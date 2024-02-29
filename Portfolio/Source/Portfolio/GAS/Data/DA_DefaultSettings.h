// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemComponent.h"
#include "Engine/DataAsset.h"
#include "Portfolio/GAS/AC_PortfolioAbilitySystem.h"
#include <Portfolio\GAS\PortfolioGameplayAbility.h>
#include "DA_DefaultSettings.generated.h"

class UInputAction;
class UGameplayAbility;
class UAttributeSet;


/**
 *  GameplayAbilityInput
 */
USTRUCT(BlueprintType)
struct FAbilitySet_GameplayAbilityInput
{
	GENERATED_BODY()

public:
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UPortfolioGameplayAbility> GameplayAbility = nullptr;

	UPROPERTY(EditDefaultsOnly)
	FGameplayTag InputTag;

	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<UInputAction> InputAction;

};

/**
 * GameplayEffect
 */
USTRUCT(BlueprintType)
struct FAbilitySet_GameplayEffect
{
	GENERATED_BODY()

public:

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UBaseGameplayEffect> GameplayEffect = nullptr;

	UPROPERTY(EditDefaultsOnly)
	float EffectLevel = 1.0f;
};


/**
 * AttributeSet
 */
USTRUCT(BlueprintType)
struct FAbilitySet_AttributeSet
{
	GENERATED_BODY()

public:
	// Gameplay effect to grant.
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UAttributeSet> AttributeSet;

};

UCLASS(Blueprinttype)
class PORTFOLIO_API UDA_DefaultSettings : public UDataAsset
{
	GENERATED_BODY()

public:
	
	// Grants the ability set to the specified ability system component.
	// The returned handles can be used later to take away anything that was granted.
	void GiveToAbilitySystem(UAC_PortfolioAbilitySystem& ASC);

protected:

	// Gameplay abilities to grant when this ability set is granted.
	UPROPERTY(EditDefaultsOnly, Category = "Gameplay Abilities", meta = (TitleProperty = Ability))
	TArray<FAbilitySet_GameplayAbilityInput> GrantedGameplayAbilitiesWithInput;

	// Gameplay effects to grant when this ability set is granted.
	UPROPERTY(EditDefaultsOnly, Category = "Gameplay Effects", meta = (TitleProperty = GameplayEffect))
	TArray<FAbilitySet_GameplayEffect> GrantedGameplayEffects;

	// Attribute sets to grant when this ability set is granted.
	UPROPERTY(EditDefaultsOnly, Category = "Attribute Sets", meta = (TitleProperty = AttributeSet))
	TArray<FAbilitySet_AttributeSet> GrantedAttributes;

};
