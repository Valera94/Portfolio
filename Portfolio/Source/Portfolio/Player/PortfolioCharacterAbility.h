// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemInterface.h"
#include "PortfolioCharacter.h"
#include "Portfolio/GAS/Data/DA_DefaultSettings.h"
#include "PortfolioCharacterAbility.generated.h"
/**
 *
 */

UCLASS(Config = Game)
class PORTFOLIO_API APortfolioCharacterAbility : public APortfolioCharacter, public IAbilitySystemInterface
{
	GENERATED_BODY()

protected:
	APortfolioCharacterAbility();


protected:

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = GAS, meta = (AllowPrivateAccess))
	TObjectPtr<UAbilitySystemComponent> PortfolioAbilitySystemComponent;
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override { return PortfolioAbilitySystemComponent; }



	UPROPERTY(EditAnywhere,BlueprintReadOnly,Category= "Effects")
	TArray<TSubclassOf<class UBaseGameplayEffect>> DefaultEffects;

	//DefaultAttribute
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = GAS, meta = (AllowPrivateAccess))
	TObjectPtr<const class UAttribute_Health> Health;
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = GAS, meta = (AllowPrivateAccess))
	TObjectPtr<const class UAttribute_Mana> Mana;
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = GAS, meta = (AllowPrivateAccess))
	TObjectPtr<const class UAttribute_Energy> Energy;
	
	UPROPERTY()
	TArray<FGameplayAbilitySpecHandle> InitiallyGrantedAbilitySpecHandles;

	UPROPERTY(EditDefaultsOnly, Category = GAS, meta = (AllowPrivateAccess))
	UDA_DefaultSettings* DA_DefaultSettings;

	virtual void PossessedBy(AController* NewController) override;
	virtual void BeginPlay() override;
	virtual void OnRep_PlayerState() override;
	virtual void OnRep_Controller() override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	//Pressed
	void AbilityInputBindingsPressedHandler(const EInputID AbilityInput);
	//UnPressed
	void AbilityInputBindingsReleasedHandler(const EInputID AbilityInput);

	void SetupInitialAbilitiesAndEffects();

};