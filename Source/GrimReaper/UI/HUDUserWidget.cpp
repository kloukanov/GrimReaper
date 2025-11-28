#include "HUDUserWidget.h"
#include "Components/TextBlock.h"
#include "GrimReaper/Actors/GRPlayerState.h"
#include "GrimReaper/CollectibleType.h"

void UHUDUserWidget::NativeConstruct(){
    Super::NativeConstruct();

    APlayerController* PlayerController = GetOwningPlayer();
    if(AGRPlayerState* PlayerState = PlayerController->GetPlayerState<AGRPlayerState>()){
        PlayerState->OnSoulsChanged.AddDynamic(this, &UHUDUserWidget::UpdateCollectedSouls);
        // initialize with 0
        UpdateCollectedSouls(ECollectibleType::Blue, 0);
        UpdateCollectedSouls(ECollectibleType::Red, 0);
    }
}

void UHUDUserWidget::UpdateCollectedSouls(ECollectibleType Type, int Souls){
    switch (Type){
        case ECollectibleType::Blue :
            CollectedSouls_B->SetText(FText::AsNumber(Souls));
            break;
        case ECollectibleType::Red :
            CollectedSouls_R->SetText(FText::AsNumber(Souls));
            break;
        default:
            return;
    }
}