// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayCueManager.h"
#include "PortfolioGameplayCueManager.generated.h"

/**
 * 
 */
UCLASS()
class PORTFOLIO_API UPortfolioGameplayCueManager : public UGameplayCueManager
{
	GENERATED_BODY()

	virtual bool ShouldAsyncLoadRuntimeObjectLibraries() const override { return false; };

};
