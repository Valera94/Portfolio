// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "DA_CharacterCreator.h"
#include "InterfaceCharacterCreator.h"
#include "UW_CharacterCreator.h"
#include "CharacterCreator.generated.h"


class UUW_CharacterCreator;




UCLASS(Abstract)
class PORTFOLIO_API ACharacterCreator : public AActor, public IInterfaceCharacterCreator
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ACharacterCreator();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	void GetDataTableRow(const int32 IndexSelect);


public:
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

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Settings")
	TSoftClassPtr<UUW_CharacterCreator> UW_ClassCharacterCreator;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Settings", meta = (ExposeOnSpawn))
	TObjectPtr <ACharacter> CharacterForBackView;

protected:
	//-------------------
	//Default components = Body actor
	//-------------------

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Default", meta = (AllowPrivateAccess))
	TObjectPtr<USceneComponent> Root;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Default", meta = (AllowPrivateAccess))
	TObjectPtr<USceneComponent> Decoration;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Default", meta = (AllowPrivateAccess))
	TObjectPtr<USceneCaptureComponent2D> SceneCaptureComponent;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Default", meta = (AllowPrivateAccess))
	TObjectPtr<USkeletalMeshComponent> SkeletalMeshComponent;

public:

	FGameplayTag TagClass;

public:

	void CreateUW();
	void ConstructorCharacter();

	//Interface IInterfaceCharacterCreator
	virtual bool FChangeRace(const int32 IndexSelect) override;
	virtual bool FChangeGender(const int32 IndexSelect) override;
	virtual bool FChangeClass(const int32 IndexSelect) override;
	virtual bool FClickComplete() override;

};