#pragma once

#define TRACE_LENGTH 80000.f


UENUM(BlueprintType)
enum class EWeaponType : uint8
{
    EWT_AssaultRifle UMETA(DisplayName = "Assault Rifle"),
    EWT_RocketLauncher UMETA(DisplayName = "Rocket Launcher"),
    EWT_Pistol UMETA(DisplayName = "Pistol"),
    EWT_SubmachineGun UMETA(DisplayName = "Submachine Gun"),
    EWT_Shotgun UMETA(DisplayName = "Shotgun"),
    EWT_SniperRifle UMETA(DisplayName = "Sniper Rifle"),
    EWT_GrenadeLauncher UMETA(DisplayName = "Grenade Launcher"),
    EWT_Flag UMETA(DisplayName = "Flag"),

    EWT_MAX UMETA(DisplayName = "DefaultMAX")
};


UENUM(BlueprintType)
enum class EWeaponState : uint8
{
    EWS_Initial UMETA(DisplayName = "Initial State"),
    EWS_Equipped UMETA(DisplayName = "Equipped"),
    EWS_EquippedSecondary UMETA(DisplayName = "Equipped Secondary"),
    EWS_Dropped UMETA(DisplayName = "Dropped"),

    EWS_MAX UMETA(DisplayName = "DefaultMAX")
};


UENUM(BlueprintType)
enum class EFireType : uint8
{
    EFT_HitScan UMETA(DisplayName = "Hit Scan Weapon"),
    EFT_Projectile UMETA(DisplayName = "Projectile Weapon"),
    EFT_Shotgun UMETA(DisplayName = "Shotgun Weapon"),

    EFT_MAX UMETA(DisplayName = "DefaultMAX")
};