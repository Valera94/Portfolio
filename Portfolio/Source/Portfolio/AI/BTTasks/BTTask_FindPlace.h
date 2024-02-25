// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Tasks/BTTask_BlackboardBase.h"
#include "BTTask_FindPlace.generated.h"

/**
 * 
 */
UCLASS()
class PORTFOLIO_API UBTTask_FindPlace : public UBTTask_BlackboardBase
{
	GENERATED_BODY()

public:


	UBTTask_FindPlace();

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FBlackboardKeySelector ActorMiniGameTeam;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FBlackboardKeySelector LocationTeamA;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FBlackboardKeySelector LocationTeamB;
	
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
};
