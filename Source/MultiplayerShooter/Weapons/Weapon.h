#pragma once
#include "CoreMinimal.h"
#include "../Items/PickUpBase.h"
#include "../MetaTypes/WeaponTypes.h"
#include "../MetaTypes/Team.h"
#include "Weapon.generated.h"


/*
    Weapon is a pick up item with skeletal mesh.
*/
UCLASS()
class MULTIPLAYERSHOOTER_API AWeapon : public APickUpBase
{
    GENERATED_BODY()
    
public:	
    AWeapon();

protected:
    virtual void BeginPlay() override;
    virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

    UPROPERTY(EditAnywhere, BlueprintReadOnly)
    class USkeletalMeshComponent* Mesh;

    UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
    EWeaponState WeaponState;

#pragma region Properties
    /* Weapon properties */

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Weapon Properties")
    EWeaponType WeaponType;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Weapon Properties")
    EFireType FireType;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Weapon Properties")
    float Damage = 20.f;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Weapon Properties")
    float HeadShotDamage = 40.f;

    UPROPERTY(EditAnywhere, Category = "Weapon Properties")
    float FireDelay = .15f;

    UPROPERTY(EditAnywhere, Category = "Weapon Properties")
    bool bAutomatic = true;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Weapon Properties")
    int32 MagCapacity;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Weapon Properties")
    int32 Ammo;

    UPROPERTY(EditAnywhere, Category = "Weapon Properties")
    float ZoomedFOV = 30.f;

    UPROPERTY(EditAnywhere, Category = "Weapon Properties")
    float ZoomInterpSpeed = 20.f;

    UPROPERTY(EditAnywhere, Category = "Weapon Scatter")
    bool bUseScatter = false;

    UPROPERTY(EditAnywhere, Category = "Weapon Scatter")
    float DistanceToSphere = 800.f;

    UPROPERTY(EditAnywhere, Category = "Weapon Scatter")
    float SphereRadius = 75.f;

#pragma endregion

    /* Additional assets */

    UPROPERTY(EditAnywhere, Category = Assets)
    class USoundCue* EquipSound;

    UPROPERTY(EditAnywhere, Category = Assets)
    class UAnimationAsset* FireAnimation;

    /* Textures for the weapon crosshairs */

    UPROPERTY(EditAnywhere, Category = Assets)
    class UTexture2D* CrosshairsCenter;

    UPROPERTY(EditAnywhere, Category = Assets)
    UTexture2D* CrosshairsLeft;

    UPROPERTY(EditAnywhere, Category = Assets)
    UTexture2D* CrosshairsRight;

    UPROPERTY(EditAnywhere, Category = Assets)
    UTexture2D* CrosshairsTop;

    UPROPERTY(EditAnywhere, Category = Assets)
    UTexture2D* CrosshairsBottom;

    void EnableCustomDepth(bool bEnable);

public:
    /* Some getters / setters */

    FORCEINLINE USkeletalMeshComponent* GetMesh() const { return Mesh; }
};
