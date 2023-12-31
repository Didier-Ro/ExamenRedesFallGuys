// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Doors.h"
#include "GameFramework/Actor.h"
#include "Doors_Controller.generated.h"

UCLASS()
class EXAMENREDES_API ADoors_Controller : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ADoors_Controller();

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<ADoors*> Doorses;

	UPROPERTY(EditAnywhere)
	int32 DoorIndex;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void SelectRandomDoor();

};
