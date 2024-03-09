// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/Overlay.h"
#include "Portfolio/Player/PortfolioCharacterAbility.h"
#include "UW_MainGame.generated.h"

class UCanvasPanel;

/**
 *
 */
UCLASS()
class PORTFOLIO_API UUW_MainGame : public UUserWidget
{
	GENERATED_BODY()

	virtual void NativeConstruct() override;

public:

	UPROPERTY(BlueprintReadOnly,meta = (ExposeOnSpawn))
	TObjectPtr<APortfolioCharacterAbility>CharacterAbility;

public:

	//NeedConstruction Layer
	UPROPERTY(BlueprintReadWrite, Instanced, EditDefaultsOnly, meta = (AllowPrivateAccess))
	TObjectPtr <UUserWidget> Layer_Pawn;
	UPROPERTY(BlueprintReadWrite, Instanced, EditDefaultsOnly, meta = (AllowPrivateAccess))
	TObjectPtr <UUserWidget> Layer_Info;
	UPROPERTY(BlueprintReadWrite, Instanced, EditDefaultsOnly, meta = (AllowPrivateAccess))
	TObjectPtr <UUserWidget> Layer_Menu;
};
