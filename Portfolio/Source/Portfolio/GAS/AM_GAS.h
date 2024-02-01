// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/AssetManager.h"
#include "AM_GAS.generated.h"

/**
 * 
 */
UCLASS()
class PORTFOLIO_API UAM_GAS : public UAssetManager
{
	GENERATED_BODY()

public:

	virtual void StartInitialLoading() override;
};
