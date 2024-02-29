// Fill out your copyright notice in the Description page of Project Settings.


#include "DA_DefaultSettings.h"
#include "AbilitySystemComponent.h"
#include "GameplayAbilitySpec.h"

void UDA_DefaultSettings::GiveToAbilitySystem(UAC_PortfolioAbilitySystem& ASC)
{
	if (ASC.GetOwnerRole() != ROLE_Authority) { return; }

	for (auto& i : GrantedGameplayAbilitiesWithInput)
	{
		Cast<UGameplayAbility>(i.GameplayAbility)->AbilityTags.AddTag(i.InputTag); // SimpleAddTagHowConstructor
		FGameplayAbilitySpec L_GameplayAbilitySpec;
		L_GameplayAbilitySpec.Ability = Cast<UGameplayAbility>(i.GameplayAbility);

		ASC.GiveAbility(L_GameplayAbilitySpec);
	}
}