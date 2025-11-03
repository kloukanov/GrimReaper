#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "GRPlayerController.generated.h"

UCLASS()
class GRIMREAPER_API AGRPlayerController : public APlayerController
{
	GENERATED_BODY()
	
protected:

	UPROPERTY(EditAnywhere, Category = "Input")
    class UInputMappingContext* InputMappingContext;

	virtual void BeginPlay() override;
};
