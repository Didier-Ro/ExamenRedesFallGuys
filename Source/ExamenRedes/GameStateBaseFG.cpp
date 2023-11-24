// Fill out your copyright notice in the Description page of Project Settings.
#include "GameStateBaseFG.h"

#include <string>

#include "Engine/TargetPoint.h"
#include "Kismet/GameplayStatics.h"

AGameStateBaseFG::AGameStateBaseFG()
{
	
}

void AGameStateBaseFG::BeginPlay()
{
	Super::BeginPlay();
	
	GetTargetPointsPositions();
	GetWorldTimerManager().SetTimer(TimerHandle,this, &AGameStateBaseFG::ReduceTime, 1.0f, true);
}

void AGameStateBaseFG::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
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
	for (int32 i = 0; i < PlayersInGame.Num(); i++)
	{
		PlayersInGame[i]->SetActorTransform(Targets[i]);
	}
}

void AGameStateBaseFG::PlayerConnect()
{
	PlayerCount++;
	CheckPlayers();
}

void AGameStateBaseFG::CheckPlayers()
{
	FString PlayerString = FString::Printf(TEXT("Players: %d"), PlayerCount);
	GEngine->AddOnScreenDebugMessage(-1,5.0f,FColor::Blue, PlayerString);
	if (PlayerCount >= MaxPlayers)
	{
		StartGameTimer = 10;
	}
}

void AGameStateBaseFG::ReduceTime()
{
	StartGameTimer--;
	if (StartGameTimer <= 0)
	{
		GetPlayers();
	}
}

