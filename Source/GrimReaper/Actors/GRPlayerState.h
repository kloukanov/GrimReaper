#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "GRPlayerState.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnSoulsChanged, ECollectibleType, Type, int, NewSouls);
UCLASS()
class GRIMREAPER_API AGRPlayerState : public APlayerState
{
	GENERATED_BODY()
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Inventory", meta = (AllowPrivateAccess = "true"))
	int TotalSouls_B = 0;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Inventory", meta = (AllowPrivateAccess = "true"))
	int TotalSouls_R = 0;

public:
	AGRPlayerState();

	UFUNCTION(BlueprintCallable, Category = "Souls")
    void ModifySouls(ECollectibleType Type, const int Amount);

    UPROPERTY(BlueprintAssignable, Category = "Events")
    FOnSoulsChanged OnSoulsChanged;
};
