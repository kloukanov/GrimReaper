#include "MainGameMode.h"
#include "Blueprint/UserWidget.h"

void AMainGameMode::BeginPlay(){

    HUD = CreateWidget(GetWorld(), HUDScreen);

    if(HUD){
        HUD->AddToViewport();
    }
}