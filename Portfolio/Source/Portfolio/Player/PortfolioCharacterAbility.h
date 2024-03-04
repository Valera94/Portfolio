// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemInterface.h"
#include "PortfolioCharacter.h"
#include "AbilitySystemComponent.h"
#include "Portfolio/GAS/Data/DA_DefaultSettings.h"
#include "ShowDamage/Content/AC_SD_WidgetTextDamage.h"
#include "PortfolioCharacterAbility.generated.h"

DECLARE_LOG_CATEGORY_EXTERN(Project_CharacterAbility, All, All);


/**
 *
 */

UCLASS(Abstract, Config = Game)
class PORTFOLIO_API APortfolioCharacterAbility : public APortfolioCharacter, public IAbilitySystemInterface
{
	GENERATED_BODY()

protected:

	UPROPERTY(Category = Character, VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UAC_SD_WidgetTextDamage>WidgetTextDamage;

public:
	APortfolioCharacterAbility();
	
	virtual void PossessedBy(AController* NewController) override;
protected:

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "GAS", meta = (AllowPrivateAccess))
	TObjectPtr<UAbilitySystemComponent> PortfolioAbilitySystemComponent;

	virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;

	/* ----------------------------------------------------------------------------------------------------------------------
	 *
	 * We use attributes, abilities and effects inside the character,
	 * for the reason that we can change the character to another and abilities,
	 * attributes and effects can be completely different.
	 *
	 * ---------------------------------------------------------------------------------------------------------------------- */

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly,  Category = "GAS", meta = (AllowPrivateAccess))
	TArray<TSubclassOf<UGameplayEffect>> DefaultEffects;
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "GAS", meta = (AllowPrivateAccess))
	TArray<TSubclassOf<UGameplayAbility>> DefaultAbility;

public:
	UPROPERTY()
	TObjectPtr<const class UAttribute_Health> Health;
	UPROPERTY()
	TObjectPtr<const class UAttributeSet_Experience> Experience;


public:
	void IA_Pressed(const FInputActionValue& Value,const FName NameTag);
	
public:
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override { return PortfolioAbilitySystemComponent; }



	UPROPERTY(ReplicatedUsing= OnRep_ViewSkeletalMesh)
	USkeletalMesh* ViewSkeletalMesh;
	UFUNCTION()
	void OnRep_ViewSkeletalMesh();

	UPROPERTY(ReplicatedUsing = OnRep_AnimationSkeletalMesh)
	TSubclassOf<UAnimInstance> AnimationSkeletalMesh;
	UFUNCTION()
	void OnRep_AnimationSkeletalMesh();



	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
};