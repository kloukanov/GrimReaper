#include "GRPlayerState.h"
#include "GrimReaper/CollectibleType.h"

AGRPlayerState::AGRPlayerState() {}

void AGRPlayerState::ModifySouls(ECollectibleType Type, const int Amount){
    switch (Type){
        case ECollectibleType::Blue :
            TotalSouls_B += Amount;
            OnSoulsChanged.Broadcast(Type, TotalSouls_B);
            break;
        case ECollectibleType::Red :
            TotalSouls_R += Amount;
            OnSoulsChanged.Broadcast(Type, TotalSouls_R);
            break;
        default:
            return;
    }
}