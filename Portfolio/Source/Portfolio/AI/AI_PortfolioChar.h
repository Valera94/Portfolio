// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemInterface.h"
#include "GameplayEffectTypes.h"
#include "GameplayEffect.h"
#include "GameFramework/Character.h"
#include "Portfolio/GAS/Effects/BaseGameplayEffect.h"
#include "AI_PortfolioChar.generated.h"

struct FGameplayTagContainer;

UCLASS()
class PORTFOLIO_API AAI_PortfolioChar : public ACharacter, public IAbilitySystemInterface
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AAI_PortfolioChar();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	/*
	 * Attribute
	 *
	 */

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "GAS", meta = (AllowPrivateAccess))
	TObjectPtr<UAbilitySystemComponent> PortfolioAbilitySystemComponent;
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override { return PortfolioAbilitySystemComponent; }

	UPROPERTY(meta = (AllowPrivateAccess))
	TObjectPtr<const class UAttribute_Health> Health;
	UPROPERTY(meta = (AllowPrivateAccess))
	TObjectPtr<const class UAttribute_Mana> Mana;
	UPROPERTY(meta = (AllowPrivateAccess))
	TObjectPtr<const class UAttribute_Energy> Energy;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "GAS", meta = (AllowPrivateAccess))
	FGameplayTagContainer GameplayTagContainer;

	UFUNCTION(BlueprintCallable, Category = "GAS|Tag")
	void AddGamePlayTag(const FGameplayTag& TagToAdd);
	UFUNCTION(BlueprintCallable, Category = "GAS|Tag")
	bool HasGamePlayTag(const FGameplayTag& TagCheck);
	UFUNCTION(BlueprintCallable, Category = "GAS|Tag")
	void RemoveGamePlayTag(const FGameplayTag& TagCheck);

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "GAS|Effects")
	TArray<TSubclassOf<UBaseGameplayEffect>> DefaultEffects;

	UFUNCTION(BlueprintCallable)
	void InitEffect();
	UFUNCTION(BlueprintCallable)
	void AddEffect(TSubclassOf<UBaseGameplayEffect> Effect);

	UFUNCTION(Reliable, Server, BlueprintCallable)
	void ServerAddEffect(TSubclassOf<UBaseGameplayEffect> Effect);

	UPROPERTY(Replicated,BlueprintReadWrite,Category="Gas|Effects")
	TArray<FEffectKeyPair>Effects;

	virtual void GetLifetimeReplicatedProps(TArray< FLifetimeProperty >& OutLifetimeProps) const override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
