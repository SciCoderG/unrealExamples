// Fill out your copyright notice in the Description page of Project Settings.

#include "OpenDoor.h"
#include "GameFramework/Actor.h"
#include "Engine/World.h"
#include "GameFramework/PlayerController.h"
#include "Components/PrimitiveComponent.h"

// Sets default values for this component's properties
UOpenDoor::UOpenDoor()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UOpenDoor::BeginPlay()
{
	Super::BeginPlay();
	Owner = GetOwner();
}



// Called every frame
void UOpenDoor::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (GetTotalMassOfActorsOnPlate() > ThresholdToOpenDoor) {
		OnOpen.Broadcast();
		LastDoorOpenTime = GetWorld()->GetTimeSeconds();
	}

	if (GetWorld()->GetTimeSeconds() - LastDoorOpenTime > DoorCloseDelay)
		OnClose.Broadcast();
	


}

float UOpenDoor::GetTotalMassOfActorsOnPlate() 
{
	float TotalMass = 0.f;

	TArray<AActor*> OverlappingActors;

	if(PressurePlate)
		PressurePlate->GetOverlappingActors(OverlappingActors);

	for (auto actor : OverlappingActors) {
		TotalMass += actor->FindComponentByClass<UPrimitiveComponent>()->GetMass();
	}

	return TotalMass;
}

