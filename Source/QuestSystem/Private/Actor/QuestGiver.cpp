#include "Actor/QuestGiver.h"
#include "QuestDefinition.h"
#include "Public/Component/QuestComponent.h"

#include "Components/SceneComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Components/SphereComponent.h"


AQuestGiver::AQuestGiver()
{

	PrimaryActorTick.bCanEverTick = false;
    
    SceneRoot = CreateDefaultSubobject<USceneComponent>(TEXT("SceneRoot"));
    RootComponent = SceneRoot;

    QuestMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("QuestMesh"));
    QuestMesh->SetupAttachment(RootComponent);

    InteractionSphere = CreateDefaultSubobject<USphereComponent>(TEXT("InteractionSphere"));
    InteractionSphere->SetupAttachment(RootComponent);
    InteractionSphere->SetSphereRadius(200.f);
    InteractionSphere->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
    InteractionSphere->SetCollisionResponseToAllChannels(ECR_Ignore);
    InteractionSphere->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap);
}

void AQuestGiver::Interact_Implementation(AActor* Interactor)
{
    if (!IsValid(Interactor) || !IsValid(QuestDefinition))
    {
        return;
    }
    UQuestComponent* QuestComponent = Interactor->FindComponentByClass<UQuestComponent>();

    //Verificar que el componente exista
    if (!IsValid(QuestComponent))
    {
        UE_LOG(LogTemp, Warning, TEXT("El actor no tiene QuestComponent"));
        return;
    }

    //Verificar si hay overlapping
    if (!InteractionSphere->IsOverlappingActor(Interactor))
    {
        return;
    }
    QuestComponent->AddQuest(QuestDefinition);
    UE_LOG(LogTemp, Warning,TEXT("Interaccion con QuestGiver: %s"),*QuestDefinition->QuestID.ToString());

}

// Called when the game starts or when spawned
void AQuestGiver::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AQuestGiver::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}



