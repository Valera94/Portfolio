// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "BehaviorTree/BehaviorTreeTypes.h"
#include "BehaviorTree/BlackboardData.h"
#include "PortfolioAIController.generated.h"

PORTFOLIO_API DECLARE_LOG_CATEGORY_EXTERN(LogPortfolioAI, All, All);

/**
 * 
 */
UCLASS()
class PORTFOLIO_API APortfolioAIController : public AAIController
{
	GENERATED_BODY()

public:

	virtual void OnPossess(APawn* InPawn) override;

protected:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI", meta = (AllowPrivateAccess))
	TObjectPtr<UBehaviorTree> Tree;

	UPROPERTY(EditAnywhere,BlueprintReadOnly)
	FBlackboardKeySelector MyBlackboardKey;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	UBlackboardData* BlackBoardData;
};