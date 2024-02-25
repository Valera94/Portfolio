// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "Layer/UW_LayerPawn.h"
#include "PortfolioHUD.generated.h"

//class UUW_MainGame;

/**
 *
 */
UCLASS()
class PORTFOLIO_API APortfolioHUD : public AHUD
{
	GENERATED_BODY()



public:

	//Main Game Widget
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Instanced, Category = "Layer", meta = (AllowPrivateAccess))
	TObjectPtr<class UUW_MainGame> MainGameWidget;

	virtual void BeginPlay() override;

	virtual bool AddMainHeroWidget();

};
