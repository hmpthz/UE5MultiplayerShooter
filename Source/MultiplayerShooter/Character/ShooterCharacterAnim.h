#pragma once
#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "../MetaTypes/TurningInPlace.h"
#include "../MetaTypes/CombatState.h"
#include "ShooterCharacterAnim.generated.h"


UCLASS()
class MULTIPLAYERSHOOTER_API UShooterCharacterAnim : public UAnimInstance
{
    GENERATED_BODY()
public:
    virtual void NativeInitializeAnimation() override;
    virtual void NativeUpdateAnimation(float DeltaTime) override;

protected:
    UPROPERTY(BlueprintReadOnly, Category = Character, meta = (AllowPrivateAccess = "true"))
    class AShooterCharacter* Character;

    UPROPERTY(BlueprintReadOnly, Category = Movement, meta = (AllowPrivateAccess = "true"))
    float Speed;

    UPROPERTY(BlueprintReadOnly, Category = Movement, meta = (AllowPrivateAccess = "true"))
    float YawOffset;

    UPROPERTY(BlueprintReadOnly, Category = Movement, meta = (AllowPrivateAccess = "true"))
    bool bIsInAir;

    UPROPERTY(BlueprintReadOnly, Category = Movement, meta = (AllowPrivateAccess = "true"))
    bool bIsAccelerating;

    UPROPERTY(BlueprintReadOnly, Category = Movement, meta = (AllowPrivateAccess = "true"))
    bool bIsCrouched;

    UPROPERTY(BlueprintReadOnly, Category = Movement, meta = (AllowPrivateAccess = "true"))
    float Lean;

    // class AWeapon* EquippedWeapon;

    UPROPERTY(BlueprintReadOnly, Category = Movement, meta = (AllowPrivateAccess = "true"))
    bool bWeaponEquipped;

    UPROPERTY(BlueprintReadOnly, Category = Movement, meta = (AllowPrivateAccess = "true"))
    bool bAiming;

    UPROPERTY(BlueprintReadOnly, Category = Movement, meta = (AllowPrivateAccess = "true"))
    bool bUseAimOffsets;

    UPROPERTY(BlueprintReadOnly, Category = Movement, meta = (AllowPrivateAccess = "true"))
    float AO_Yaw;

    UPROPERTY(BlueprintReadOnly, Category = Movement, meta = (AllowPrivateAccess = "true"))
    float AO_Pitch;

    FRotator CharacterRotationLastFrame;
    FRotator CharacterRotation;
    FRotator DeltaRotation;

    UPROPERTY(BlueprintReadOnly, Category = Movement, meta = (AllowPrivateAccess = "true"))
    ETurningInPlace TurningInPlace;

    UPROPERTY(BlueprintReadOnly, Category = Movement, meta = (AllowPrivateAccess = "true"))
    FTransform LeftHandTransform;

    UPROPERTY(BlueprintReadOnly, Category = Movement, meta = (AllowPrivateAccess = "true"))
    FRotator RightHandRotation;

    UPROPERTY(BlueprintReadOnly, Category = Movement, meta = (AllowPrivateAccess = "true"))
    bool bLocallyControlled;

    UPROPERTY(BlueprintReadOnly, Category = Movement, meta = (AllowPrivateAccess = "true"))
    bool bRotateRootBone;

    UPROPERTY(BlueprintReadOnly, Category = Movement, meta = (AllowPrivateAccess = "true"))
    bool bElimmed;

    UPROPERTY(BlueprintReadOnly, Category = Movement, meta = (AllowPrivateAccess = "true"))
    bool bUseFABRIK;

    UPROPERTY(BlueprintReadOnly, Category = Movement, meta = (AllowPrivateAccess = "true"))
    bool bTransformRightHand;

    UPROPERTY(BlueprintReadOnly, Category = Movement, meta = (AllowPrivateAccess = "true"))
    bool bHoldingTheFlag;
};
