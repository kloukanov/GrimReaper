#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ProjectileBase.generated.h"

UCLASS()
class GRIMREAPER_API AProjectileBase : public AActor
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components", meta = (AllowPrivateAccess = "true"))
	class USphereComponent* SphereComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Mesh", meta = (AllowPrivateAccess = "true"))
	class UStaticMeshComponent* ProjectileMesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components", meta = (AllowPrivateAccess = "true"))
	class UProjectileMovementComponent* ProjectileMovementComp;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Projectile Variables", meta = (AllowPrivateAccess = "true"))
	float Damage = 20;

public:	

	AProjectileBase();

protected:

	virtual void BeginPlay() override;

	UFUNCTION()
    void OnSphereComponentOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
                            UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep,
                            const FHitResult& SweepResult);

public:	

	virtual void Tick(float DeltaTime) override;

	float GetDamageAmount() const { return Damage; }
};
