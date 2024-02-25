// Fill out your copyright notice in the Description page of Project Settings.


#include "Ability_Jump.h"

#include "Portfolio/GAS/Attribute/Attribute_Energy.h"
#include "Portfolio/Player/PortfolioCharacterAbility.h"

UAbility_Jump::UAbility_Jump(const FObjectInitializer& ObjectInitializer)
	:Super(ObjectInitializer)
{
	InstancingPolicy = EGameplayAbilityInstancingPolicy::InstancedPerActor;
	NetExecutionPolicy = EGameplayAbilityNetExecutionPolicy::LocalPredicted;
}

bool UAbility_Jump::CanActivateAbility(const FGameplayAbilitySpecHandle Handle,
                                       const FGameplayAbilityActorInfo* ActorInfo, const FGameplayTagContainer* SourceTags,
                                       const FGameplayTagContainer* TargetTags, FGameplayTagContainer* OptionalRelevantTags) const
{
	if (!ActorInfo || !ActorInfo->AvatarActor.IsValid()) { return false; }
	if (!Super::CanActivateAbility(Handle, ActorInfo, SourceTags, TargetTags, OptionalRelevantTags)) { return false; }
	return true;
}



void UAbility_Jump::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo,
                                    const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);

	if (!CommitAbility(Handle, ActorInfo, ActivationInfo))
	{
		EndAbility(Handle, ActorInfo, ActivationInfo, true, true);
	}

	if (IsActive()) { CancelAbility(Handle, ActorInfo, ActivationInfo, true); }
	Cast<ACharacter>(ActorInfo->AvatarActor)->UnCrouch();
	Cast<ACharacter>(ActorInfo->AvatarActor)->Jump();
}

void UAbility_Jump::EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo,
	const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled)
{
	Super::EndAbility(Handle, ActorInfo, ActivationInfo, bReplicateEndAbility, bWasCancelled);

	if (!ActorInfo->IsLocallyControlled()) { return; }
	Cast<ACharacter>(ActorInfo->AvatarActor)->StopJumping();
}