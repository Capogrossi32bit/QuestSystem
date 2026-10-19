#include "Actor/AQuestObjectiveActor.h"
#include "QuestGameState.h"

#include "Public/Component/QuestComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Components/SphereComponent.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
AAQuestObjectiveActor::AAQuestObjectiveActor()
{
	PrimaryActorTick.bCanEverTick = false;

    Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
    RootComponent = Mesh;

    InteractionSphere = CreateDefaultSubobject<USphereComponent>(TEXT("InteractionSphere"));
    InteractionSphere->SetupAttachment(RootComponent);
    InteractionSphere->SetSphereRadius(150.f);
    InteractionSphere->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
    InteractionSphere->SetCollisionResponseToAllChannels(ECR_Ignore);
    InteractionSphere->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap);
    InteractionSphere->SetGenerateOverlapEvents(true);
    InteractionSphere->OnComponentBeginOverlap.AddDynamic(this,&AAQuestObjectiveActor::OnSphereBeginOverlap);
}

void AAQuestObjectiveActor::ReportObjective()
{
    if (bAlreadyReported || Amount <= 0)
    {
        return;
    }

    AQuestGameState* QuestGameState = Cast<AQuestGameState>(UGameplayStatics::GetGameState(GetWorld()));

    if (!IsValid(QuestGameState))
    {
        return;
    }

    QuestGameState->ReportGameplayObjective(ObjectiveType, TargetID, Amount);

    UE_LOG(LogTemp, Warning, TEXT("Objective reported: %s"), *TargetID.ToString());
}

void AAQuestObjectiveActor::OnSphereBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, 
     UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
    if (ObjectiveType != EQuestObjectiveType::ReachLocation)
    {
        return;
    }

    if (!IsValid(OtherActor))
    {
        return;
    }

    UQuestComponent* QuestComponent = OtherActor->FindComponentByClass<UQuestComponent>();

    if (!IsValid(QuestComponent))
    {
        return;
    }

    ReportObjective();

}

void AAQuestObjectiveActor::Interact_Implementation(AActor* Interactor)
{
    UE_LOG(LogTemp, Warning,
        TEXT("Interact recibido por: %s"),
        *GetName()
    );

    if(!IsValid(Interactor) || !InteractionSphere->IsOverlappingActor(Interactor))
    {
        return;
    }

    if (ObjectiveType == EQuestObjectiveType::Interact || ObjectiveType == EQuestObjectiveType::Collect
        || ObjectiveType == EQuestObjectiveType::Kill)
    {
        ReportObjective();
        if (ObjectiveType == EQuestObjectiveType::Collect || ObjectiveType == EQuestObjectiveType::Kill)
        {
            Destroy();
        }
    }
}

// Called when the game starts or when spawned
void AAQuestObjectiveActor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AAQuestObjectiveActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}





