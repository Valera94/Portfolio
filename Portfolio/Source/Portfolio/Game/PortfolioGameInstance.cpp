// Fill out your copyright notice in the Description page of Project Settings.


#include "PortfolioGameInstance.h"

#include "AbilitySystemGlobals.h"

void UPortfolioGameInstance::Init()
{
	Super::Init();

	UAbilitySystemGlobals::Get().InitGlobalData(); //Initialisation for AbilityTargetSystem

	
}
