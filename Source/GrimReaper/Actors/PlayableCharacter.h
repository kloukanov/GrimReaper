#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "PlayableCharacter.generated.h"

UCLASS()
class GRIMREAPER_API APlayableCharacter : public ACharacter
{
	GENERATED_BODY()

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Components", meta = (AllowPrivateAccess = "true"))
	class USpringArmComponent* CameraBoom;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Components", meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* FollowCamera;

	UPROPERTY(EditAnywhere, Category ="Input")
	class UInputAction* MoveAction;


public:

	APlayableCharacter();

protected:

	virtual void BeginPlay() override;

	void Move(const struct FInputActionValue& Value);


public:	

	virtual void Tick(float DeltaTime) override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
