#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "GrimReaper/CollectibleType.h"
#include "Collectible.generated.h"

UCLASS()
class GRIMREAPER_API ACollectible : public ACharacter
{
	GENERATED_BODY()

public:
	ACollectible();

protected:

	UPROPERTY(EditAnywhere, Category = "Movement Variables", meta = (AllowPrivateAccess = "true"))
	float Speed;

	UPROPERTY(EditAnywhere, Category = "Collecatble Properties", meta = (AllowPrivateAccess = "true"))
	ECollectibleType Type;

	virtual void BeginPlay() override;

	UFUNCTION()
    void OnCapsuleComponentOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
                            UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep,
                            const FHitResult& SweepResult);

public:	
	virtual void Tick(float DeltaTime) override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
