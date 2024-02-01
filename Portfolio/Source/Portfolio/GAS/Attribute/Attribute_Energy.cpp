// Fill out your copyright notice in the Description page of Project Settings.


#include "Attribute_Energy.h"
#include "GameplayEffectExtension.h"
#include "GameplayEffectTypes.h"
#include "Net/UnrealNetwork.h"


UAttribute_Energy::UAttribute_Energy()
	:Energy(100.f)
, EnergyMax(100.f)
{

}

void UAttribute_Energy::OnRep_Energy(const FGameplayAttributeData& OldEnergy)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAttribute_Energy, Energy, OldEnergy);
}

void UAttribute_Energy::OnRep_EnergyMax(const FGameplayAttributeData& OldEnergyMax)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAttribute_Energy, EnergyMax, OldEnergyMax);
}

void UAttribute_Energy::PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue)
{
	Super::PreAttributeChange(Attribute, NewValue);

	if (Attribute == GetEnergyAttribute())
	{
		NewValue = FMath::Clamp(NewValue, 0.f, GetEnergyMax());
	}
}

void UAttribute_Energy::PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data)
{
	Super::PostGameplayEffectExecute(Data);
	if (Data.EvaluatedData.Attribute == GetDamageEnergyAttribute())
	{
		if (GetDamageEnergy() > 0)
		{
			const float LocalDamageEnergyDone = GetDamageEnergy();
			SetDamageEnergy(0.f);
			SetEnergy(FMath::Clamp(GetEnergy() - LocalDamageEnergyDone, 0.f, GetEnergyMax()));
		}
	}
}

void UAttribute_Energy::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME_CONDITION_NOTIFY(UAttribute_Energy, Energy, COND_None, REPNOTIFY_OnChanged);
	DOREPLIFETIME_CONDITION_NOTIFY(UAttribute_Energy, EnergyMax, COND_None, REPNOTIFY_OnChanged);
}
