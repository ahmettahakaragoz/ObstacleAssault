// Fill out your copyright notice in the Description page of Project Settings.


#include "MovingPlatform.h"

// Sets default values
AMovingPlatform::AMovingPlatform()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AMovingPlatform::BeginPlay()
{
	Super::BeginPlay();
	
	StartLocation = GetActorLocation();
	UE_LOG(LogTemp, Display, TEXT("Configured Moved Distance: %f"), MoveDistance);
	FString Name = GetName();
	UE_LOG(LogTemp, Display, TEXT("BeginPlay: %s"), *Name);
	
}

// Called every frame
void AMovingPlatform::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	//MyVector.Z = MyVector.Z + 1;
	//MyVector.Y = MyVector.Y + 1;
	//MyVector.X = MyVector.X + 7;

	/*FVector LocalVector = FVector(1, 2, 3);

	LocalVector.Z += 100;

	SetActorLocation(LocalVector);*/

	MovePlatform(DeltaTime);
	RotatePlatform(DeltaTime);

}
void AMovingPlatform::MovePlatform(float DeltaTime)
{
	if (ShouldPlatformReturn())
	{
		FVector MovedDirection = PlatformVelocity.GetSafeNormal();
		StartLocation += MovedDirection * MoveDistance;
		SetActorLocation(StartLocation);
		PlatformVelocity = -PlatformVelocity;
	}
	else
	{
		FVector CurrentLocation = GetActorLocation();
		CurrentLocation = CurrentLocation + (PlatformVelocity * DeltaTime);
		SetActorLocation(CurrentLocation);
	}
}

void AMovingPlatform::RotatePlatform(float DeltaTime)
{
	FRotator CurrentRotation = GetActorRotation();
	CurrentRotation = CurrentRotation + RotationVelocity * DeltaTime;
	SetActorRotation(CurrentRotation);

	//AddActorLocalRotation(RotationVelocity * DeltaTime); Sadece bu komut olduðu zaman yukaridaki kodlara gerek kalmaz yerel rotasyonu otomatik olarak alýr ve 
	//verdiðimiz deðere göre iiþlem yapar
}
	//SetActorLocation(MyVector);

bool AMovingPlatform::ShouldPlatformReturn()
{
	return GetDistanceMoved() > MoveDistance;
}

float AMovingPlatform::GetDistanceMoved()
{
	return FVector::Dist(StartLocation, GetActorLocation());
}

