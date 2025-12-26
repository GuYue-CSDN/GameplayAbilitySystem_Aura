// Copyright  HuJiaHao


#include "Player/AuraPlayerController.h"
#include "EnhancedInputSubsystems.h"

AAuraPlayerController::AAuraPlayerController()
{
	bReplicates = true;
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
