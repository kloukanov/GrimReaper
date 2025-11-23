#include "PlayableCharacter.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Camera/CameraComponent.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"
#include "GrimReaper/Components/HealthComponent.h"
#include "GrimReaper/Components/Weapon/WeaponBaseComponent.h"

APlayableCharacter::APlayableCharacter() {
	PrimaryActorTick.bCanEverTick = true;

	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->TargetArmLength = 400.0f;
	CameraBoom->bUsePawnControlRotation = true;

	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
	FollowCamera->bUsePawnControlRotation = false;

	HealthComponent = CreateDefaultSubobject<UHealthComponent>(TEXT("HealthComponent"));
}


void APlayableCharacter::BeginPlay() {
	Super::BeginPlay();
	
	GetCharacterMovement()->MaxWalkSpeed = Speed;

	if(HealthComponent){
		HealthComponent->OnActorDamaged.AddDynamic(this, &APlayableCharacter::HandleTakeDamage);
	}

	SetUpWeapons();
}


void APlayableCharacter::Tick(float DeltaTime) {
	Super::Tick(DeltaTime);
	HandleSteering(DeltaTime);
}

void APlayableCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) {
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent)) {
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &APlayableCharacter::Move);
		EnhancedInputComponent->BindAction(TurnAction, ETriggerEvent::Triggered, this, &APlayableCharacter::Turn);
	}
}

void APlayableCharacter::HandleSteering(float DeltaTime) {
	if(GetVelocity().IsNearlyZero()){
		// UE_LOG(LogTemp, Warning, TEXT("velocity is zero, early return"));
		return;
	}

	// Update car rotation based on turn rate
    if (!FMath::IsNearlyZero(CurrentTurnRate))
    {
		// UE_LOG(LogTemp, Warning, TEXT("rotation input not zero"));
        FRotator NewRotation = GetActorRotation();
		if(MovementVector.Y <= 0 && GetActorForwardVector().Dot(GetVelocity().GetSafeNormal()) < -0.1f){
			// UE_LOG(LogTemp, Warning, TEXT("we are NOT GOING FORWARD"));
			NewRotation.Yaw -= CurrentTurnRate * DeltaTime;
		}else {
			// UE_LOG(LogTemp, Warning, TEXT("we are going forward"));
			NewRotation.Yaw += CurrentTurnRate * DeltaTime; // basically inverting the turn direction when going backwards
		}

        SetActorRotation(NewRotation);
    }
	
	if(MovementVector.Y == 0.f && FMath::Abs(GetVelocity().Length()) > 0){
		// UE_LOG(LogTemp, Warning, TEXT("forward movement stoped but velocity is not zero"));
		AddMovementInput(GetActorForwardVector(), FMath::Abs(GetVelocity().Length())/DecelarationRate);
	}

	CurrentTurnRate = 0.f;
	MovementVector.Y = 0;
	MovementVector.X = 0;
}

void APlayableCharacter::Move(const FInputActionValue& Value) {
	MovementVector = Value.Get<FVector2D>();
	AddMovementInput(GetActorForwardVector(), MovementVector.Y);
}

void APlayableCharacter::Turn(const FInputActionValue& Value) {
	CurrentTurnRate = Value.Get<FVector2D>().X * TurnRate;
}

void APlayableCharacter::HandleTakeDamage() {
	//TODO: play damaged animation
	//TODO: grant x seconds invincibility
	UE_LOG(LogTemp, Warning, TEXT("this actor is taking damage: %s"), *this->GetActorNameOrLabel());
}

float APlayableCharacter::GetHealthPercent() const {
	return HealthComponent->GetHealthPercent();
}

void APlayableCharacter::SetUpWeapons() {
	for(auto WeaponClass : WeaponClasses){
		if(!WeaponClass){
			continue;
		}
		
		UWeaponBaseComponent* NewWeapon = NewObject<UWeaponBaseComponent>(this, WeaponClass);
		
		if(NewWeapon){
			// TODO: change attach location but root is fine for now
			NewWeapon->AttachToComponent(GetRootComponent(), FAttachmentTransformRules::KeepRelativeTransform);
			NewWeapon->SetMobility(EComponentMobility::Movable);
			NewWeapon->RegisterComponent();
			Weapons.Add(NewWeapon);
		}
	}
}