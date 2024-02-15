// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemInterface.h"
#include "PortfolioCharacter.h"
#include "Portfolio/GAS/Data/DA_DefaultSettings.h"
#include "Portfolio/HUD/HUDInterface.h"
#include "PortfolioCharacterAbility.generated.h"

DECLARE_LOG_CATEGORY_EXTERN(Project_CharacterAbility, All, All);



/**
 *
 */

UCLASS(Config = Game)
class PORTFOLIO_API APortfolioCharacterAbility : public APortfolioCharacter, public IAbilitySystemInterface, public IHUDInterface
{
	GENERATED_BODY()

public:
	APortfolioCharacterAbility();

	virtual void PostInitializeComponents() override;

	virtual void BeginPlay() override;

protected:

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "GAS", meta = (AllowPrivateAccess))
	TObjectPtr<UAbilitySystemComponent> PortfolioAbilitySystemComponent;

	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override { return PortfolioAbilitySystemComponent; }

	virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;


	/* ----------------------------------------------------------------------------------------------------------------------
	 *
	 * We use attributes, abilities and effects inside the character,
	 * for the reason that we can change the character to another and abilities,
	 * attributes and effects can be completely different.
	 *
	 * ---------------------------------------------------------------------------------------------------------------------- */


	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "GAS", meta = (AllowPrivateAccess))
	TArray<FBindInput> BindInputWithTag;

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly,  Category = "GAS", meta = (AllowPrivateAccess))
	TArray<TSubclassOf<UGameplayEffect>> DefaultEffects;

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "GAS", meta = (AllowPrivateAccess))
	TArray<TSubclassOf<UGameplayAbility>> DefaultAbility;

	UPROPERTY()
	TObjectPtr<const class UAttribute_Health> Health;
	UPROPERTY()
	TObjectPtr<const class UAttribute_Mana> Mana;
	UPROPERTY()
	TObjectPtr<const class UAttribute_Energy> Energy;

	/* ----------------------------------------------------------------------------------------------------------------------
	 * Input Bind
	 * ---------------------------------------------------------------------------------------------------------------------- */
	
	void IA_Space(const FInputActionValue& Value);

};