// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameStateBase.h"
#include "PingPongGameState.generated.h"

/**
 * 
 */
UCLASS()
class PINGPONG_API APingPongGameState : public AGameStateBase
{
	GENERATED_BODY()
	
public:

	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	UFUNCTION(Server, Reliable, WithValidation)
		void Server_GoalScore1();

	UFUNCTION(Server, Reliable, WithValidation)
		void Server_GoalScore2();

	UFUNCTION()
		void GoalScore1() { Server_GoalScore1(); };

	UFUNCTION()
		void GoalScore2() { Server_GoalScore2(); };

	UPROPERTY(BlueprintReadOnly, Replicated)
		int Score_1 = 0;
	UPROPERTY(BlueprintReadOnly, Replicated)
		int Score_2 = 0;
};
