#include "Collectible.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GrimReaper/GRGameInstance.h"
#include "Components/CapsuleComponent.h"
#include "PlayableCharacter.h"

ACollectible::ACollectible()
{
	PrimaryActorTick.bCanEverTick = false;

}

void ACollectible::BeginPlay()
{
	Super::BeginPlay();

	UGRGameInstance* GI = GetGameInstance<UGRGameInstance>();

	if(GI){
		GI->LoadCollectibleAssets(Type, FCollectibleLoadedDelegate::CreateWeakLambda(this, [this](UMaterialInterface* Material){
			if(Material){
				GetMesh()->SetMaterial(0, Material);
			}
		}));
	}

	if(GetCapsuleComponent()){
		GetCapsuleComponent()->OnComponentBeginOverlap.AddDynamic(this, &ACollectible::OnCapsuleComponentOverlap);
	}

	GetCharacterMovement()->MaxWalkSpeed = Speed;
	
}

void ACollectible::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ACollectible::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

void ACollectible::OnCapsuleComponentOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) {
	UE_LOG(LogTemp, Warning, TEXT("we collided with an actor with name %s"), *OtherActor->GetActorNameOrLabel());
	if (APlayableCharacter* Player = Cast<APlayableCharacter>(OtherActor)) {
        UE_LOG(LogTemp, Log, TEXT("the player interacted with this"));
		// TODO: broadcast this instead of going directly to player and pass the ECollectibleType Type
		Player->CollectSoul(Type, 1);
		Destroy();
    }
}