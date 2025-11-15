#pragma once

#include "CollectibleType.generated.h"

UENUM(BlueprintType)
enum class ECollectibleType : uint8
{
    Blue    UMETA(DisplayName="Blue"),
    Red     UMETA(DisplayName="Red"),
    Yellow  UMETA(DisplayName="Yellow")
};