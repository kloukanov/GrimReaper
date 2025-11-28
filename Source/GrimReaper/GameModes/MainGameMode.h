#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "MainGameMode.generated.h"

UCLASS()
class GRIMREAPER_API AMainGameMode : public AGameModeBase
{
	GENERATED_BODY()
	
	class UUserWidget* HUD;

	UPROPERTY(EditAnywhere)
	TSubclassOf<class UUserWidget> HUDScreen;

	virtual void BeginPlay() override;
};
