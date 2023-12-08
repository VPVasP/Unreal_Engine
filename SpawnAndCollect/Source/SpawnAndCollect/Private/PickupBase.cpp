// Fill out your copyright notice in the Description page of Project Settings.


#include "PickupBase.h"

// Sets default values
APickupBase::APickupBase()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	PickupMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Pickup Mesh"));
	RootComponent = PickupMesh;

	PickupMesh->SetSimulatePhysics(true);
}

// Called when the game starts or when spawned
void APickupBase::BeginPlay()
{
	Super::BeginPlay();

}

// Called every frame
void APickupBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void APickupBase::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void APickupBase::OnPickupAction_Implementation()
{
	const FString logString = GetName();
	UE_LOG(LogTemp, Warning, TEXT("Picked up a collectible!!!11 It's %s !!1!"), *logString);

	Destroy();
}
