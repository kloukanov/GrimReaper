#pragma once

#include "CoreMinimal.h"
#include "Components/SceneComponent.h"
#include "WeaponBaseComponent.generated.h"


UCLASS( ClassGroup=(Custom), Blueprintable, meta=(BlueprintSpawnableComponent) )
class GRIMREAPER_API UWeaponBaseComponent : public USceneComponent
{
	GENERATED_BODY()

private:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon Variables", meta = (AllowPrivateAccess = "true"))
	TSubclassOf<class AProjectileBase> ProjectileClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon Variables", meta = (AllowPrivateAccess = "true"))
	FTransform MuzzleTransform;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon Variables", meta = (AllowPrivateAccess = "true"))
	float FireRate = 1;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon Variables", meta = (AllowPrivateAccess = "true"))
	float TargetDetectionRadius = 1300.f;

	FTimerHandle IFrameTimerHandle;

	UPROPERTY(VisibleAnywhere)
	class USphereComponent* TargetDetectionSphere;

	TArray<AActor*> NearbyTargets;

public:	

	UWeaponBaseComponent();

protected:

	virtual void BeginPlay() override;

	virtual AActor* GetClosestTarget() const;

	UFUNCTION()
	virtual void OnTargetEnterDetectionSphere(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	virtual void OnTargetExitDetectionSphere(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

public:	

	virtual void Fire();

	virtual void StartFiring();

	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

		
};
