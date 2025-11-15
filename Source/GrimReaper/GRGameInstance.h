#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "CollectibleType.h"
#include "Engine/StreamableManager.h"
#include "CollectibleDataRow.h"
#include "GRGameInstance.generated.h"

UCLASS()
class GRIMREAPER_API UGRGameInstance : public UGameInstance
{
	GENERATED_BODY()
	
public:
	void LoadCollectibleAssets(ECollectibleType Type, FCollectibleLoadedDelegate Callback);

private:

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Data", meta = (AllowPrivateAccess = "true"))
	UDataTable* CollectibleDataTable;

	FStreamableManager Streamable;
};
