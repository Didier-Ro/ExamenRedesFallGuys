// Fill out your copyright notice in the Description page of Project Settings.
#include "StartGameWidget.h"

#include "GameStateBaseFG.h"

void UStartGameWidget::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);
	
	if (GetWorld() != nullptr)
	{
		AGameStateBaseFG* GameStateBaseFg = Cast<AGameStateBaseFG>(GetWorld()->GetGameState());

		if (GameStateBaseFg)
		{
			WTimerValue = GameStateBaseFg->StartGameTimer;
		}
	}
}
