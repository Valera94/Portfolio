// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_InitialisationInfo.h"

#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/BTFunctionLibrary.h"
#include "Kismet/GameplayStatics.h"

UBTTask_InitialisationInfo::UBTTask_InitialisationInfo()
{
	NodeName = "Node for initialisation base variable for need information";
}


EBTNodeResult::Type UBTTask_InitialisationInfo::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	UBlackboardComponent* MyBlackboard = OwnerComp.GetBlackboardComponent();

	TArray<AActor*> FindedActors;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AMiniGameTeam::StaticClass(), FindedActors);

	for (auto i : FindedActors)
	{
		if (Cast<AMiniGameTeam>(i))
		{
			
			OwnerComp.GetBlackboardComponent()->SetValueAsObject(SelectedActor.SelectedKeyName, i);
			OwnerComp.GetBlackboardComponent()->SetValueAsVector(BlackboardKeyPositionA.SelectedKeyName, Cast<AMiniGameTeam>(i)->GetTeamAPlace()->GetComponentLocation());
			OwnerComp.GetBlackboardComponent()->SetValueAsVector(BlackboardKeyPositionB.SelectedKeyName, Cast<AMiniGameTeam>(i)->GetTeamBPlace()->GetComponentLocation());

			FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
			return EBTNodeResult::Succeeded;
		}
	}
	return EBTNodeResult::Failed;
}

void UBTTask_InitialisationInfo::InitializeFromAsset(UBehaviorTree& Asset)
{
	Super::InitializeFromAsset(Asset);

}

