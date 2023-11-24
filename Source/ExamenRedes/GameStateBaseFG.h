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

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Replicated)
	int32 StartGameTimer;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Replicated)
	int32 GoTimer;

	FTimerHandle TimerHandle;
public:
	AGameStateBaseFG();

	UFUNCTION(BlueprintCallable)
	void GetTargetPointsPositions();

	UFUNCTION(BlueprintCallable)
	void GetPlayers();

	UFUNCTION(BlueprintCallable)
	void PlayerConnect();

	UFUNCTION(BlueprintImplementableEvent)
	void AppearGoTimerUI();

	UFUNCTION(BlueprintImplementableEvent)
	void DisableGoTimerUI();

	UFUNCTION(BlueprintImplementableEvent)
	void DisableStarTimerUI();

private:
	UFUNCTION()
	void TeleportPlayers();
	
	UFUNCTION()
	void CheckPlayers();
	
	UFUNCTION()
	void ReduceStartTime();

	UFUNCTION()
	void ReduceGoTimerHandle();

	UFUNCTION()
	void ReduceGoTimer();

	UFUNCTION()
	void ActivateInputs();

	UFUNCTION()
	void OnRep_StartTimer();

protected:
	virtual void BeginPlay() override;

	virtual void Tick(float DeltaSeconds) override;

	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
};
