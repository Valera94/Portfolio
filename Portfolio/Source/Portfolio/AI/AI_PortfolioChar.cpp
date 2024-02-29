// Fill out your copyright notice in the Description page of Project Settings.


#include "AI_PortfolioChar.h"

#include "AbilitySystemComponent.h"
#include "PortfolioAIController.h"
#include "Net/UnrealNetwork.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Portfolio/GAS/AC_PortfolioAbilitySystem.h"
#include "Portfolio/GAS/Attribute/Attribute_Energy.h"
#include "Portfolio/GAS/Attribute/Attribute_Health.h"
#include "Portfolio/GAS/Attribute/Attribute_Mana.h"

// Sets default values
AAI_PortfolioChar::AAI_PortfolioChar()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;


	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = FRotator(0.f, 540.f, 0.f);
	bUseControllerRotationYaw = false;



	PortfolioAbilitySystemComponent = CreateDefaultSubobject<UAC_PortfolioAbilitySystem>("AC_PortfolioAbilitySystem");
	PortfolioAbilitySystemComponent->SetIsReplicated(true);
	PortfolioAbilitySystemComponent->SetReplicationMode(EGameplayEffectReplicationMode::Mixed);

	Health = CreateDefaultSubobject<UAttribute_Health>("UAttribute_Health");
	Mana = CreateDefaultSubobject<UAttribute_Mana>("UAttribute_Mana");
	Energy = CreateDefaultSubobject<UAttribute_Energy>("UAttribute_Energy");

	AIControllerClass = APortfolioAIController::StaticClass();
	AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;

}

// Called when the game starts or when spawned
void AAI_PortfolioChar::BeginPlay()
{
	Super::BeginPlay();

	//PortfolioAbilitySystemComponent->InitAbilityActorInfo(this, this);
	InitEffect();
}

void AAI_PortfolioChar::AddGamePlayTag(const FGameplayTag& TagToAdd)
{
	GameplayTagContainer.AddTag(TagToAdd);
}

bool AAI_PortfolioChar::HasGamePlayTag(const FGameplayTag& TagCheck)
{
	return GameplayTagContainer.HasTag(TagCheck);
}

void AAI_PortfolioChar::RemoveGamePlayTag(const FGameplayTag& TagCheck)
{
	GameplayTagContainer.RemoveTag(TagCheck);
}

void AAI_PortfolioChar::InitEffect()
{
	for (auto i : DefaultEffects)
	{
		AddEffect(i);
	}
}

void AAI_PortfolioChar::AddEffect(TSubclassOf<UBaseGameplayEffect> Effect)
{
	if (!HasAuthority())
	{
		ServerAddEffect(Effect);
	}
	if (GetAbilitySystemComponent())
	{
		TSubclassOf<UBaseGameplayEffect>& EffectRef = Effect;

		FGameplayEffectContextHandle EffectContext = PortfolioAbilitySystemComponent->MakeEffectContext();
		EffectContext.AddSourceObject(this);

		FGameplayEffectSpecHandle EffectSpecHandle = PortfolioAbilitySystemComponent->MakeOutgoingSpec(Effect->StaticClass(), 1, EffectContext);

	}
}

void AAI_PortfolioChar::ServerAddEffect_Implementation(TSubclassOf<UBaseGameplayEffect> Effect)
{
	AddEffect(Effect);
}

//bool AAI_PortfolioChar::ServerAddEffect_Validate(UGameplayEffect* Effect)
//{
//	return true;
//}


void AAI_PortfolioChar::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

}

// Called every frame
void AAI_PortfolioChar::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AAI_PortfolioChar::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

