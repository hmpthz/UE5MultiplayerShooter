#include "OverheadWidget.h"
#include "Components/TextBlock.h"
#include "GameFramework/PlayerState.h"


void UOverheadWidget::SetDisplayText(FString TextToDisplay)
{
    if (DisplayText)
    {
        DisplayText->SetText(FText::FromString(TextToDisplay));
    }
}

void UOverheadWidget::ShowPlayerNetRole(APawn* InPawn)
{
    ENetRole RemoteRole = InPawn->GetRemoteRole();
    FString Role;
    switch (RemoteRole)
    {
    case ROLE_Authority:
        Role = FString("Authority");
        break;
    case ROLE_AutonomousProxy:
        Role = FString("Autonomous Proxy");
        break;
    case ROLE_SimulatedProxy:
        Role = FString("Simulated Proxy");
        break;
    case ROLE_None:
        Role = FString("None");
        break;
    }
    FString RemoteRoleString = FString::Printf(TEXT("Remote Role: %s"), *Role);
    SetDisplayText(RemoteRoleString);
}

void UOverheadWidget::ShowPlayerName(APawn* InPawn)
{
    if (!InPawn->GetPlayerState())
    {
        UE_LOG(LogTemp, Error, TEXT("PlayerState NULL")); return;
    }
    FString Name = InPawn->GetPlayerState()->GetPlayerName();
    SetDisplayText(Name);
}

void UOverheadWidget::OnLevelRemovedFromWorld(ULevel* InLevel, UWorld* InWorld)
{
    RemoveFromParent();
    Super::OnLevelRemovedFromWorld(InLevel, InWorld);
}

