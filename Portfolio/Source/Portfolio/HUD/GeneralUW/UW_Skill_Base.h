// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/Image.h"
#include "Components/ProgressBar.h"
#include "Components/TextBlock.h"
#include "Abilities/GameplayAbility.h"
#include "Portfolio/HUD/AbilityInterface.h"
#include "UW_Skill_Base.generated.h"


UCLASS(Abstract)
class PORTFOLIO_API UUW_Skill_Base : public UUserWidget, public IAbilityInterface
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadWrite,meta =(AllowPrivateAccess,BindWidget))
	TObjectPtr<UImage> ImageSkill;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (AllowPrivateAccess, BindWidget))
	TObjectPtr<UTextBlock> ButtonText;
	UPROPERTY(BlueprintReadWrite, meta = (AllowPrivateAccess, BindWidget))
	TObjectPtr<UProgressBar> ReloadBar;


	UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (AllowPrivateAccess, ExposeOnSpawn))
	TSubclassOf<UGameplayAbility> AbilityForActivate;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (AllowPrivateAccess, ExposeOnSpawn))
	FText TextButton;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess,ExposeOnSpawn))
	FVector2D IconSelect = FVector2D::One();



public:

	UFUNCTION(BlueprintNativeEvent)
	void ActivatePress();

	UFUNCTION()
	virtual void PressInput(const FString Input) override;

};
