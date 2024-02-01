// Fill out your copyright notice in the Description page of Project Settings.


#include "DA_DefaultSettings.h"

#include "AbilitySystemComponent.h"
#include "GameplayAbilitySpec.h"

TArray<FGameplayAbilitySpecHandle> UDA_DefaultSettings::GrantAbilitiesToAbilitySystem(
	UAbilitySystemComponent* AbilitySystemComponent) const
{
	check(AbilitySystemComponent)

	TArray<FGameplayAbilitySpecHandle> handles;
	
	handles.Reserve(StartInformation.StructAbilityWithInput.Num());
	
	for (const auto AbilitySetItem : StartInformation.StructAbilityWithInput)
	{
		handles.AddUnique(
			AbilitySystemComponent->GiveAbility(
				FGameplayAbilitySpec(
					AbilitySetItem.GameplayAbility,
					0,
					static_cast<uint32>(AbilitySetItem.InputID)
				)
			)
		);
	}
	return handles;
}
