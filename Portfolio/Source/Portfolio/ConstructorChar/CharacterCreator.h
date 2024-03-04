// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "DA_CharacterCreator.h"
#include "InterfaceCharacterCreator.h"
#include "UW_CharacterCreator.h"
#include "CharacterCreator.generated.h"


class UUW_CharacterCreator;

/*
 *  If we change the Race, then we automatically
 *  have to change the class and gender related to that race.
 *
 *		- Race	->	Change Class And Gender
 *		- Class	->	Change Gender
 *
 */


USTRUCT(BlueprintType)
struct FInformationAboutWidget
{
	GENERATED_BODY();

	UPROPERTY()
	TWeakObjectPtr<UUW_CharacterCreator> UserWidget;

	UPROPERTY()
	int32 IndexRace = 0;
	UPROPERTY()
	int32 IndexClass = 0;
	UPROPERTY()
	int32 IndexGender = 0;
};

UCLASS(Abstract)
class PORTFOLIO_API ACharacterCreator : public APawn, public IInterfaceCharacterCreator
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ACharacterCreator();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	virtual void PossessedBy(AController* NewController) override;
	virtual void UnPossessed() override;
public:
	void GetDataTableRow(const int32 IndexSelect);


public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Settings")
	TSoftClassPtr<UUW_CharacterCreator> UW_ClassCharacterCreator;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Settings", meta = (AllowPrivateAccess))
	TObjectPtr<UDataTable> DataTableAsset = nullptr;
	UPROPERTY(BlueprintReadOnly)
	FDataTableCharacterCreator RowDataTable;

public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Settings|UI|Visual")
	TSoftObjectPtr<UMaterialInstance> MaterialInstance_Race;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Settings|UI|Visual")
	TSoftObjectPtr<UMaterialInstance> MaterialInstance_Class;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Settings|UI|Visual")
	TSoftObjectPtr<UMaterialInstance> MaterialInstance_Gender;

protected:
	//-------------------
	//Default components = Body actor
	//-------------------

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Default", meta = (AllowPrivateAccess))
	TObjectPtr<USceneComponent> Root;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Default", meta = (AllowPrivateAccess))
	TObjectPtr<UChildActorComponent> Decoration;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Default", meta = (AllowPrivateAccess))
	TObjectPtr<USceneCaptureComponent2D> SceneCaptureComponent;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Default", meta = (AllowPrivateAccess))
	TObjectPtr<USkeletalMeshComponent> SkeletalMeshComponent;

	UPROPERTY()
	FInformationAboutWidget InformationAboutWidget;
public:

	void CreateUW();
	void RecreateImageClass();

	UFUNCTION(Server,Reliable)
	void Server_PossessClient(APlayerController* ThisController, TSubclassOf<APortfolioCharacterAbility> Character, const FInformationAboutWidget& SetInformationAboutWidget);

	//Interface IInterfaceCharacterCreator
	virtual bool FChangeRace(const int32 IndexSelect) override;
	virtual bool FChangeGender(const int32 IndexSelect) override;
	virtual bool FChangeClass(const int32 IndexSelect) override;
	virtual bool FClickComplete() override;

};