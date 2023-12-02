// Fill out your copyright notice in the Description page of Project Settings.


#include "Piso.h"

#include "ExamenRedesCharacter.h"

// Sets default values
APiso::APiso()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	bReplicates = true;

	MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	RootComponent = MeshComponent;

	BoxComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxComponent"));
	BoxComponent->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	BoxComponent->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap);
	BoxComponent->SetupAttachment(MeshComponent);
}

// Called when the game starts or when spawned
void APiso::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void APiso::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void APiso::NotifyActorBeginOverlap(AActor* OtherActor)
{
	Super::NotifyActorBeginOverlap(OtherActor);
	AExamenRedesCharacter* Character = Cast<AExamenRedesCharacter>(OtherActor);
	if (Character)
	{
		MeshComponent->SetSimulatePhysics(true);
	}
}

void APiso::DesactivePlayerDetection()
{
	BoxComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);
}