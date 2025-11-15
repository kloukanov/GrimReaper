#pragma once

#include "Engine/DataTable.h"
#include "CollectibleType.h"
#include "CollectibleDataRow.generated.h"

DECLARE_DELEGATE_OneParam(FCollectibleLoadedDelegate, UMaterialInterface*);

USTRUCT(BlueprintType)
struct FCollectibleDataRow : public FTableRowBase
{
    GENERATED_BODY()

public:

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    ECollectibleType Type;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    TSoftObjectPtr<UMaterialInterface> Material; // this is for soft reference asynch loading

};