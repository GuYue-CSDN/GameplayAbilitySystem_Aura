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
	AbilitySystemComponent = CreateDefaultSubobject<UAuraAbilitySystemComponent>("AbilitySystemComponent");\
	//开启 AbilitySystemComponent（ASC）网络同步的总开关
	AbilitySystemComponent->SetIsReplicated(true);
	//设置 GAS 中 “GameplayEffect（游戏玩法效果）” 的网络同步模式，核心作用是控制 “属性变化、效果持续状态” 等数据在客户端和服务器之间的同步规则
	//让 GAS 的 Effect 以 “混合同步” 的方式在网络中传输
	AbilitySystemComponent->SetReplicationMode(EGameplayEffectReplicationMode::Minimal);
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

void AAuraEnemy::BeginPlay()
{
	Super::BeginPlay();
	//初始化 AbilitySystemComponent（ASC）核心关联信息 的关键操作，作用是为 ASC 绑定「权威 Actor」和「拥有者 Actor」
	AbilitySystemComponent->InitAbilityActorInfo(this, this);
}
