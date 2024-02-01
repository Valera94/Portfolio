// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemComponent.h"
#include "GameplayAbilitySpecHandle.h"
#include "Engine/DataAsset.h"
#include "DA_DefaultSettings.generated.h"

class UInputAction;
class UGameplayAbility;
class UAttributeSet;


UENUM(BlueprintType)
enum class EInputID
{
	NONE = 0 UMETA(Hidden),
	Space = 1,
	LeftClick = 2,
	RightClick = 3,
	QClick = 4,
	EClick = 5,
	Press1 = 6,
	Press2 = 7,
	Press3 = 8,
	Press4 = 9,
	Press5 = 10,
};


#pragma region /* *InputBind */

USTRUCT(BlueprintType)
struct FStructAbilityWithInput
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly)
	UInputAction* InputAction;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UGameplayAbility> GameplayAbility;

	UPROPERTY(EditDefaultsOnly)
	EInputID InputID;
};

USTRUCT(BlueprintType)
struct FStartInformation
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly)
	TArray<FStructAbilityWithInput> StructAbilityWithInput;


};

#pragma endregion


/**
 *
 */

UCLASS()
class PORTFOLIO_API UDA_DefaultSettings : public UDataAsset
{
	GENERATED_BODY()

public:

	UPROPERTY(EditDefaultsOnly)
	FStartInformation StartInformation;

	TArray<FGameplayAbilitySpecHandle> GrantAbilitiesToAbilitySystem(UAbilitySystemComponent* AbilitySystemComponent) const;


};
