// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/BoxComponent.h"
#include "GameFramework/Actor.h"
#include "Piso.generated.h"

UCLASS()
class EXAMENREDES_API APiso : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APiso();

	UPROPERTY(EditAnywhere, Category="Component")
	UStaticMeshComponent* MeshComponent;

	UPROPERTY(EditAnywhere, Category="Component")
	UBoxComponent* BoxComponent;
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual void NotifyActorBeginOverlap(AActor* OtherActor) override;

	void DesactivePlayerDetection();

};
