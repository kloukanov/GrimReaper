#include "EnemyBase.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Components/CapsuleComponent.h"
#include "GrimReaper/Components/HealthComponent.h"

AEnemyBase::AEnemyBase()
{
	PrimaryActorTick.bCanEverTick = false;
	HealthComponent = CreateDefaultSubobject<UHealthComponent>(TEXT("HealthComponent"));
}

void AEnemyBase::BeginPlay()
{
	Super::BeginPlay();

	if(GetCapsuleComponent()){
		GetCapsuleComponent()->OnComponentBeginOverlap.AddDynamic(this, &AEnemyBase::OnCapsuleComponentOverlap);
	}

	if(HealthComponent){
		HealthComponent->OnActorDamaged.AddDynamic(this, &AEnemyBase::HandleTakeDamage);
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
	// UE_LOG(LogTemp, Warning, TEXT("enemy collided with a component with name %s"), *OtherComp->GetName());
	if (OtherComp && OtherComp->ComponentHasTag("WeaponDetection"))
		return;
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
		// TODO: enable the AI controller
	}else {
		bIsDead = false;
		HealthComponent->ResetHealth();
		SetActorHiddenInGame(false);
		SetActorEnableCollision(true);
		// TODO: disable the AI controller
	}
}

void AEnemyBase::HandleTakeDamage() {
	//TODO: play damaged animation
	UE_LOG(LogTemp, Warning, TEXT("this actor is taking damage: %s"), *this->GetActorNameOrLabel());
	if(HealthComponent->GetHealthPercent() <= 0){
		ToggleIsDead(true);
	}
}