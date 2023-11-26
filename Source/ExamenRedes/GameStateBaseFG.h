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


public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<AExamenRedesCharacter*> PlayersInGame;
	
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	int32 PlayerCount;

	UPROPERTY(EditAnywhere)
	int32 MaxPlayers;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, ReplicatedUsing = OnRep_StartTimer)
	int32 StartGameTimer;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Replicated)
	int32 GoTimer;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, ReplicatedUsing = OnRep_ReturnMenuTimer)
	int32 ReturnMenuTimer;

	FTimerHandle TimerHandle;

	UPROPERTY(EditAnywhere, Replicated,BlueprintReadWrite)
	int32 DeadPlayers;

	UPROPERTY(EditAnywhere,Replicated, BlueprintReadWrite)
	bool bAllPlayersDead;

	UPROPERTY(EditAnywhere, BlueprintReadWrite,  ReplicatedUsing = OnRep_DeadPlayersTimer)
	int32 DeadPlayersTimer;
	
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

	UFUNCTION(BlueprintImplementableEvent)
	void AllPlayersDeadUI();

	UFUNCTION(BlueprintImplementableEvent)
	void ReturnMenuUI();
	
	UFUNCTION(BlueprintCallable)
	void IncrementDeadPlayers();

	UFUNCTION( BlueprintImplementableEvent)
	void PlayerVictoryUI();

	UFUNCTION(BlueprintCallable)
	void StopAndReturnPlayers();

private:
	UFUNCTION()
	void TeleportPlayers();
	
	UFUNCTION()
	void CheckPlayers();

	UFUNCTION()
	void CheckDeadPlayers();
	
	UFUNCTION()
	void ReduceStartTime();

	UFUNCTION()
	void ReduceGoTimerHandle();

	UFUNCTION()
	void ReduceGoTimer();

	UFUNCTION()
	void ReduceDeadPlayersTimer();

	UFUNCTION()
	void ReduceDeadPlayersTimerHandle();

	UFUNCTION()
	void ActivateInputs();

	UFUNCTION()
	void ReturnMenu();

	UFUNCTION()
	void ReturnMenuHandle();

	UFUNCTION()
	void OnRep_StartTimer();

	UFUNCTION()
	void OnRep_DeadPlayersTimer();

	UFUNCTION()
	void OnRep_ReturnMenuTimer();

protected:
	virtual void BeginPlay() override;

	virtual void Tick(float DeltaSeconds) override;

	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
};
