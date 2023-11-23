// Fill out your copyright notice in the Description page of Project Settings.
#include "GameStateBaseFG.h"

#include "Engine/TargetPoint.h"
#include "Kismet/GameplayStatics.h"

AGameStateBaseFG::AGameStateBaseFG()
{
	
}

void AGameStateBaseFG::BeginPlay()
{
	Super::BeginPlay();
	
	GetTargetPointsPositions();
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

	PrintTargets();
}

void AGameStateBaseFG::GetPlayers()
{
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

void AGameStateBaseFG::PrintTargets()
{
	for (FTransform TargetPoint : Targets)
	{
		FString TransformString = TargetPoint.ToString();
		GEngine->AddOnScreenDebugMessage(-1,10.0f,FColor::Blue, TransformString);
	}
}

void AGameStateBaseFG::TeleportPlayers()
{
	for (int32 i = 0; i < PlayersInGame.Num(); i++)
	{
		PlayersInGame[i]->SetActorTransform(Targets[i]);
	}
}

