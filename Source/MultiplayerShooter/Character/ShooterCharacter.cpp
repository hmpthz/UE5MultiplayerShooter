#include "ShooterCharacter.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Components/WidgetComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/BoxComponent.h"
#include "TimerManager.h"
#include "Net/UnrealNetwork.h"
#include "Kismet/KismetMathLibrary.h"
#include "Kismet/GameplayStatics.h"
#include "Sound/SoundCue.h"
#include "Particles/ParticleSystemComponent.h"
#include "NiagaraComponent.h"
#include "NiagaraFunctionLibrary.h"

#include "ShooterCharacterAnim.h"
#include "CombatComponent.h"
#include "ItemComponent.h"


AShooterCharacter::AShooterCharacter()
{
    PrimaryActorTick.bCanEverTick = true;
    bUseControllerRotationYaw = false;

    SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
    SpringArm->SetupAttachment(GetMesh());
    SpringArm->TargetArmLength = 320.f;
    SpringArm->bUsePawnControlRotation = true;

    Camera3rd = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera3rd"));
    Camera3rd->SetupAttachment(SpringArm, USpringArmComponent::SocketName);
    Camera3rd->bUsePawnControlRotation = false;

    OverheadWidget = CreateDefaultSubobject<UWidgetComponent>(TEXT("OverheadWidget"));
    OverheadWidget->SetupAttachment(RootComponent);

    Combat = CreateDefaultSubobject<UCombatComponent>(TEXT("Combat"));
    Combat->SetIsReplicated(true);

    ItemComp = CreateDefaultSubobject<UItemComponent>(TEXT("ItemComponent"));
    ItemComp->SetupAttachment(RootComponent);

    GetCharacterMovement()->bOrientRotationToMovement = true;
    GetCharacterMovement()->NavAgentProps.bCanCrouch = true;
    GetCharacterMovement()->RotationRate = FRotator(0.f, 540.f, 0.f);

    GetCapsuleComponent()->SetCollisionResponseToChannel(ECollisionChannel::ECC_Camera, ECollisionResponse::ECR_Ignore);
    GetMesh()->SetRelativeLocation(FVector(0, 0, -88));
    GetMesh()->SetRelativeRotation(FRotator(0, -90, 0));
    GetMesh()->SetCollisionObjectType(ECC_SkeletalMesh);
    GetMesh()->SetCollisionResponseToChannel(ECollisionChannel::ECC_Camera, ECollisionResponse::ECR_Ignore);
    GetMesh()->SetCollisionResponseToChannel(ECollisionChannel::ECC_Visibility, ECollisionResponse::ECR_Block);


    head = CreateDefaultSubobject<UBoxComponent>(TEXT("head"));
    head->SetupAttachment(GetMesh(), FName("head"));
    HitCollisionBoxes.Add(FName("head"), head);

    pelvis = CreateDefaultSubobject<UBoxComponent>(TEXT("pelvis"));
    pelvis->SetupAttachment(GetMesh(), FName("pelvis"));
    HitCollisionBoxes.Add(FName("pelvis"), pelvis);

    spine_02 = CreateDefaultSubobject<UBoxComponent>(TEXT("spine_02"));
    spine_02->SetupAttachment(GetMesh(), FName("spine_02"));
    HitCollisionBoxes.Add(FName("spine_02"), spine_02);

    spine_03 = CreateDefaultSubobject<UBoxComponent>(TEXT("spine_03"));
    spine_03->SetupAttachment(GetMesh(), FName("spine_03"));
    HitCollisionBoxes.Add(FName("spine_03"), spine_03);

    upperarm_l = CreateDefaultSubobject<UBoxComponent>(TEXT("upperarm_l"));
    upperarm_l->SetupAttachment(GetMesh(), FName("upperarm_l"));
    HitCollisionBoxes.Add(FName("upperarm_l"), upperarm_l);

    upperarm_r = CreateDefaultSubobject<UBoxComponent>(TEXT("upperarm_r"));
    upperarm_r->SetupAttachment(GetMesh(), FName("upperarm_r"));
    HitCollisionBoxes.Add(FName("upperarm_r"), upperarm_r);

    lowerarm_l = CreateDefaultSubobject<UBoxComponent>(TEXT("lowerarm_l"));
    lowerarm_l->SetupAttachment(GetMesh(), FName("lowerarm_l"));
    HitCollisionBoxes.Add(FName("lowerarm_l"), lowerarm_l);

    lowerarm_r = CreateDefaultSubobject<UBoxComponent>(TEXT("lowerarm_r"));
    lowerarm_r->SetupAttachment(GetMesh(), FName("lowerarm_r"));
    HitCollisionBoxes.Add(FName("lowerarm_r"), lowerarm_r);

    hand_l = CreateDefaultSubobject<UBoxComponent>(TEXT("hand_l"));
    hand_l->SetupAttachment(GetMesh(), FName("hand_l"));
    HitCollisionBoxes.Add(FName("hand_l"), hand_l);

    hand_r = CreateDefaultSubobject<UBoxComponent>(TEXT("hand_r"));
    hand_r->SetupAttachment(GetMesh(), FName("hand_r"));
    HitCollisionBoxes.Add(FName("hand_r"), hand_r);

    blanket = CreateDefaultSubobject<UBoxComponent>(TEXT("blanket"));
    blanket->SetupAttachment(GetMesh(), FName("backpack"));
    HitCollisionBoxes.Add(FName("blanket"), blanket);

    backpack = CreateDefaultSubobject<UBoxComponent>(TEXT("backpack"));
    backpack->SetupAttachment(GetMesh(), FName("backpack"));
    HitCollisionBoxes.Add(FName("backpack"), backpack);

    thigh_l = CreateDefaultSubobject<UBoxComponent>(TEXT("thigh_l"));
    thigh_l->SetupAttachment(GetMesh(), FName("thigh_l"));
    HitCollisionBoxes.Add(FName("thigh_l"), thigh_l);

    thigh_r = CreateDefaultSubobject<UBoxComponent>(TEXT("thigh_r"));
    thigh_r->SetupAttachment(GetMesh(), FName("thigh_r"));
    HitCollisionBoxes.Add(FName("thigh_r"), thigh_r);

    calf_l = CreateDefaultSubobject<UBoxComponent>(TEXT("calf_l"));
    calf_l->SetupAttachment(GetMesh(), FName("calf_l"));
    HitCollisionBoxes.Add(FName("calf_l"), calf_l);

    calf_r = CreateDefaultSubobject<UBoxComponent>(TEXT("calf_r"));
    calf_r->SetupAttachment(GetMesh(), FName("calf_r"));
    HitCollisionBoxes.Add(FName("calf_r"), calf_r);

    foot_l = CreateDefaultSubobject<UBoxComponent>(TEXT("foot_l"));
    foot_l->SetupAttachment(GetMesh(), FName("foot_l"));
    HitCollisionBoxes.Add(FName("foot_l"), foot_l);

    foot_r = CreateDefaultSubobject<UBoxComponent>(TEXT("foot_r"));
    foot_r->SetupAttachment(GetMesh(), FName("foot_r"));
    HitCollisionBoxes.Add(FName("foot_r"), foot_r);

    for (auto Box : HitCollisionBoxes)
    {
        if (Box.Value)
        {
            Box.Value->SetCollisionObjectType(ECC_HitBox);
            Box.Value->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);
            Box.Value->SetCollisionResponseToChannel(ECC_HitBox, ECollisionResponse::ECR_Block);
            Box.Value->SetCollisionEnabled(ECollisionEnabled::NoCollision);
        }
    }
}

