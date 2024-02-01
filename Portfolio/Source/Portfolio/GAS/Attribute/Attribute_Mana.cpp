// Fill out your copyright notice in the Description page of Project Settings.


#include "Attribute_Mana.h"
#include "GameplayEffectExtension.h"
#include "GameplayEffectTypes.h"
#include "Net/UnrealNetwork.h"

UAttribute_Mana::UAttribute_Mana()
	:Mana(100.f)
	,ManaMax(100.f)
{
}

void UAttribute_Mana::OnRep_Mana(const FGameplayAttributeData& OldMana)
{

	GAMEPLAYATTRIBUTE_REPNOTIFY(UAttribute_Mana, Mana, OldMana);
}

void UAttribute_Mana::OnRep_ManaMax(const FGameplayAttributeData& OldManaMax)
{

	GAMEPLAYATTRIBUTE_REPNOTIFY(UAttribute_Mana, ManaMax, OldManaMax);
}

void UAttribute_Mana::PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue)
{
	Super::PreAttributeChange(Attribute, NewValue);

	if (Attribute == GetManaAttribute())
	{
		NewValue = FMath::Clamp(NewValue, 0.f, GetManaMax());
	}
}

void UAttribute_Mana::PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data)
{
	Super::PostGameplayEffectExecute(Data);
	if (Data.EvaluatedData.Attribute == GetDamageManaAttribute())
	{
		if (GetDamageMana() > 0)
		{
			const float LocalDamageManaDone = GetDamageMana();
			SetDamageMana(0.f);
			SetMana(FMath::Clamp(GetMana() - LocalDamageManaDone, 0.f, GetManaMax()));
		}
	}
}

void UAttribute_Mana::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME_CONDITION_NOTIFY(UAttribute_Mana, Mana, COND_None, REPNOTIFY_OnChanged);
	DOREPLIFETIME_CONDITION_NOTIFY(UAttribute_Mana, ManaMax, COND_None, REPNOTIFY_OnChanged);
}