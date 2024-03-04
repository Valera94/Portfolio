// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimBlueprint.h"
#include "DataContainer_CharacterCreator.h"
#include "Engine/StreamableManager.h"
#include "GameplayTagContainer.h"
#include "Portfolio/GAS/Attribute/AttributeSet_General.h"
#include "Portfolio/Player/PortfolioCharacterAbility.h"
#include "DA_CharacterCreator.generated.h"


//This for GAS information only.
USTRUCT(BlueprintType)
struct FStructGAS
{

	GENERATED_BODY()

	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly)
	TArray<TObjectPtr<UAttributeSet_General>> ArrAttribute;

	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly)
	TArray<TObjectPtr<UBaseGameplayEffect>> ArrEffect;
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly)
	TArray<TObjectPtr<UPortfolioGameplayAbility>> ArrAbility;

	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly)
	FGameplayTagContainer GameplayTagContainer;

};

//Text for Widget information
USTRUCT(BlueprintType)
struct FTextInfo
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = "UI|BlockInfoCharacter")
	FString TopText;

	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = "UI|BlockInfoCharacter")
	FString InfoText;

};

//This struct for atlas information
USTRUCT(BlueprintType)
struct FAtlasMaterialCalculate
{
	GENERATED_BODY()

	//U - Horizontal, V - Vertical
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly)
	FVector2D ParameterMaterial = FVector2D(0.f,0.f);

	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly)
	FTextInfo TextInfo;
};

//This struct for Information about character view
USTRUCT(BlueprintType)
struct FStructGender
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly)
	TSoftObjectPtr<USkeletalMesh> SkeletalMeshMan;
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly)
	FTextInfo TextInfoMan;

	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly)
	TSoftObjectPtr<USkeletalMesh> SkeletalMeshWomen;
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly)
	FTextInfo TextInfoWomen;

	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly)
	TSubclassOf<UAnimInstance>AnimationBlueprint;
};







USTRUCT(BlueprintType)
struct FStructRace
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly)
	TSoftObjectPtr<UTexture2D> BackgroundCastleRaceImage;
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly)
	TSubclassOf<AActor> DecorationActor;
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly)
	FAtlasMaterialCalculate AtlasMaterial;
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly)
	FStructGAS UniqueRaceSkill;
};

USTRUCT(BlueprintType)
struct FStructClass
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly)
	TSubclassOf<APortfolioCharacterAbility> ClassForSpawnAndPossess;
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly)
	FAtlasMaterialCalculate AtlasMaterial;
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly)
	FStructGender UniqueViewForClass;
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly)
	FStructGAS UniqueClassSkill;
};


USTRUCT(BlueprintType)
struct FDataTableCharacterCreator :public FTableRowBase
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly)
	TEnumAsByte<ERaceType> TypeRace;

	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = "StructInfo")
	FStructRace struct_Race;

	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = "StructInfo")
	TArray<FStructClass>struct_Class;
};









UCLASS()
class PORTFOLIO_API UDA_CharacterCreator : public UObject
{
	GENERATED_BODY()

};
