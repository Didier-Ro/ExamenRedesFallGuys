// Fill out your copyright notice in the Description page of Project Settings.


#include "Doors_Controller.h"

// Sets default values
ADoors_Controller::ADoors_Controller()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ADoors_Controller::BeginPlay()
{
	Super::BeginPlay();

	SelectRandomDoor();
}

// Called every frame
void ADoors_Controller::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ADoors_Controller::SelectRandomDoor()
{
	DoorIndex = FMath::RandRange(0, Doorses.Num()-1);

	Doorses[DoorIndex]->ActivarFisica();
}

