// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Piso.h"
#include "GameFramework/Actor.h"
#include "Fall_Controller.generated.h"

UCLASS()
class EXAMENREDES_API AFall_Controller : public AActor
{
	GENERATED_BODY()

	
public:	
	// Sets default values for this actor's properties
	AFall_Controller();
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<APiso*> Pisos;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 PisoIndex;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
