// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/BoxComponent.h"
#include "GameFramework/Actor.h"
#include "Gates.generated.h"

UCLASS()
class PINGPONG_API AGates : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AGates();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditDefaultsOnly)
	class UStaticMeshComponent* Mesh;

	UPROPERTY(EditDefaultsOnly)
	UBoxComponent* Gate1Collision;

	UPROPERTY(EditDefaultsOnly)
	UBoxComponent* Gate2Collision;

	UPROPERTY(BlueprintReadOnly)
	class APingPongPlayerController* player1;
	UPROPERTY(BlueprintReadOnly)
	class APingPongPlayerController* player2;
	
	UFUNCTION()
	void OnGate1OverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	UFUNCTION()
	void OnGate2OverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
};
