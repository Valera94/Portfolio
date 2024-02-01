// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemComponent.h"
#include "AttributeSet_General.h"
#include "Attribute_Energy.generated.h"

/**
 *
 */
UCLASS()
class PORTFOLIO_API UAttribute_Energy : public UAttributeSet_General
{
	GENERATED_BODY()

public:

	ATTRIBUTE_ACCESSORS(UAttribute_Energy, Energy)
	ATTRIBUTE_ACCESSORS(UAttribute_Energy, EnergyMax)
	ATTRIBUTE_ACCESSORS(UAttribute_Energy, DamageEnergy)

private:

	UAttribute_Energy();

	UPROPERTY(BlueprintReadOnly, Category = "Energy", ReplicatedUsing = OnRep_Energy, meta = (AllowPrivateAccess))
	FGameplayAttributeData Energy;

	UPROPERTY(BlueprintReadOnly, Category = "Energy", ReplicatedUsing = OnRep_EnergyMax, meta = (AllowPrivateAccess))
	FGameplayAttributeData EnergyMax;

	UPROPERTY(BlueprintReadOnly, Category = "Energy", meta = (AllowPrivateAccess))
	FGameplayAttributeData DamageEnergy;


	UFUNCTION()
	virtual void OnRep_Energy(const FGameplayAttributeData& OldEnergy);
	UFUNCTION()
	virtual void OnRep_EnergyMax(const FGameplayAttributeData& OldEnergyMax);



	virtual void PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue) override;
	virtual void PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data) override;
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps)  const override;
};
