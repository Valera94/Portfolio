// Fill out your copyright notice in the Description page of Project Settings.


#include "PortfolioCharacterAbility.h"

#include "EnhancedInputComponent.h"
#include "Blueprint/UserWidget.h"
#include "Engine/AssetManagerSettings.h"
#include "Kismet/GameplayStatics.h"

#include "Portfolio/GAS/AC_PortfolioAbilitySystem.h"

#include "Portfolio/GAS/Attribute/Attribute_Health.h"
#include "Portfolio/GAS/Attribute/Attribute_Mana.h"
#include "Portfolio/GAS/Attribute/Attribute_Energy.h"



APortfolioCharacterAbility::APortfolioCharacterAbility()
{
	PortfolioAbilitySystemComponent = CreateDefaultSubobject<UAC_PortfolioAbilitySystem>("AC_PortfolioAbilitySystem");
	PortfolioAbilitySystemComponent->SetIsReplicated(true);
	PortfolioAbilitySystemComponent->SetReplicationMode(EGameplayEffectReplicationMode::Mixed);


	Health = CreateDefaultSubobject<UAttribute_Health>("UAttribute_Health");
	Mana = CreateDefaultSubobject<UAttribute_Mana>("UAttribute_Mana");
	Energy = CreateDefaultSubobject<UAttribute_Energy>("UAttribute_Energy");


}

void APortfolioCharacterAbility::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);

}

void APortfolioCharacterAbility::BeginPlay()
{
	Super::BeginPlay();


}

void APortfolioCharacterAbility::OnRep_PlayerState()
{
	Super::OnRep_PlayerState();

}

void APortfolioCharacterAbility::OnRep_Controller()
{
	Super::OnRep_Controller();

}


void APortfolioCharacterAbility::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent))
	{
		if (HasAuthority())
		{
			SetupInitialAbilitiesAndEffects();
		}

		for (const FStructAbilityWithInput& Binding : DA_DefaultSettings->StartInformation.StructAbilityWithInput)
		{
			EnhancedInputComponent->BindAction(Binding.InputAction, ETriggerEvent::Started, this, &APortfolioCharacterAbility::AbilityInputBindingsPressedHandler, Binding.InputID);
			EnhancedInputComponent->BindAction(Binding.InputAction, ETriggerEvent::Completed, this, &APortfolioCharacterAbility::AbilityInputBindingsReleasedHandler, Binding.InputID);
		}
	}
}

void APortfolioCharacterAbility::AbilityInputBindingsPressedHandler(const EInputID AbilityInput)
{
	GetAbilitySystemComponent()->AbilityLocalInputPressed(static_cast<uint32>(AbilityInput));
}


void APortfolioCharacterAbility::AbilityInputBindingsReleasedHandler(const EInputID AbilityInput)
{
	GetAbilitySystemComponent()->AbilityLocalInputReleased(static_cast<uint32>(AbilityInput));

}


void APortfolioCharacterAbility::SetupInitialAbilitiesAndEffects()
{
	if (!GetAbilitySystemComponent())
	{
		return;
	}

	if (InitiallyGrantedAbilitySpecHandles.IsEmpty())
	{
		for (const auto AbilitySetItem : DA_DefaultSettings->StartInformation.StructAbilityWithInput)
		{
			FGameplayAbilitySpec L_GameplayAbilitySpec = FGameplayAbilitySpec(AbilitySetItem.GameplayAbility, 0, static_cast<uint32>(AbilitySetItem.InputID));
			GetAbilitySystemComponent()->GiveAbility(L_GameplayAbilitySpec);
		}
	}
}
