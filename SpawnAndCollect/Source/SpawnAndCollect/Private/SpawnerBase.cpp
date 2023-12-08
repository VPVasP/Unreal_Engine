// Fill out your copyright notice in the Description page of Project Settings.

#include "SpawnerBase.h"
#include "Components/BoxComponent.h"
#include "Kismet/KismetMathLibrary.h"

// Sets default values
ASpawnerBase::ASpawnerBase()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SpawnVolume = CreateDefaultSubobject<UBoxComponent>(TEXT("Spawner"));

	MinSpawnDelay = 0.5f;
	MaxSpawnDelay = 5.0f;
}

// Called when the game starts or when spawned
void ASpawnerBase::BeginPlay()
{
	Super::BeginPlay();

	currentWorld = GetWorld();

	RandomSpawnInterval = FMath::RandRange(MinSpawnDelay, MaxSpawnDelay);
	currentWorld->GetTimerManager().SetTimer(SpawnTimerHandle, this, &ASpawnerBase::SpawnItem, RandomSpawnInterval, false);
}

// Called every frame
void ASpawnerBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

FVector ASpawnerBase::GetRandomSpawnPoint()
{
	const FVector spawnOrigin = SpawnVolume->Bounds.Origin;
	const FVector spawnLimit = SpawnVolume->Bounds.BoxExtent;

	return UKismetMathLibrary::RandomPointInBoundingBox(spawnOrigin, spawnLimit);
}

void ASpawnerBase::SpawnItem()
{
	//Check if actor to spawn exists
	if (!ItemToSpawn)
	{
		return;
	}

	FRotator randomRotation;
	randomRotation.Yaw = FMath::RandRange(0.0, 360.0);
	randomRotation.Pitch = FMath::RandRange(0.0, 360.0);
	randomRotation.Roll = FMath::RandRange(0.0, 360.0);

	//Setup the spawning parameters
	FActorSpawnParameters params;
	params.Owner = this;
	params.Instigator = GetInstigator();
	params.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;

	//Spawn item
	if (!currentWorld)
	{
		return;
	}
	currentWorld->SpawnActor<APickupBase>(ItemToSpawn, GetRandomSpawnPoint(), randomRotation, params);

	RandomSpawnInterval = FMath::RandRange(MinSpawnDelay, MaxSpawnDelay);
	currentWorld->GetTimerManager().SetTimer(SpawnTimerHandle, this, &ASpawnerBase::SpawnItem, RandomSpawnInterval, false);
}