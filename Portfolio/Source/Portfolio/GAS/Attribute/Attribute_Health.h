// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemComponent.h"
#include "AttributeSet_General.h"
#include "Attribute_Health.generated.h"


/**
 * 
 */
UCLASS()
class PORTFOLIO_API UAttribute_Health : public UAttributeSet_General
{
	GENERATED_BODY()


public:

	ATTRIBUTE_ACCESSORS(UAttribute_Health, Health)
	ATTRIBUTE_ACCESSORS(UAttribute_Health, HealthMax)
	ATTRIBUTE_ACCESSORS(UAttribute_Health, Damage)

protected:


	UPROPERTY(BlueprintReadOnly, Category = "Health", ReplicatedUsing = OnRep_Health)
	FGameplayAttributeData Health;

	UPROPERTY(BlueprintReadOnly, Category = "Health", ReplicatedUsing = OnRep_HealthMax)
	FGameplayAttributeData HealthMax;

	UPROPERTY(BlueprintReadOnly, Category = "Health")
	FGameplayAttributeData Damage;


private:

	UAttribute_Health();

	UFUNCTION()
	virtual void OnRep_Health(const FGameplayAttributeData& OldHealth);
	UFUNCTION()
	virtual void OnRep_HealthMax(const FGameplayAttributeData& OldHealthMax);

	virtual void PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue) override;
	virtual void PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data) override;
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps)  const override;


};
