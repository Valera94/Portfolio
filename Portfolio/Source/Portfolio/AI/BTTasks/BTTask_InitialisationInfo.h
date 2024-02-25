// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Tasks/BTTask_BlackboardBase.h"
#include "Portfolio/AI/MiniGameTeam.h"
#include "BTTask_InitialisationInfo.generated.h"

/**
 * 
 */
UCLASS()
class PORTFOLIO_API UBTTask_InitialisationInfo : public UBTTask_BlackboardBase
{
	GENERATED_BODY()

public:

	UBTTask_InitialisationInfo();

	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	FBlackboardKeySelector BlackboardKeyPositionA;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FBlackboardKeySelector BlackboardKeyPositionB;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FBlackboardKeySelector SelectedActor;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Settings")
	TSubclassOf<AMiniGameTeam> FindClassMiniGameTeam;

	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
	virtual void InitializeFromAsset(UBehaviorTree& Asset) override;

};
