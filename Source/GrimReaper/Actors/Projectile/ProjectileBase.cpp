#include "ProjectileBase.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Components/SphereComponent.h"
#include "GrimReaper/Components/HealthComponent.h"

AProjectileBase::AProjectileBase()
{
	PrimaryActorTick.bCanEverTick = false;

	SphereComponent = CreateDefaultSubobject<USphereComponent>(TEXT("Sphere Component"));
	RootComponent = SphereComponent;
	ProjectileMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Projectile Mesh"));
	ProjectileMesh->SetupAttachment(RootComponent);

	ProjectileMovementComp = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("Projectile Movement Component"));
	ProjectileMovementComp->MaxSpeed = 1300.f;
	ProjectileMovementComp->InitialSpeed = 1300.f;
}

void AProjectileBase::BeginPlay()
{
	Super::BeginPlay();

	if(SphereComponent){
		if(GetInstigator()){
			SphereComponent->IgnoreActorWhenMoving(GetInstigator(), true);
		}
		SphereComponent->OnComponentBeginOverlap.AddDynamic(this, &AProjectileBase::OnSphereComponentOverlap);
	}
	
}

void AProjectileBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AProjectileBase::OnSphereComponentOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) {
	if (OtherActor == GetInstigator()) return;
	UE_LOG(LogTemp, Warning, TEXT("enemy got hit by projectile %s"), *OtherActor->GetActorNameOrLabel());
	UHealthComponent* HC = OtherActor->FindComponentByClass<UHealthComponent>();
	if(HC){
		HC->TakeDamage(GetDamageAmount());
	}
	Destroy();
}