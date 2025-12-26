#include "ZCharacterPlayer.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "InputMappingContext.h"
#include "InputActionValue.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"

AZCharacterPlayer::AZCharacterPlayer()
{
	// Default Options
	PrimaryActorTick.bCanEverTick = true;

	// Character Movement Settings
	GetCharacterMovement()->bOrientRotationToMovement = false;

	// FPS Camera Settings
	FPSCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("FirstPersonCamera"));
	check(FPSCameraComponent != nullptr);

	FPSCameraComponent->SetupAttachment(CastChecked<USceneComponent, UCapsuleComponent>(GetCapsuleComponent()));
	FPSCameraComponent->SetRelativeLocation(FVector(0.0f, 0.0f, 50.0f + BaseEyeHeight));

	FPSCameraComponent->bUsePawnControlRotation = true;
}

void AZCharacterPlayer::BeginPlay()
{
	Super::BeginPlay();

	InitializeCharacterControl();
}

void AZCharacterPlayer::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AZCharacterPlayer::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	UEnhancedInputComponent* Input = Cast<UEnhancedInputComponent>(PlayerInputComponent);

	Input->BindAction(MoveAction, ETriggerEvent::Triggered, this, &AZCharacterPlayer::Move);
	Input->BindAction(LookAction, ETriggerEvent::Triggered, this, &AZCharacterPlayer::Look);
	Input->BindAction(JumpAction, ETriggerEvent::Started, this, &AZCharacterPlayer::StartJump);
	Input->BindAction(JumpAction, ETriggerEvent::Completed, this, &AZCharacterPlayer::StopJump);
}

/// <summary>
/// 입력 매핑 컨텍스트를 포함하여 캐릭터 조작 관련 설정을 수행합니다.
/// </summary>
void AZCharacterPlayer::InitializeCharacterControl()
{
	APlayerController* PlayerController = CastChecked<APlayerController>(GetController());
	if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
	{
		Subsystem->ClearAllMappings();
		if (!InputMapping.IsNull())
		{
			Subsystem->AddMappingContext(InputMapping.LoadSynchronous(), 0);
		}
	}
}

/// <summary>
/// 캐릭터 이동을 수행합니다.
/// </summary>
/// <param name="Value">이동 입력 값</param>
void AZCharacterPlayer::Move(const FInputActionValue& Value)
{
	FVector2D MovementVector = Value.Get<FVector2D>();

	const FRotator Rotation = Controller->GetControlRotation();
	const FRotator YawPosition(0, Rotation.Yaw, 0);

	// 어디가 앞인지 찾고, 플레이어가 그쪽으로 움직이려 함을 기록합니다.
	FVector ForewardDirection = FRotationMatrix(YawPosition).GetUnitAxis(EAxis::X);
	FVector RightDirection = FRotationMatrix(YawPosition).GetUnitAxis(EAxis::Y);

	AddMovementInput(ForewardDirection, MovementVector.Y);
	AddMovementInput(RightDirection, MovementVector.X);

	OnMove(MovementVector.X, MovementVector.Y);
}

/// <summary>
/// 캐릭터가 바라보는 방향을 구현합니다.
/// </summary>
/// <param name="Value">카메라 입력 값</param>
void AZCharacterPlayer::Look(const FInputActionValue& Value)
{
	FVector2D LookVector = Value.Get<FVector2D>();

	AddControllerYawInput(LookVector.X);
	AddControllerPitchInput(LookVector.Y);
}

/// <summary>
/// 점프 버튼이 눌러졌을 때 실행합니다.
/// </summary>
void AZCharacterPlayer::StartJump()
{
	bPressedJump = true;
}

/// <summary>
/// 점프 버튼을 뗐을 때 실행합니다.
/// </summary>
void AZCharacterPlayer::StopJump()
{
	bPressedJump = false;
}
