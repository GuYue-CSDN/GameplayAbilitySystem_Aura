// Copyright  HuJiaHao


#include "Character/AuraEnemy.h"

#include "AbilitySystemComponent.h"
#include "AbilitySystem/AuraAbilitySystemComponent.h"
#include "AbilitySystem/AuraAttributeSet.h"
#include "AUra/Aura.h"


AAuraEnemy::AAuraEnemy()
{
	//将角色的 Mesh（网格体）对 “可见性检测通道（ECC_Visibility）” 的碰撞响应设置为 “阻挡（ECR_Block）
	GetMesh()->SetCollisionResponseToChannel(ECC_Visibility,ECR_Block);
	
	//初始化 AbilitySystemComponent（能力系统组件）
	AbilitySystemComponent = CreateDefaultSubobject<UAuraAbilitySystemComponent>("AbilitySystemComponent");
	AbilitySystemComponent->SetIsReplicated(true);
	//初始化 AttributeSet
	AttributeSet = CreateDefaultSubobject<UAuraAttributeSet>("AttributeSet");
}

void AAuraEnemy::HighLightActor()
{
	GetMesh()->SetRenderCustomDepth(true);
	GetMesh()->SetCustomDepthStencilValue(CUSTOM_DEPTH_RED);
	Weapon->SetRenderCustomDepth(true);
	Weapon->SetCustomDepthStencilValue(CUSTOM_DEPTH_RED);
}

void AAuraEnemy::UnHighLightActor()
{
	GetMesh()->SetRenderCustomDepth(false);
}
