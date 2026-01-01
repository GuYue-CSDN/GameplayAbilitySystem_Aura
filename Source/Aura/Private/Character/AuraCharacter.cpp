// Copyright  HuJiaHao


#include "Character/AuraCharacter.h"

#include "GameFramework/CharacterMovementComponent.h"

AAuraCharacter::AAuraCharacter()
{
	//开启 “角色自动转向移动方向”
	GetCharacterMovement()->bOrientRotationToMovement = true;
	//设置角色自动转向的 “旋转速度”
	GetCharacterMovement()->RotationRate = FRotator(0.f, 400.0f, 0.f);
	//将角色移动约束在 “平面” 内（通常是 XY 平面，即地面）
	GetCharacterMovement()->bConstrainToPlane = true;
	//角色生成时，自动 “吸附” 到约束平面（配合bConstrainToPlane使用）
	GetCharacterMovement()->bSnapToPlaneAtStart = true;
	
	//bUseControllerRotationPitch/Yaw/Roll是ACharacter的成员变量，控制 “角色是否跟随 PlayerController 的旋转”。
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;
}
