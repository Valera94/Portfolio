// Fill out your copyright notice in the Description page of Project Settings.


#include "PortfolioCharacterAbility.h"

#include "EnhancedInputComponent.h"
#include "Blueprint/WidgetBlueprintLibrary.h"
#include "Engine/AssetManagerSettings.h"
#include "Kismet/GameplayStatics.h"

#include "Portfolio/GAS/AC_PortfolioAbilitySystem.h"

#include "Portfolio/GAS/Attribute/Attribute_Health.h"
#include "Portfolio/GAS/Attribute/Attribute_Mana.h"
#include "Portfolio/GAS/Attribute/Attribute_Energy.h"
#include "ShowDamage/Content/AC_SD_WidgetTextDamage.h"


DEFINE_LOG_CATEGORY(Project_CharacterAbility);


APortfolioCharacterAbility::APortfolioCharacterAbility()
{
	PortfolioAbilitySystemComponent = CreateDefaultSubobject<UAC_PortfolioAbilitySystem>("AC_PortfolioAbilitySystem");
	PortfolioAbilitySystemComponent->SetIsReplicated(true);
	PortfolioAbilitySystemComponent->SetReplicationMode(EGameplayEffectReplicationMode::Mixed);

	Health = CreateDefaultSubobject<UAttribute_Health>("UAttribute_Health");
	Mana = CreateDefaultSubobject<UAttribute_Mana>("UAttribute_Mana");
	Energy = CreateDefaultSubobject<UAttribute_Energy>("UAttribute_Energy");

	WidgetTextDamage = CreateDefaultSubobject<UAC_SD_WidgetTextDamage>("AC_SD_WidgetTextDamage");
	WidgetTextDamage->SetupAttachment(RootComponent);

}

void APortfolioCharacterAbility::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	check(GetAbilitySystemComponent());
	GetAbilitySystemComponent()->InitAbilityActorInfo(this, this);


	//Add default ability
	for(auto i : DefaultAbility)
	{
		GetAbilitySystemComponent()->GiveAbility(i);
	}


}

void APortfolioCharacterAbility::BeginPlay()
{
	Super::BeginPlay();
}


void APortfolioCharacterAbility::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{

	Super::SetupPlayerInputComponent(PlayerInputComponent);
	// Set up action bindings
	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent)) 
	{

		EnhancedInputComponent->BindAction(InputConfigData->InputSpace, ETriggerEvent::Started, this, &APortfolioCharacterAbility::IA_Space);
		EnhancedInputComponent->BindAction(InputConfigData->InputSpace, ETriggerEvent::Completed, this, &APortfolioCharacterAbility::IA_Space);
	}

}

void APortfolioCharacterAbility::IA_Space(const FInputActionValue& Value)
{
	bool ActivePressed = Value.Get<bool>();

	if (ActivePressed)
	{
		GetAbilitySystemComponent()->TryActivateAbilityByClass(DefaultAbility[0]);
	}
	else
	{
		GetAbilitySystemComponent()->TryActivateAbilityByClass(DefaultAbility[0]);
	}
}
