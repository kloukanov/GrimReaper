#include "WeaponBaseComponent.h"
#include "GrimReaper/Actors/Projectile/ProjectileBase.h"
#include "Components/SphereComponent.h"
#include "GrimReaper/Components/HealthComponent.h"

UWeaponBaseComponent::UWeaponBaseComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
	SetMobility(EComponentMobility::Movable);

	TargetDetectionSphere = CreateDefaultSubobject<USphereComponent>(TEXT("TargetDetectionSphere"));
    TargetDetectionSphere->SetRelativeLocation(FVector::ZeroVector);
    TargetDetectionSphere->SetMobility(EComponentMobility::Movable);
    TargetDetectionSphere->InitSphereRadius(TargetDetectionRadius);
	TargetDetectionSphere->ComponentTags.Add("WeaponDetection");
}

void UWeaponBaseComponent::BeginPlay()
{
	Super::BeginPlay();

	TargetDetectionSphere->SetSphereRadius(TargetDetectionRadius, true);
	TargetDetectionSphere->AttachToComponent(this, FAttachmentTransformRules::KeepRelativeTransform);
	TargetDetectionSphere->RegisterComponent();
	TargetDetectionSphere->IgnoreActorWhenMoving(GetOwner(), true);

	TargetDetectionSphere->OnComponentBeginOverlap.AddDynamic(this, &UWeaponBaseComponent::OnTargetEnterDetectionSphere);
	TargetDetectionSphere->OnComponentEndOverlap.AddDynamic(this, &UWeaponBaseComponent::OnTargetExitDetectionSphere);

	if(ShouldFire){
		StartFiring();
	}
}

void UWeaponBaseComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	DrawDebugSphere(
        GetWorld(),
        TargetDetectionSphere->GetComponentLocation(),
        TargetDetectionSphere->GetScaledSphereRadius(),
        24,
        FColor::Red,
        false,
        0.f,
        0,
        1.f
    );
}

void UWeaponBaseComponent::StartFiring(){
	GetOwner()->GetWorldTimerManager().SetTimer(IFrameTimerHandle, this, &UWeaponBaseComponent::Fire, FireRate, true);
}

void UWeaponBaseComponent::Fire() {
	AActor* Target = GetClosestTarget();

	if(Target){
		// UE_LOG(LogTemp, Warning, TEXT("fire!"));
		// UE_LOG(LogTemp, Warning, TEXT("closest target is %s"), *Target->GetActorNameOrLabel());
		FVector Direction = (Target->GetActorLocation() - GetOwner()->GetActorLocation()).GetSafeNormal();
    	FRotator SpawnRotation = Direction.Rotation();
		FActorSpawnParameters Params;
		Params.Instigator = Cast<APawn>(GetOwner());
		// TODO: use a spawn pool manager to keep track of objects and reuse
		AProjectileBase* Projectile = GetWorld()->SpawnActor<AProjectileBase>(ProjectileClass, GetOwner()->GetActorLocation(), SpawnRotation, Params);
	}
	// else{
	// 	 UE_LOG(LogTemp, Warning, TEXT("no targets in sphere!"));
	// }	
}

AActor* UWeaponBaseComponent::GetClosestTarget() const{

	AActor* ClosestTarget = nullptr;
	float ClosestDistSq = TNumericLimits<float>::Max();

	const FVector CurrentLocation = GetOwner()->GetActorLocation();

	for(AActor* Target : NearbyTargets){
		// UE_LOG(LogTemp, Warning, TEXT("target located: %s"), *Target->GetActorNameOrLabel());
		if(!IsValid(Target)){
			continue;	
		}

		float DistSq = FVector::DistSquared(Target->GetActorLocation(), CurrentLocation);

		if(DistSq < ClosestDistSq){
			ClosestDistSq = DistSq;
			ClosestTarget = Target;
		}
	}

	return ClosestTarget;
}

void UWeaponBaseComponent::OnTargetEnterDetectionSphere(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) {
	// UE_LOG(LogTemp, Warning, TEXT("detection sphere collided with an actor with name %s"), *OtherActor->GetActorNameOrLabel());
	if(OtherActor->FindComponentByClass<UHealthComponent>()){
		// UE_LOG(LogTemp, Warning, TEXT("we added this guy: %s"), *OtherActor->GetActorNameOrLabel());
		NearbyTargets.Add(OtherActor);
	}
}

void UWeaponBaseComponent::OnTargetExitDetectionSphere(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex) {
	// UE_LOG(LogTemp, Warning, TEXT("Removing this guy: %s"), *OtherActor->GetActorNameOrLabel());
	NearbyTargets.Remove(OtherActor);
}