#include "GRGameInstance.h"

void UGRGameInstance::LoadCollectibleAssets(ECollectibleType Type, FCollectibleLoadedDelegate Callback) {

    if (!CollectibleDataTable){
        UE_LOG(LogTemp, Error, TEXT("Collectible DataTable not set in GameInstance"));
        Callback.ExecuteIfBound(nullptr);
        return;
    }

    const FString EnumName = UEnum::GetDisplayValueAsText(Type).ToString();
    const FName RowName(*EnumName);

    const FCollectibleDataRow* Row = CollectibleDataTable->FindRow<FCollectibleDataRow>(RowName, TEXT(""));

    if (!Row) {
        UE_LOG(LogTemp, Warning, TEXT("No row named '%s' in DataTable"), *RowName.ToString());
        Callback.ExecuteIfBound(nullptr);
        return;
    }

    TArray<FSoftObjectPath> AssetsToLoad;

    if(Row->Material.ToSoftObjectPath().IsValid()){
        AssetsToLoad.Add(Row->Material.ToSoftObjectPath());
    }

    Streamable.RequestAsyncLoad(AssetsToLoad, [Row, Callback](){
        Callback.ExecuteIfBound(Row->Material.Get());
    });
}