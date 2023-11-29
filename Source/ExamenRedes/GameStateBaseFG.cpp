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
	DOREPLIFETIME(AGameStateBaseFG, DeadPlayersTimer);
	DOREPLIFETIME(AGameStateBaseFG, DeadPlayers);
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

void AGameStateBaseFG::IncrementDeadPlayers()
{
	DeadPlayers++;
	if (DeadPlayers >= PlayersInGame.Num())
	{
		ReduceDeadPlayersTimer();
	}
}

void AGameStateBaseFG::StopAndReturnPlayers()
{
	PlayerVictoryUI();
	for (AExamenRedesCharacter* Player : PlayersInGame)
	{
		Player->DesactiveInput();
	}
	ReturnMenu();
}

void AGameStateBaseFG::TeleportPlayers()
{
	DisableStarTimerUI();
	for (int32 i = 0; i < PlayersInGame.Num(); i++)
	{
		PlayersInGame[i]->SetActorTransform(Targets[i]);
		//APlayerController* PlayerController = UGameplayStatics::GetPlayerController(PlayersInGame[i],i);
		PlayersInGame[i]->DesactiveInput();
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

void AGameStateBaseFG::CheckDeadPlayers()
{
	FString PlayersDeadString = FString::Printf(TEXT("Players Dead: %d"), DeadPlayers);
	GEngine->AddOnScreenDebugMessage(-1,5.0f,FColor::Orange, PlayersDeadString);
	AllPlayersDeadUI();
	ReturnMenu();
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

void AGameStateBaseFG::ReduceDeadPlayersTimer()
{
	GetWorldTimerManager().SetTimer(TimerHandle,this, &AGameStateBaseFG::ReduceDeadPlayersTimerHandle,1, true);
}

void AGameStateBaseFG::ReduceDeadPlayersTimerHandle()
{
	DeadPlayersTimer--;
	if (DeadPlayersTimer <= 0)
	{
		GetWorldTimerManager().ClearTimer(TimerHandle);
		DeadPlayersTimer = 0;
		CheckDeadPlayers();
	}
}

void AGameStateBaseFG::ActivateInputs()
{
	for (int32 i = 0; i<PlayersInGame.Num(); i++)
	{
		APlayerController* PlayerController = UGameplayStatics::GetPlayerController(PlayersInGame[i],i);
		PlayersInGame[i]->ActiveInput();
	}
	DisableGoTimerUI();
}

void AGameStateBaseFG::ReturnMenu()
{
	ReturnMenuUI();
	GetWorldTimerManager().SetTimer(TimerHandle,this, &AGameStateBaseFG::ReturnMenuHandle, 1, true);
}

void AGameStateBaseFG::ReturnMenuHandle()
{
	ReturnMenuTimer--;
	if (ReturnMenuTimer <= 0)
	{
		GetWorldTimerManager().ClearTimer(TimerHandle);
		ReturnMenuTimer = 0;
		for (AExamenRedesCharacter* Player: PlayersInGame)
		{
			Player->DestroyPlayer();
		}
		FString Menu = TEXT("Menu");
		UGameplayStatics::OpenLevel(GetWorld(), FName(*Menu), true);
	}
}

void AGameStateBaseFG::OnRep_StartTimer()
{
}

void AGameStateBaseFG::OnRep_DeadPlayersTimer()
{
}

void AGameStateBaseFG::OnRep_ReturnMenuTimer()
{
}

