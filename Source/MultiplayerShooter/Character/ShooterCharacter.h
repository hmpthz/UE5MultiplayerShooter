#pragma once
#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Components/TimelineComponent.h"
#include "../MultiplayerShooter.h"
#include "../MetaTypes/TurningInPlace.h"
#include "../MetaTypes/CombatState.h"
#include "../MetaTypes/Team.h"
#include "ShooterCharacter.generated.h"


UCLASS()
class MULTIPLAYERSHOOTER_API AShooterCharacter : public ACharacter
{
    GENERATED_BODY()

public:
    AShooterCharacter();
    virtual void Tick(float DeltaTime) override;
    virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
    virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
    virtual void PostInitializeComponents() override;

protected:
    virtual void BeginPlay() override;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera)
    class USpringArmComponent* SpringArm;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera)
    class UCameraComponent* Camera3rd;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
    class UWidgetComponent* OverheadWidget;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
    class UCombatComponent* Combat;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
    class UItemComponent* ItemComp;

#pragma region Movement

    void MoveForward(float Value);
    void MoveRight(float Value);
    void Turn(float Value);
    void LookUp(float Value);
    virtual void Jump() override;
    void CrouchButtonPressed();
    void SprintButtonPressed();
    void SprintButtonReleased();

#pragma endregion

    void EquipButtonPressed();
    void AimButtonPressed();
    void AimButtonReleased();
    void FireButtonPressed();
    void FireButtonReleased();
    void ReloadButtonPressed();
    void GrenadeButtonPressed();


#pragma region LagCompensation

    /* Hit boxes for server-side rewind */
    UPROPERTY()
    TMap<FName, class UBoxComponent*> HitCollisionBoxes;

    UPROPERTY(EditAnywhere)
    class UBoxComponent* head;

    UPROPERTY(EditAnywhere)
    UBoxComponent* pelvis;

    UPROPERTY(EditAnywhere)
    UBoxComponent* spine_02;

    UPROPERTY(EditAnywhere)
    UBoxComponent* spine_03;

    UPROPERTY(EditAnywhere)
    UBoxComponent* upperarm_l;

    UPROPERTY(EditAnywhere)
    UBoxComponent* upperarm_r;

    UPROPERTY(EditAnywhere)
    UBoxComponent* lowerarm_l;

    UPROPERTY(EditAnywhere)
    UBoxComponent* lowerarm_r;

    UPROPERTY(EditAnywhere)
    UBoxComponent* hand_l;

    UPROPERTY(EditAnywhere)
    UBoxComponent* hand_r;

    UPROPERTY(EditAnywhere)
    UBoxComponent* backpack;

    UPROPERTY(EditAnywhere)
    UBoxComponent* blanket;

    UPROPERTY(EditAnywhere)
    UBoxComponent* thigh_l;

    UPROPERTY(EditAnywhere)
    UBoxComponent* thigh_r;

    UPROPERTY(EditAnywhere)
    UBoxComponent* calf_l;

    UPROPERTY(EditAnywhere)
    UBoxComponent* calf_r;

    UPROPERTY(EditAnywhere)
    UBoxComponent* foot_l;

    UPROPERTY(EditAnywhere)
    UBoxComponent* foot_r;

#pragma endregion
};
