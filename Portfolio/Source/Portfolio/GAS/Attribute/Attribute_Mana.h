// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemComponent.h"
#include "AttributeSet_General.h"
#include "Attribute_Mana.generated.h"


/**
 *
 */

UCLASS()
class PORTFOLIO_API UAttribute_Mana : public UAttributeSet_General
{
	GENERATED_BODY()

public:

	ATTRIBUTE_ACCESSORS(UAttribute_Mana, Mana)
	ATTRIBUTE_ACCESSORS(UAttribute_Mana, ManaMax)
	ATTRIBUTE_ACCESSORS(UAttribute_Mana, DamageMana)


protected:

	UPROPERTY(BlueprintReadOnly, Category = "Mana", ReplicatedUsing = OnRep_Mana,meta=(AllowPrivateAccess))
	FGameplayAttributeData Mana;

	UPROPERTY(BlueprintReadOnly, Category = "Mana", ReplicatedUsing = OnRep_ManaMax, meta = (AllowPrivateAccess))
	FGameplayAttributeData ManaMax;

	UPROPERTY(BlueprintReadOnly, Category = "Mana", meta = (AllowPrivateAccess))
	FGameplayAttributeData DamageMana;

private:
	UAttribute_Mana();

	UFUNCTION()
	virtual void OnRep_Mana(const FGameplayAttributeData& OldMana);
	UFUNCTION()
	virtual void OnRep_ManaMax(const FGameplayAttributeData& OldManaMax);



	virtual void PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue) override;
	virtual void PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data) override;

	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps)  const override;

};
