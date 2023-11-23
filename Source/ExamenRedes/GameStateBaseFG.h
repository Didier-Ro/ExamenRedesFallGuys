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
	AGameStateBaseFG();

	UFUNCTION(BlueprintCallable)
	void GetTargetPointsPositions();

	UFUNCTION(BlueprintCallable)
	void GetPlayers();

	UFUNCTION()
	void PrintTargets();

	UFUNCTION()
	void TeleportPlayers();

protected:
	virtual void BeginPlay() override;
};
