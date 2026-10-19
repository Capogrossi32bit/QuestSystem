// Fill out your copyright notice in the Description page of Project Settings.


#include "QuestGameState.h"

void AQuestGameState::ReportGameplayObjective(EQuestObjectiveType ObjectiveType, FName TargetID, int32 Amount)
{
	if (Amount <= 0)
	{
		return;
	}

	OnGameplayObjectiveEvent.Broadcast(ObjectiveType, TargetID, Amount);
}
