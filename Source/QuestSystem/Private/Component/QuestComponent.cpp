#include "Component/QuestComponent.h"
#include "QuestDefinition.h"
#include "QuestGameState.h"
#include "Kismet/Gameplaystatics.h"

UQuestComponent::UQuestComponent()
{
	
	PrimaryComponentTick.bCanEverTick = false;
	//Por la consigna, ninguna accion puede ejecutarse desde Tick, asi que lo
	//seteamos en false.
	
}



void UQuestComponent::BeginPlay()
{
	Super::BeginPlay();

	//Castear al gamestate
	AQuestGameState* QuestGameState = Cast<AQuestGameState>(UGameplayStatics::GetGameState(GetWorld()));
	if (IsValid(QuestGameState)) 
	{
		QuestGameState->OnGameplayObjectiveEvent.AddDynamic(this, &UQuestComponent::HandleGameplayObjective);
		
	}
}



void UQuestComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

}

bool UQuestComponent::FindQuestByID(FName QuestID, FQuestRuntime& QuestData, int32& QuestIndex) const
{
	QuestData = FQuestRuntime();
	QuestIndex = INDEX_NONE;


	for (int32 i = 0 ; i < ActiveQuests.Num(); i++)
	{
		if (ActiveQuests[i].QuestID == QuestID)
		{
			QuestData = ActiveQuests[i];
			QuestIndex = i;
			return true;
		}
	}

	return false;
}

void UQuestComponent::AddQuest(UQuestDefinition* QuestDefinition)
{
	if (!IsValid(QuestDefinition)) 
	{
		return;
	}
	FQuestRuntime FoundQuest;
	int32 QuestIndex = INDEX_NONE;

	if (FindQuestByID(QuestDefinition->QuestID, FoundQuest, QuestIndex))
	{
		return;
	}

	FQuestRuntime NewQuest;
	
	NewQuest.QuestID = QuestDefinition->QuestID;
	NewQuest.QuestDefinition = QuestDefinition;
	NewQuest.Objectives = QuestDefinition->Objectives;

	NewQuest.IsActive = true;
	NewQuest.IsCompleted = false;

	//Reiniciar progreso
	for (FQuestObjective& Objective : NewQuest.Objectives)
	{
		Objective.CurrentAmount = 0;
	}

	//Guardar en ActiveQuests
	ActiveQuests.Add(NewQuest);

	//Notificar inicio de mision
	OnQuestStarted.Broadcast(NewQuest);
}

void UQuestComponent::HandleGameplayObjective(EQuestObjectiveType ObjectiveType, FName TargetID, int32 Amount)
{

	if (Amount <= 0)
	{
		return;
	}
	
	for (int32 QuestIndex = 0; QuestIndex < ActiveQuests.Num();QuestIndex++)
	{
		//Recorrer las quests ignorando las inactivas y completas
		if (!ActiveQuests[QuestIndex].IsActive || ActiveQuests[QuestIndex].IsCompleted)
		{
			continue;
		}
		for (int32 ObjectiveIndex = 0; ObjectiveIndex < ActiveQuests[QuestIndex].Objectives.Num();ObjectiveIndex++)
		{
			const FQuestObjective& Objective = ActiveQuests[QuestIndex].Objectives[ObjectiveIndex];
			
			//Si coinciden el tipo de objetivo y el id del objetivo entonces actualizar el progreso
			if (Objective.ObjectiveType == ObjectiveType && Objective.TargetID == TargetID)
			{
				UpdateObjectiveProgress(QuestIndex, ObjectiveIndex, Amount);
				//Si se completa la mision, finalizar el proceso
				if (ActiveQuests[QuestIndex].IsCompleted)
				{
					break;
				}
			}
		}
	}
}

void UQuestComponent::UpdateObjectiveProgress(int32 QuestIndex, int32 ObjectiveIndex, int32 Amount)
{
	// Maneja el caso en que el indice sea invalido para evitar crasheos
	if (!ActiveQuests.IsValidIndex(QuestIndex))
	{
		return;
	}
	// Obtener la quest correspondiente al indice
	FQuestRuntime& Quest = ActiveQuests[QuestIndex];

	// Ignorar las quests inactivas y completas
	if (!Quest.IsActive || Quest.IsCompleted) 
	{
		return;
	}

	// Maneja el caso en que el indice sea invalido para evitar crasheos
	if (!Quest.Objectives.IsValidIndex(ObjectiveIndex))
	{
		return;
	}

	// Ignora edge cases, como enemigos usando numeros negativos o el cero como amount
	if (Amount <= 0) 
	{
		return;
	}

	// Obtiene el objetivo indicado por el indice
	FQuestObjective& Objective = Quest.Objectives[ObjectiveIndex];

	if (Objective.RequiredAmount <= 0 || Objective.CurrentAmount >= Objective.RequiredAmount)
	{
		return;
	}

	// Cambiar el current amount
	Objective.CurrentAmount = FMath::Min(Objective.CurrentAmount + Amount, Objective.RequiredAmount); 
	//Si la suma de amount + current amount es mayor al required amount 
	//entonces tomar el required amount para finalizar la quest

	CheckQuestCompleted(QuestIndex);
	
	// Si la mision esta activa y no está completada, actualizar progreso y 
	// realizar broadcast
	if(ActiveQuests.IsValidIndex(QuestIndex) && ActiveQuests[QuestIndex].IsActive && !ActiveQuests[QuestIndex].IsCompleted)
	{
		OnQuestProgressChanged.Broadcast(ActiveQuests[QuestIndex]);
	}

}

void UQuestComponent::CheckQuestCompleted(int32 QuestIndex)
{
	if (!ActiveQuests.IsValidIndex(QuestIndex)) 
	{
		return;
	}

	FQuestRuntime& Quest = ActiveQuests[QuestIndex];

	if (!Quest.IsActive || Quest.IsCompleted)
	{
		return;
	}

	if (Quest.Objectives.IsEmpty())
	{
		return;
	}

	bool bAllCompleted = true;

	//Recorre el arreglo en busca de una mision que no cumpla la precondicion 
	//CurrentAmount = RequiredAmount, en caso de encontrarlo finaliza la ejecucion
	for (const FQuestObjective& Objective : Quest.Objectives)
	{
		if (Objective.CurrentAmount < Objective.RequiredAmount)
		{
			bAllCompleted = false;
			break;
		}
	}
	//Esto funciona por que inicializamos bAllCompleted = true, en caso de 
	// encontrar algun objetivo incompleto finaliza la ejecucion, en caso 
	// contrario esta condicion sera verdadera
	if (bAllCompleted) 
	{
		Quest.IsCompleted = true;
		Quest.IsActive = false;

		OnQuestCompleted.Broadcast(Quest);
	}
}

