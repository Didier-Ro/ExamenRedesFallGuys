// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Doors.generated.h"

UCLASS()
class EXAMENREDES_API ADoors : public AActor
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, Category="components")
	UStaticMeshComponent* StaticMeshComponent;

	

	
	
public:	
	// Sets default values for this actor's properties
	ADoors();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION()
	void ActivarFisica();

};
