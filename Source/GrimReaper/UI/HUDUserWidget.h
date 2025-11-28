#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "HUDUserWidget.generated.h"

UCLASS()
class GRIMREAPER_API UHUDUserWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:

	UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (BindWidget))
	class UTextBlock* CollectedSouls_B;
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (BindWidget))
	class UTextBlock* CollectedSouls_R;

	virtual void NativeConstruct() override;

	UFUNCTION(Blueprintcallable)
	void UpdateCollectedSouls(ECollectibleType Type, int Souls);

};
