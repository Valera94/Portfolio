// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimBlueprint.h"
#include "DataContainer_CharacterCreator.h"
#include "Engine/StreamableManager.h"
#include "DA_CharacterCreator.generated.h"

/**
 *
 */
USTRUCT(BlueprintType)
struct FTextInfo
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = "UI|BlockInfoCharacter")
	FString TopText;

	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = "UI|BlockInfoCharacter")
	FString InfoText;
};

USTRUCT(BlueprintType)
struct FStructInfo
{
	GENERATED_BODY()

	//U - Horizontal, V - Vertical
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly)
	FVector2D ParameterMaterial;

	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly)
	FTextInfo TextInfo;
};

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
	TSoftObjectPtr<UAnimBlueprint>AnimationBlueprint;
};




USTRUCT(BlueprintType)
struct FDataTableCharacterCreator :public FTableRowBase
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly)
	TEnumAsByte<ERaceType> TypeRace;

	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly)
	TSoftObjectPtr<UTexture2D> BackgroundCastleRaceImage;


	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = "StructInfo")
	FStructInfo struct_Race;

	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = "StructInfo")
	TArray<FStructInfo>struct_Class;

	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = "StructInfo")
	FStructGender struct_Gender;

};









UCLASS()
class PORTFOLIO_API UDA_CharacterCreator : public UObject
{
	GENERATED_BODY()

};
