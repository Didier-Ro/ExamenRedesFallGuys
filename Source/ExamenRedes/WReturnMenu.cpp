// Fill out your copyright notice in the Description page of Project Settings.
#include "WReturnMenu.h"
#include "GameStateBaseFG.h"

void UWReturnMenu::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);

	if (GetWorld() != nullptr)
	{
		AGameStateBaseFG* GameStateBaseFg = Cast<AGameStateBaseFG>(GetWorld()->GetGameState());

		if (GameStateBaseFg)
		{
			MenuTimer = GameStateBaseFg->ReturnMenuTimer;
		}
	}
}
