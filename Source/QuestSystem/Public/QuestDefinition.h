#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "../Source/QuestSystem/Public/QuestTypes.h"
#include "QuestDefinition.generated.h"

UCLASS()
class QUESTSYSTEM_API UQuestDefinition : public UPrimaryDataAsset
{
	GENERATED_BODY()
	
public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "QuestSystem")
	FName QuestID = NAME_None;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "QuestSystem")
	FText QuestName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "QuestSystem")
	FText Description;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "QuestSystem")
	TArray<FQuestObjective> Objectives;

};
