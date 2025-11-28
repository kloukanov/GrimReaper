#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "PlayableCharacter.generated.h"

UCLASS()
class GRIMREAPER_API APlayableCharacter : public ACharacter
{
	GENERATED_BODY()

	UPROPERTY(VisibleAnywhere)
	class UHealthComponent* HealthComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Components", meta = (AllowPrivateAccess = "true"))
	class USpringArmComponent* CameraBoom;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Components", meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* FollowCamera;

	UPROPERTY(EditAnywhere, Category ="Input")
	class UInputAction* MoveAction;

	UPROPERTY(EditAnywhere, Category ="Input")
	class UInputAction* TurnAction;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement Variables", meta = (AllowPrivateAccess = "true"))
	float TurnRate;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement Variables", meta = (AllowPrivateAccess = "true"))
	float DecelarationRate = 1500;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement Variables", meta = (AllowPrivateAccess = "true"))
	float Speed;

	float CurrentTurnRate;
	
	FVector2D MovementVector;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon Variables", meta = (AllowPrivateAccess = "true"))
	TArray<TSubclassOf<class UWeaponBaseComponent>> WeaponClasses;

	UPROPERTY()
	TArray<class UWeaponBaseComponent*> Weapons;

public:

	APlayableCharacter();

protected:

	virtual void BeginPlay() override;

	void Move(const struct FInputActionValue& Value);

	void Turn(const struct FInputActionValue& Value);

	void HandleSteering(float DeltaTime);

	void SetUpWeapons();

	class AGRPlayerState* PlayerState;

public:	

	virtual void Tick(float DeltaTime) override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UFUNCTION(Blueprintcallable)
	void HandleTakeDamage();

	UFUNCTION(Blueprintcallable)
	float GetHealthPercent() const;

	UFUNCTION(Blueprintcallable)
	void CollectSoul(ECollectibleType Type, const int Value);
};
