#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "EnemyBase.generated.h"

UCLASS()
class GRIMREAPER_API AEnemyBase : public ACharacter
{
	GENERATED_BODY()

	UPROPERTY(VisibleAnywhere)
	class UHealthComponent* HealthComponent;

public:
	AEnemyBase();

protected:
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Enemy Variables", meta = (AllowPrivateAccess = "true"))
	float Damage = 10;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Enemy Variables", meta = (AllowPrivateAccess = "true"))
	float Speed = 300;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Enemy Variables", meta = (AllowPrivateAccess = "true"))
	float AttackRate = 5;

	bool bIsDead = false;

	UFUNCTION()
    void OnCapsuleComponentOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
                            UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep,
                            const FHitResult& SweepResult);

public:	
	virtual void Tick(float DeltaTime) override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	bool GetIsDead() const { return bIsDead; }

	float GetDamageAmount() const { return Damage; }

	float GetAttackRate() const { return AttackRate; }

	void ToggleIsDead(bool IsDead);

};
