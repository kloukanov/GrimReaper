#include "Collectible.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GrimReaper/GRGameInstance.h"

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
