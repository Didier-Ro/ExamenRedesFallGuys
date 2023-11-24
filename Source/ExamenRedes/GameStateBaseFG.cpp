// Fill out your copyright notice in the Description page of Project Settings.
#include "GameStateBaseFG.h"

#include <string>

#include "Engine/TargetPoint.h"
#include "Kismet/GameplayStatics.h"
#include "Net/UnrealNetwork.h"

AGameStateBaseFG::AGameStateBaseFG()
{
	
}

void AGameStateBaseFG::BeginPlay()
{
	Super::BeginPlay();
	
	GetTargetPointsPositions();
	GetWorldTimerManager().SetTimer(TimerHandle,this, &AGameStateBaseFG::ReduceStartTime, 1.0f, true);
}

void AGameStateBaseFG::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
}

void AGameStateBaseFG::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME(AGameStateBaseFG, StartGameTimer);
	DOREPLIFETIME(AGameStateBaseFG, GoTimer);
}

void AGameStateBaseFG::GetTargetPointsPositions()
{
	UWorld* World = GetWorld();
	TArray<AActor*> TargetPoints;

	UGameplayStatics::GetAllActorsOfClass(World, ATargetPoint::StaticClass(), TargetPoints);

	for (AActor* TargetPoint : TargetPoints)
	{
		ATargetPoint* MyTargetPoint = Cast<ATargetPoint>(TargetPoint);
		if (MyTargetPoint)
		{
			Targets.Add(MyTargetPoint->GetTransform());
		}
	}
}

void AGameStateBaseFG::GetPlayers()
{
	GetWorldTimerManager().ClearTimer(TimerHandle);
	StartGameTimer = 0;
	UWorld* World = GetWorld();
	if (World)
	{
		TArray<AActor*> Players;
		UGameplayStatics::GetAllActorsOfClass(World, AExamenRedesCharacter::StaticClass(),Players);

		for (AActor* Player : Players)
		{
			AExamenRedesCharacter* MyPlayer = Cast<AExamenRedesCharacter>(Player);
			if (MyPlayer)
			{
				PlayersInGame.Add(MyPlayer);
			}
		}
	}
	TeleportPlayers();
}

void AGameStateBaseFG::TeleportPlayers()
{
	DisableStarTimerUI();
	for (int32 i = 0; i < PlayersInGame.Num(); i++)
	{
		PlayersInGame[i]->SetActorTransform(Targets[i]);
		APlayerController* PlayerController = UGameplayStatics::GetPlayerController(PlayersInGame[i],i);
		PlayersInGame[i]->DisableInput(PlayerController);
	}
	ReduceGoTimerHandle();
}

void AGameStateBaseFG::PlayerConnect()
{
	PlayerCount++;
	CheckPlayers();
}

void AGameStateBaseFG::CheckPlayers()
{
	if (PlayerCount >= MaxPlayers)
	{
		StartGameTimer = 10;
	}
}

void AGameStateBaseFG::ReduceStartTime()
{
	StartGameTimer--;
	if (StartGameTimer <= 0)
	{
		GetPlayers();
	}
}

void AGameStateBaseFG::ReduceGoTimerHandle()
{
	AppearGoTimerUI();
	GetWorldTimerManager().SetTimer(TimerHandle, this, &AGameStateBaseFG::ReduceGoTimer, 1.0f,true);
}

void AGameStateBaseFG::ReduceGoTimer()
{
	GoTimer--;
	if (GoTimer <= 0)
	{
		GetWorldTimerManager().ClearTimer(TimerHandle);
		GoTimer = 0;
		ActivateInputs();
	}
}

void AGameStateBaseFG::ActivateInputs()
{
	for (int32 i = 0; i<PlayersInGame.Num(); i++)
	{
		APlayerController* PlayerController = UGameplayStatics::GetPlayerController(PlayersInGame[i],i);
		PlayersInGame[i]->EnableInput(PlayerController);
	}
	DisableGoTimerUI();
}

void AGameStateBaseFG::OnRep_StartTimer()
{
}

