// Copyright Matthew Pye 2018.

#include "Grabber.h"
#include "Runtime/Engine/Classes/Engine/World.h"
#include "DrawDebugHelpers.h"

#define OUT


// Sets default values for this component's properties
UGrabber::UGrabber()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UGrabber::BeginPlay()
{
	Super::BeginPlay();
	UE_LOG(LogTemp,Warning, TEXT("Grabber reporting for duty!"))
	// ...
	
}


// Called every frame
void UGrabber::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	//Get the players view point per tick
	FVector PlayerViewPointLocation;
	FRotator PlayerViewPointRotation;

	GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(
	OUT PlayerViewPointLocation,
	OUT PlayerViewPointRotation);



	FVector LineTraceEnd = PlayerViewPointLocation + PlayerViewPointRotation.Vector()*Reach;

	///Draw a trace in the world to visualise
	DrawDebugLine
	(
		GetWorld(), 
		PlayerViewPointLocation, 
		LineTraceEnd,
		FColor(255,0,0,0),
		false,
		0.f,
		0.f,
		15.f
	);

	///Setup query paramerters
	FCollisionQueryParams TraceParameters(FName(TEXT("")), false, GetOwner());

	///Ray-cast out to reach distance
	FHitResult LineTraceHit;
	 GetWorld()->LineTraceSingleByObjectType
	 (
	 	OUT LineTraceHit,
	 	PlayerViewPointLocation,
	 	LineTraceEnd,
	 	FCollisionObjectQueryParams(ECollisionChannel::ECC_PhysicsBody),
	 	TraceParameters
	 );

	///see what we hit
	 AActor* ActorHit = LineTraceHit.GetActor();
	if (ActorHit)
	{
		UE_LOG(LogTemp, Warning, TEXT("Line Trace Hit: %s"), *(ActorHit->GetName()))
	}
	 
}

