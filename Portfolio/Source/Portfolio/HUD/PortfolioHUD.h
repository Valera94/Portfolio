// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UW_MainGame.h"
#include "GameFramework/HUD.h"
#include "Layer/UW_LayerPawn.h"
#include "Portfolio/Game/PortfolioSaveGame.h"
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

	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = "Layer", meta = (AllowPrivateAccess))
	TObjectPtr<UUW_MainGame> PawnWidget;

	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = "Layer", meta = (AllowPrivateAccess))
	TObjectPtr<UUserWidget> MenuWidget;

	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = "Layer", meta = (AllowPrivateAccess))
	TObjectPtr<UUserWidget> InfoWidget;


	virtual void BeginPlay() override;

	UFUNCTION(BlueprintNativeEvent)
	void BindDelegatePossessed(APawn* OldPawn, APawn* NewPawn);

	UFUNCTION(BlueprintCallable)
	void SaveSettingKeyboard(FSetting Setting);

	UFUNCTION(BlueprintCallable)
	FSetting LoadSaveSettingKeyboard();

};
