// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameMode.h"
#include "PortfolioGameMode.generated.h"

UCLASS(Abstract)
class APortfolioGameMode : public AGameMode
{
	GENERATED_BODY()

public:
	APortfolioGameMode();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Classes)
	TSubclassOf<APawn> DefaultCharacter;
	
	virtual void PostLogin(APlayerController* NewPlayer) override;
};



