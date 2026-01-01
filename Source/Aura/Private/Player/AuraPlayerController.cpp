// Copyright  HuJiaHao


#include "Player/AuraPlayerController.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"
#include "Interaction/EnemyInterface.h"

AAuraPlayerController::AAuraPlayerController()
{
	bReplicates = true;
}

void AAuraPlayerController::PlayerTick(float DeltaTime)
{
	Super::PlayerTick(DeltaTime);
	CursorTrace();
}

void AAuraPlayerController::CursorTrace()
{
	//定义一个FHitResult类型的变量CursorHit，用于存储鼠标光标射线检测的结果
	FHitResult CursorHit;
	//从 “鼠标光标位置” 向游戏世界发射一条射线，检测 “可见层” 的对象，并将结果存入CursorHit
	GetHitResultUnderCursor(ECC_Visibility, false, CursorHit);
	//判断射线是否 “命中了阻挡对象”，若未命中则直接返回（终止后续逻辑）
	if (!CursorHit.bBlockingHit) return;
	
	LastActor = ThisActor;
	////将 “射线命中的 Actor” 尝试转换为IEnemyInterface接口类型（即判断该 Actor 是否实现了 “敌人接口”）
	ThisActor = Cast<IEnemyInterface>(CursorHit.GetActor());
	
	    /**
		* Line trace from cursor. There are several scenarios:
		* A. LastActor is null && ThisActor is null
		*     - Do nothing
		* B. LastActor is null && ThisActor is valid
		*     - Highlight ThisActor
		* C. LastActor is valid && ThisActor is null
		*     - UnHighlight LastActor
		* D. Both actors are valid, but LastActor != ThisActor
		*     - UnHighlight LastActor, and Highlight ThisActor
		* E. Both actors are valid, and are the same actor
		*     - Do nothing
		*/
	
	if (LastActor == nullptr)
	{
		if (ThisActor != nullptr)
		{
			// Case B
			ThisActor->HighLightActor();
		}
		else
		{
			// Case A - both are null, do nothing
		}
	}
	else // LastActor is valid
	{
		if (ThisActor == nullptr)
		{
			// Case C
			LastActor->UnHighLightActor();
		}
		else // both actors are valid
		{
			if (LastActor != ThisActor)
			{
				// Case D
				LastActor->UnHighLightActor();
				ThisActor->HighLightActor();
			}
			else
			{
				// Case E - do nothing
			}
		}
	}
	
}

void AAuraPlayerController::BeginPlay()
{
	Super::BeginPlay();
	check(AuraContext);
	//通过LocalPlayer（本地玩家）获取增强输入子系统的实例（每个本地玩家对应一个子系统）。
	UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer());
	check(Subsystem);
	//将AuraContext（自定义的 IMC 资产）激活，并设置优先级为 0（优先级数值越高，映射越优先）。
	Subsystem->AddMappingContext(AuraContext, 0);
	
	bShowMouseCursor = true;
	DefaultMouseCursor = EMouseCursor::Default;
	
	FInputModeGameAndUI InputModeData;
	//设置鼠标不锁定在视口内（默认游戏模式会锁定鼠标，避免移出窗口；UI 模式下通常不锁定）。
	InputModeData.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);
	//捕获鼠标时不隐藏光标（“捕获” 指鼠标焦点在游戏窗口内，此设置确保光标始终可见）。
	InputModeData.SetHideCursorDuringCapture(false);
	SetInputMode(InputModeData);
}

void AAuraPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();
	//将通用的InputComponent指针强制转换为增强输入专属的UEnhancedInputComponent类型，并确保转换绝对成功
	UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(InputComponent);
	
	EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &AAuraPlayerController::Move);
}

void AAuraPlayerController::Move(const FInputActionValue& InputActionValue)
{
	const FVector2D InputAxisVector = InputActionValue.Get<FVector2D>();
	const FRotator Rotation = GetControlRotation();
	const FRotator YawRotation(0.f, Rotation.Yaw, 0.f);
	
	const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
	const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
	
	if (APawn* ControlledPawn = GetPawn<APawn>())
	{
		ControlledPawn->AddMovementInput(ForwardDirection, InputAxisVector.Y);
		ControlledPawn->AddMovementInput(RightDirection, InputAxisVector.X);
	}
}


