#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "HealthComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnActorDamaged);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class GRIMREAPER_API UHealthComponent : public UActorComponent
{
	GENERATED_BODY()

private:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Health", meta = (AllowPrivateAccess = "true"))
	float MaxHealth = 100.f;

	float Health = 0.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Health", meta = (AllowPrivateAccess = "true"))
	bool HasIFramesEnabled = false; // if the actor can become temporary invincibility

	bool GotHit = false; // if the actor can be hit during invincibility

	FTimerHandle IFrameTimerHandle;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Health", meta = (AllowPrivateAccess = "true"))
	int MaxIFramesSeconds = 5;

	int IFramesSecondsRemaining = 0;

	void UpdateIFramesSecondsRemaining();

protected:
	virtual void BeginPlay() override;

public:	
	UHealthComponent();

	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	void TakeDamage(float DamageValue);

	UPROPERTY(BlueprintAssignable, Category = "Events")
	FOnActorDamaged OnActorDamaged;

	void ResetHealth();

	float GetHealthPercent() const { return Health / MaxHealth; }

	bool GetHasIFramesEnabled() const { return HasIFramesEnabled; }

	void SetHasIFramesEnabled(bool Val) { HasIFramesEnabled = Val; }
		
};
