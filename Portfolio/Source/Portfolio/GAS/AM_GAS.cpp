// Fill out your copyright notice in the Description page of Project Settings.


#include "AM_GAS.h"
#include "AbilitySystemGlobals.h"

void UAM_GAS::StartInitialLoading()
{
	Super::StartInitialLoading();
	UAbilitySystemGlobals::Get().InitGlobalData();
}
