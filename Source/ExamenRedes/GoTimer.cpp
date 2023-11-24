// Fill out your copyright notice in the Description page of Project Settings.
#include "GoTimer.h"
#include "GameStateBaseFG.h"

void UGoTimer::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);

	if (GetWorld() != nullptr)
	{
		AGameStateBaseFG* GameStateBaseFg = Cast<AGameStateBaseFG>(GetWorld()->GetGameState());

		if (GameStateBaseFg)
		{
			WGoTimerValue = GameStateBaseFg->GoTimer;
		}
	}
}
