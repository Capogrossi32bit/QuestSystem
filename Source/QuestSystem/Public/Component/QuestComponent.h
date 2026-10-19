#pragma once
//5. Quest component
#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "QuestTypes.h"
#include "QuestComponent.generated.h"

class UQuestDefinition;

// 17. Event Dispatchers del quest component
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(
	FOnQuestStarted,
	FQuestRuntime, QuestData
);

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(
	FOnQuestProgressChanged,
	FQuestRuntime, QuestData
);

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(
	FOnQuestCompleted,
	FQuestRuntime, QuestData
);


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class QUESTSYSTEM_API UQuestComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UQuestComponent();

	// PROPERTIES
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<FQuestRuntime> ActiveQuests;

	UPROPERTY(BlueprintAssignable, Category = "QuestSystem|UI")
	FOnQuestStarted OnQuestStarted;

	UPROPERTY(BlueprintAssignable, Category = "QuestSystem|UI")
	FOnQuestProgressChanged OnQuestProgressChanged;

	UPROPERTY(BlueprintAssignable, Category = "QuestSystem|UI")
	FOnQuestCompleted OnQuestCompleted;

	// FUNCTIONS
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	//6. Funcion FindQuestByID
	UFUNCTION(BlueprintCallable, Category= "QuestSystem", meta = (ReturnDisplayName = "Found"))
	bool FindQuestByID(FName QuestID, FQuestRuntime& QuestData, int32& QuestIndex) const;

	//7. Funcion AddQuest
	UFUNCTION(BlueprintCallable, Category = "QuestSystem")
	void AddQuest(UQuestDefinition* QuestDefinition);
	
	//14. Funcion HandleGameplayObjective
	UFUNCTION(BlueprintCallable, Category = "QuestSystem")
	void HandleGameplayObjective(EQuestObjectiveType ObjectiveType, FName TargetID, int32 Amount);

	//15. Funcion UpdateObjectiveProgress
	UFUNCTION(BlueprintCallable, Category = "QuestSystem")
	void UpdateObjectiveProgress(int32 QuestIndex, int32 ObjectiveIndex, int32 Amount);

	//16. Funcion CheckQuestCompleted
	UFUNCTION(BlueprintCallable, Category = "QuestSystem")
	void CheckQuestCompleted(int32 QuestIndex);


protected:

	// Called when the game starts
	virtual void BeginPlay() override;

};