void AShooterCharacter::BeginPlay()
{
    Super::BeginPlay();
    
}

void AShooterCharacter::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
}

void AShooterCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
    Super::SetupPlayerInputComponent(PlayerInputComponent);

    PlayerInputComponent->BindAxis("MoveForward", this, &ThisClass::MoveForward);
    PlayerInputComponent->BindAxis("MoveRight", this, &ThisClass::MoveRight);
    PlayerInputComponent->BindAxis("Turn", this, &ThisClass::Turn);
    PlayerInputComponent->BindAxis("LookUp", this, &ThisClass::LookUp);
    PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ThisClass::Jump);
    PlayerInputComponent->BindAction("Crouch", IE_Pressed, this, &ThisClass::CrouchButtonPressed);
    PlayerInputComponent->BindAction("Sprint", IE_Pressed, this, &ThisClass::SprintButtonPressed);
    PlayerInputComponent->BindAction("Sprint", IE_Released, this, &ThisClass::SprintButtonReleased);

    PlayerInputComponent->BindAction("Equip", IE_Pressed, this, &ThisClass::EquipButtonPressed);
    PlayerInputComponent->BindAction("Aim", IE_Pressed, this, &ThisClass::AimButtonPressed);
    PlayerInputComponent->BindAction("Aim", IE_Released, this, &ThisClass::AimButtonReleased);
    PlayerInputComponent->BindAction("Fire", IE_Pressed, this, &ThisClass::FireButtonPressed);
    PlayerInputComponent->BindAction("Fire", IE_Released, this, &ThisClass::FireButtonReleased);
    PlayerInputComponent->BindAction("Reload", IE_Pressed, this, &ThisClass::ReloadButtonPressed);
    PlayerInputComponent->BindAction("ThrowGrenade", IE_Pressed, this, &ThisClass::GrenadeButtonPressed);
}

void AShooterCharacter::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
    Super::GetLifetimeReplicatedProps(OutLifetimeProps);
}

void AShooterCharacter::PostInitializeComponents()
{
    Super::PostInitializeComponents();
}

void AShooterCharacter::MoveForward(float Value)
{
    if (Controller && Value != 0.f)
    {
        const FRotator YawRotation(0.f, Controller->GetControlRotation().Yaw, 0.f);
        const FVector Direction(FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X));
        AddMovementInput(Direction, Value);
    }
}

void AShooterCharacter::MoveRight(float Value)
{
    if (Controller && Value != 0.f)
    {
        const FRotator YawRotation(0.f, Controller->GetControlRotation().Yaw, 0.f);
        const FVector Direction(FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y));
        AddMovementInput(Direction, Value);
    }
}

void AShooterCharacter::Turn(float Value)
{
    AddControllerYawInput(Value);
}

void AShooterCharacter::LookUp(float Value)
{
    AddControllerPitchInput(Value);
}

void AShooterCharacter::Jump()
{
    if (bIsCrouched)
    {
        UnCrouch();
    }
    else
    {
        Super::Jump();
    }
}

void AShooterCharacter::CrouchButtonPressed()
{
    if (bIsCrouched)
    {
        UnCrouch();
    }
    else
    {
        Crouch();
    }
}

void AShooterCharacter::SprintButtonPressed()
{
}

void AShooterCharacter::SprintButtonReleased()
{
}

void AShooterCharacter::EquipButtonPressed()
{
}

void AShooterCharacter::AimButtonPressed()
{
}

void AShooterCharacter::AimButtonReleased()
{
}

void AShooterCharacter::FireButtonPressed()
{
}

void AShooterCharacter::FireButtonReleased()
{
}

void AShooterCharacter::ReloadButtonPressed()
{
}

void AShooterCharacter::GrenadeButtonPressed()
{
}
