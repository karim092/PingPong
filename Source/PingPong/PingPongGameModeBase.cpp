// Copyright Epic Games, Inc. All Rights Reserved.


#include "PingPongGameModeBase.h"
#include "PingPongPlayerController.h"
#include "PingPongPlayerPawn.h"
#include "Kismet/GameplayStatics.h"
#include "Gates.h"
#include "Net/UnrealNetwork.h"

APingPongGameModeBase::APingPongGameModeBase()
{
	DefaultPawnClass = APingPongPlayerPawn::StaticClass();
	PlayerControllerClass = APingPongPlayerController::StaticClass();
}

void APingPongGameModeBase::BeginPlay()
{
	Super::BeginPlay();
}

void APingPongGameModeBase::PostLogin(APlayerController* NewPlayer)
{
	Super::PostLogin(NewPlayer);
	UWorld* world = GetWorld();

	TArray<AActor*> gates;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AGates::StaticClass(), gates);
	AGates* gate1 = Cast<AGates>(gates[0]);
	
	if (world && (!Player1Start || !Player2Start))
	{
		TArray<AActor*> foundActors;
		UGameplayStatics::GetAllActorsOfClass(GetWorld(), APlayerStart::StaticClass(), foundActors);
		if (foundActors.Num() > 0)
			Player1Start = (APlayerStart*)foundActors[0];
		if (foundActors.Num() > 1)
			Player2Start = (APlayerStart*)foundActors[1];
	}
	APingPongPlayerController* currPlayer = NULL;
	APlayerStart* startPos = NULL;
	if (Player1 == NULL)
	{
		Player1 = (APingPongPlayerController*)NewPlayer;
		currPlayer = Player1;
		startPos = Player1Start;
		UE_LOG(LogTemp, Warning, TEXT("PingPongGameMode: Init player 1"));
		if(gates[0])
		{
			gate1->player1 = Player1;
		}
	}
	else if (Player2 == NULL && NewPlayer != Player1)
	{
		Player2 = (APingPongPlayerController*)NewPlayer;
		currPlayer = Player2;
		startPos = Player2Start;
		UE_LOG(LogTemp, Warning, TEXT("PingPongGameMode: Init player 2"));
		if(gates[0])
		{
			gate1->player2 = Player2;
		}
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("PingPongGameMode: There are already two players in the game.New connections are not possible"));
			return;
	}
	APingPongPlayerPawn* newPawn = Cast<APingPongPlayerPawn>(NewPlayer->GetPawn());

	if (!newPawn)
	{
		newPawn =
			world->SpawnActor<APingPongPlayerPawn>(DefaultPawnClass);
	}
	if (startPos && newPawn)
	{
		newPawn->SetActorLocation(startPos->GetActorLocation());
		newPawn->SetActorRotation(startPos->GetActorRotation());
		NewPlayer->SetPawn(newPawn);
		currPlayer->SetStartTransfrorm(startPos->GetActorTransform());
		currPlayer->Initialize();
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("Start position not setted in PingPongGameMode!"));
	}
}




