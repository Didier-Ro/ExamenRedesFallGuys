// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ExamenRedesCharacter.h"
#include "GameFramework/GameStateBase.h"
#include "GameStateBaseFG.generated.h"

/**
 * 
 */
UCLASS()
class EXAMENREDES_API AGameStateBaseFG : public AGameStateBase
{
	GENERATED_BODY()

	UPROPERTY()
	TArray<FTransform> Targets;

	UPROPERTY()
	TArray<AExamenRedesCharacter*> PlayersInGame;

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 PlayerCount;

	UPROPERTY(EditAnywhere)
	int32 MaxPlayers;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 StartGameTimer;

	FTimerHandle TimerHandle;
public:
	AGameStateBaseFG();

	UFUNCTION(BlueprintCallable)
	void GetTargetPointsPositions();

	UFUNCTION(BlueprintCallable)
	void GetPlayers();

	UFUNCTION()
	void TeleportPlayers();

	UFUNCTION(BlueprintCallable)
	void PlayerConnect();

	UFUNCTION()
	void CheckPlayers();

	UFUNCTION()
	void ReduceTime();

protected:
	virtual void BeginPlay() override;

	virtual void Tick(float DeltaSeconds) override;
};
