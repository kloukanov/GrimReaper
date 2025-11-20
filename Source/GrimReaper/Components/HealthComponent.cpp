#include "HealthComponent.h"

UHealthComponent::UHealthComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}


void UHealthComponent::BeginPlay()
{
	Super::BeginPlay();
	
	Health = MaxHealth;

	if(GetHasIFramesEnabled()){
		// this actor can have IFrames
		IFramesSecondsRemaining = MaxIFramesSeconds;
		GetOwner()->GetWorldTimerManager().SetTimer(IFrameTimerHandle, this, &UHealthComponent::UpdateIFramesSecondsRemaining, 1.f, true);
	}
}


void UHealthComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

void UHealthComponent::TakeDamage(float DamageValue) {

	if(GetHasIFramesEnabled() && GotHit){
		// don't take damage
		UE_LOG(LogTemp, Warning, TEXT("invincibleeeeeeee"));
		return;
	}

	Health -= DamageValue;
	OnActorDamaged.Broadcast();
	GotHit = true;

	// TODO: tell our gamemode or manager that actor died for stat keeping and object pooling

	UE_LOG(LogTemp, Warning, TEXT("health = %f"), Health);
}

void UHealthComponent::ResetHealth() {
	Health = MaxHealth;
}

void UHealthComponent::UpdateIFramesSecondsRemaining() {
	UE_LOG(LogTemp, Warning, TEXT("GotHit = %s"), GotHit == true ? *FString("true") : *FString("false"));
	UE_LOG(LogTemp, Warning, TEXT("IFramesSecondsRemaining = %d"), IFramesSecondsRemaining);

	if(IFramesSecondsRemaining <= 0){
		UE_LOG(LogTemp, Warning, TEXT("reset iframes and gothit"));
		IFramesSecondsRemaining = MaxIFramesSeconds;
		GotHit = false;
	}

	if(GotHit){
		IFramesSecondsRemaining--;
	}
}