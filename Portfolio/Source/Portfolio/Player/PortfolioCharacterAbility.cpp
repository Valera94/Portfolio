// Fill out your copyright notice in the Description page of Project Settings.


#include "PortfolioCharacterAbility.h"

#include "AbilitySystemGlobals.h"
#include "BlueprintGameplayTagLibrary.h"
#include "EnhancedInputComponent.h"
#include "Engine/AssetManagerSettings.h"
#include "GameFramework/GameModeBase.h"
#include "Kismet/GameplayStatics.h"
#include "Net/UnrealNetwork.h"

#include "Portfolio/GAS/AC_PortfolioAbilitySystem.h"
#include "Portfolio/GAS/Attribute/AttributeSet_Experience.h"

#include "Portfolio/GAS/Attribute/Attribute_Health.h"

#include "ShowDamage/Content/AC_SD_WidgetTextDamage.h"


DEFINE_LOG_CATEGORY(Project_CharacterAbility);


APortfolioCharacterAbility::APortfolioCharacterAbility()
{
	PortfolioAbilitySystemComponent = CreateDefaultSubobject<UAC_PortfolioAbilitySystem>("AC_PortfolioAbilitySystem");
	PortfolioAbilitySystemComponent->SetIsReplicated(true);
	PortfolioAbilitySystemComponent->SetReplicationMode(EGameplayEffectReplicationMode::Mixed);


	Health = CreateDefaultSubobject<UAttribute_Health>("UAttribute_Health");
	Experience = CreateDefaultSubobject<UAttributeSet_Experience>("UAttributeSet_Experience");

	WidgetTextDamage = CreateDefaultSubobject<UAC_SD_WidgetTextDamage>("AC_SD_WidgetTextDamage");
	WidgetTextDamage->SetupAttachment(RootComponent);
	WidgetTextDamage->SetCollisionEnabled(ECollisionEnabled::NoCollision);
}

void APortfolioCharacterAbility::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);

	check(PortfolioAbilitySystemComponent)

		GetAbilitySystemComponent()->InitAbilityActorInfo(NewController, this);

	//Add default ability
	for (auto i : DefaultAbility)
	{
		GetAbilitySystemComponent()->GiveAbility(i);
	}

	//Add default Effect
	for (auto i : DefaultEffects)
	{
		GetAbilitySystemComponent()->MakeEffectContext().AddSourceObject(this);
	}


}

void APortfolioCharacterAbility::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	// Set up action bindings
	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent))
	{
		EnhancedInputComponent->BindAction(Cast<APortfolioPlayerController>(GetController())->InputConfigData->InputLeftClickMouse, ETriggerEvent::Started, this, &APortfolioCharacterAbility::IA_Pressed, FName("Ability.Action.Shoot"));
		EnhancedInputComponent->BindAction(Cast<APortfolioPlayerController>(GetController())->InputConfigData->InputSpace, ETriggerEvent::Started, this, &APortfolioCharacterAbility::IA_Pressed, FName("Ability.Action.Jump"));
	}
}

void APortfolioCharacterAbility::IA_Pressed(const FInputActionValue& Value, const FName NameTag)
{
	bool ActivePressed = Value.Get<bool>();

	if (ActivePressed)
	{
		FGameplayTagContainer TagContainer;
		TagContainer.AddTag(FGameplayTag::RequestGameplayTag(NameTag));
		GetAbilitySystemComponent()->TryActivateAbilitiesByTag(TagContainer, true);
	}
}

void APortfolioCharacterAbility::OnRep_ViewSkeletalMesh()
{
	GetMesh()->SetSkeletalMesh(ViewSkeletalMesh);
}

void APortfolioCharacterAbility::OnRep_AnimationSkeletalMesh()
{
	GetMesh()->SetAnimClass(AnimationSkeletalMesh);
}

void APortfolioCharacterAbility::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME(APortfolioCharacterAbility, ViewSkeletalMesh)
	DOREPLIFETIME(APortfolioCharacterAbility, AnimationSkeletalMesh)
}
