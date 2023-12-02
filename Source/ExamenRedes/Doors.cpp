// Fill out your copyright notice in the Description page of Project Settings.


#include "Doors.h"

// Sets default values
ADoors::ADoors()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	bReplicates = true;

	StaticMeshComponent=CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	RootComponent=StaticMeshComponent;
}

// Called when the game starts or when spawned
void ADoors::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ADoors::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ADoors::ActivarFisica()
{
	StaticMeshComponent->SetSimulatePhysics(true);
}

