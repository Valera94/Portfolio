// Fill out your copyright notice in the Description page of Project Settings.


#include "Attribute_Health.h"
#include "GameplayEffectExtension.h"
#include "Net/UnrealNetwork.h"

UAttribute_Health::UAttribute_Health()
	:Health(100.f)
	,HealthMax(100.f)
{
}

void UAttribute_Health::OnRep_Health(const FGameplayAttributeData& OldHealth)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAttribute_Health, Health, OldHealth);
}

void UAttribute_Health::OnRep_HealthMax(const FGameplayAttributeData& OldHealthMax)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAttribute_Health, HealthMax, OldHealthMax);
}

void UAttribute_Health::PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue)
{
	Super::PreAttributeChange(Attribute, NewValue);

	if (Attribute == GetHealthAttribute())
	{
		NewValue = FMath::Clamp(NewValue, 0.f, GetHealthMax());
	}
}

void UAttribute_Health::PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data)
{
	Super::PostGameplayEffectExecute(Data);
	if (Data.EvaluatedData.Attribute == GetDamageAttribute())
	{
		if (GetDamage() > 0)
		{
			const float LocalDamageDone = GetDamage();
			SetDamage(0.f);
			SetHealth(FMath::Clamp(GetHealth() - LocalDamageDone, 0.f, GetHealthMax()));
		}
	}
}

void UAttribute_Health::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME_CONDITION_NOTIFY(UAttribute_Health, Health, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UAttribute_Health, HealthMax, COND_None, REPNOTIFY_Always);
}