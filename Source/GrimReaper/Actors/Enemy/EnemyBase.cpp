#include "EnemyBase.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Components/CapsuleComponent.h"
#include "GrimReaper/Actors/PlayableCharacter.h"

AEnemyBase::AEnemyBase()
{
	PrimaryActorTick.bCanEverTick = true;

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
	if (APlayableCharacter* Player = Cast<APlayableCharacter>(OtherActor)) {
        UE_LOG(LogTemp, Log, TEXT("the player interacted with this"));
    }
}

