// Fill out your copyright notice in the Description page of Project Settings.


#include "Gates.h"
#include "PingPongBall.h"
#include "PingPongGameModeBase.h"
#include "Kismet/GameplayStatics.h"
#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"
#include "PingPongGameState.h"

// Sets default values
AGates::AGates()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	RootComponent = Mesh;

	Gate1Collision = CreateDefaultSubobject<UBoxComponent>(TEXT("Gate 1 Collision"));
	Gate1Collision->SetupAttachment(RootComponent);
	Gate1Collision->OnComponentBeginOverlap.AddDynamic(this, &AGates::OnGate1OverlapBegin);

	Gate2Collision = CreateDefaultSubobject<UBoxComponent>(TEXT("Gate 2 Collision"));
	Gate2Collision->SetupAttachment(RootComponent);
	Gate2Collision->OnComponentBeginOverlap.AddDynamic(this, &AGates::OnGate2OverlapBegin);

	Gate1Collision->SetIsReplicated(true);
	SetReplicates(true);

	Gate2Collision->SetIsReplicated(true);
	SetReplicates(true);
}

// Called when the game starts or when spawned
void AGates::BeginPlay()
{
	Super::BeginPlay();

	
}

// Called every frame
void AGates::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	

}

void AGates::OnGate1OverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	APingPongGameState* state = Cast<APingPongGameState>(UGameplayStatics::GetGameState(GetWorld()));
	
	APingPongBall* ball = Cast<APingPongBall>(OtherActor);
	if(ball)
	{
		if(player2 && player1)
			state->GoalScore1();
	}
}

void AGates::OnGate2OverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	APingPongGameState* state = Cast<APingPongGameState>(UGameplayStatics::GetGameState(GetWorld()));

	APingPongBall* ball = Cast<APingPongBall>(OtherActor);
	if (ball)
	{
		if (player1 && player2)
			state->GoalScore2();
	}
}
