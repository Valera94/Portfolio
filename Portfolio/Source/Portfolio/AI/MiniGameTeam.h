// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AI_PortfolioChar.h"
#include "Components/BoxComponent.h"
#include "Components/TextRenderComponent.h"
#include "GameFramework/Actor.h"
#include "MiniGameTeam.generated.h"

DECLARE_LOG_CATEGORY_EXTERN(LogMiniGameTeam, All, All)

UCLASS(Abstract)
class PORTFOLIO_API AMiniGameTeam : public AActor
{
	GENERATED_BODY()


protected:

	AMiniGameTeam();

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Default|Components", meta = (AllowPrivateAccess))
	TObjectPtr<USceneComponent> Root;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Default|Components", meta = (AllowPrivateAccess))
	TObjectPtr<UBoxComponent> TeamAObjectComponent;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Default|Components", meta = (AllowPrivateAccess))
	TObjectPtr<UTextRenderComponent> TextRenderTeamA;


	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Default|Components", meta = (AllowPrivateAccess))
	TObjectPtr<UBoxComponent> TeamBObjectComponent;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Default|Components", meta = (AllowPrivateAccess))
	TObjectPtr<UTextRenderComponent> TextRenderTeamB;


	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Default|Game", meta = (AllowPrivateAccess))
	TObjectPtr<UStaticMeshComponent> Sphere;



	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Default|Spawn", meta = (AllowPrivateAccess))
	TSubclassOf<AAI_PortfolioChar> PortfolioChar;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Default|Spawn", meta = (AllowPrivateAccess))
	UMaterialInstance* ColorTeamA;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Default|Spawn", meta = (AllowPrivateAccess))
	UMaterialInstance* ColorTeamB;

	UPROPERTY()
	int32 TeamAScore = 0;
	UPROPERTY()
	int32 TeamBScore = 0;

public:
	/*
	 *  int Command   : command A = 0 ; command B = 1;
	 *	int TypeClass : Mage = 0; Warrior = 1; Rogue =2;
	 */
	 //UFUNCTION(Unreliable,Server,BlueprintCallable )
	UFUNCTION(BlueprintCallable)
	void ConstructorTeam(const int Command, const  int TypeClass);

	UBoxComponent* GetTeamAPlace() const { return TeamAObjectComponent; }
	UBoxComponent* GetTeamBPlace() const { return TeamBObjectComponent; }
	UStaticMeshComponent* GetSphere() const { return Sphere; };
	UTextRenderComponent* GetTextTeamA() const { return TextRenderTeamA; }
	UTextRenderComponent* GetTextTeamB() const { return TextRenderTeamB; }


	void AddScoreTeamA() { GetTextTeamA()->SetText(FText::FromString(FString::FromInt(TeamAScore++))); }
	void AddScoreTeamB() { GetTextTeamB()->SetText(FText::FromString(FString::FromInt(TeamBScore++))); }

};
