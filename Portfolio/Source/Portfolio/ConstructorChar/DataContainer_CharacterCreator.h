// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "DataContainer_CharacterCreator.generated.h"

UENUM(BlueprintType)
enum ERaceType : uint8
{
	RT_NONE		UMETA(Hidden),
	RT_Human	UMETA(DisplayName = "Human"),
	RT_Ork		UMETA(DisplayName = "Ork"),
	RT_Elf		UMETA(DisplayName = "Elf"),
};

UENUM(BlueprintType)
enum EGender : uint8
{
	G_NONE		UMETA(Hidden),
	G_Man		UMETA(DisplayName = "Man"),
	G_Women		UMETA(DisplayName = "Women"),
};

UENUM(BlueprintType)
enum EClass : uint8
{
	C_NONE		UMETA(Hidden),
	C_Warrior	UMETA(DisplayName = "Warrior"),
	C_Rogue		UMETA(DisplayName = "Rogue"),
	C_Mage		UMETA(DisplayName = "Mage"),
};

UCLASS()
class PORTFOLIO_API UDataContainer_CharacterCreator : public UObject
{
	GENERATED_BODY()


};
