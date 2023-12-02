// Fill out your copyright notice in the Description page of Project Settings.


#include "Fall_Controller.h"

#include "Kismet/GameplayStatics.h"
*
// Sets default values
AFall_Controller::AFall_Controller()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AFall_Controller::BeginPlay()
{
	Super::BeginPlay();
	
	PisoIndex = FMath::RandRange(0,Pisos.Num() - 1);

	Pisos[PisoIndex]->DesactivePlayerDetection();
}

// Called every frame
void AFall_Controller::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

