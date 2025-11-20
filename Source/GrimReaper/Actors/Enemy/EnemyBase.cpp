#include "EnemyBase.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Components/CapsuleComponent.h"
#include "GrimReaper/Components/HealthComponent.h"

AEnemyBase::AEnemyBase()
{
	PrimaryActorTick.bCanEverTick = false;

}

void AEnemyBase::BeginPlay()
{
	Super::BeginPlay();

	if(GetCapsuleComponent()){
		GetCapsuleComponent()->OnComponentBeginOverlap.AddDynamic(this, &AEnemyBase::OnCapsuleComponentOverlap);
	}

	GetCharacterMovement()->MaxWalkSpeed = Speed;
}

void AEnemyBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AEnemyBase::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void AEnemyBase::OnCapsuleComponentOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) {
	UE_LOG(LogTemp, Warning, TEXT("enemy collided with an actor with name %s"), *OtherActor->GetActorNameOrLabel());
	// TODO: have to disable overlap collision with other actors
	UHealthComponent* HC = OtherActor->FindComponentByClass<UHealthComponent>();
	if(HC){
		HC->TakeDamage(GetDamageAmount());
	}
}

void AEnemyBase::ToggleIsDead(bool IsDead) {
	if(IsDead) {
		bIsDead = true;
		SetActorHiddenInGame(true);
		SetActorEnableCollision(false);
	}else {
		bIsDead = false;
		// TODO: reset health
		SetActorHiddenInGame(false);
		SetActorEnableCollision(true);
	}
}
