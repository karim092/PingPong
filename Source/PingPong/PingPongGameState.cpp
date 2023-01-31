// Fill out your copyright notice in the Description page of Project Settings.


#include "PingPongGameState.h"
#include "Net/UnrealNetwork.h"

void APingPongGameState::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(APingPongGameState, Score_1);
	DOREPLIFETIME(APingPongGameState, Score_2);
}

bool APingPongGameState::Server_GoalScore1_Validate()
{
	return true;
}

bool APingPongGameState::Server_GoalScore2_Validate()
{
	return true;
}

void APingPongGameState::Server_GoalScore1_Implementation()
{
	Score_1 += 1;
}

void APingPongGameState::Server_GoalScore2_Implementation()
{
	Score_2 += 1;
}