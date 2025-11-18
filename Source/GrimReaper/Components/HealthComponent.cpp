#include "HealthComponent.h"

UHealthComponent::UHealthComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}


void UHealthComponent::BeginPlay()
{
	Super::BeginPlay();
	
	Health = MaxHealth;
}


void UHealthComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

void UHealthComponent::TakeDamage(float DamageValue) {
	Health -= DamageValue;
	OnActorDamaged.Broadcast();

	// TODO: tell our gamemode or manager that actor died for stat keeping and object pooling


	UE_LOG(LogTemp, Warning, TEXT("health = %f"), Health);
}

void UHealthComponent::ResetHealth() {
	Health = MaxHealth;
}