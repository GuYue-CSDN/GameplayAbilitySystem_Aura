// Copyright  HuJiaHao


#include "Player/AuraPlayerState.h"
#include "AbilitySystem/AuraAttributeSet.h"

AAuraPlayerState::AAuraPlayerState()
{
	//初始化 AbilitySystemComponent（能力系统组件）
	AbilitySystemComponent = CreateDefaultSubobject<UAuraAbilitySystemComponent>("AbilitySystemComponent");
	//开启 AbilitySystemComponent（ASC）网络同步
	AbilitySystemComponent->SetIsReplicated(true);
	//设置 GAS 中 “GameplayEffect（游戏玩法效果）” 的网络同步模式，核心作用是控制 “属性变化、效果持续状态” 等数据在客户端和服务器之间的同步规则
	//让 GAS 的 Effect 以 “混合同步” 的方式在网络中传输
	AbilitySystemComponent->SetReplicationMode(EGameplayEffectReplicationMode::Mixed);
	
	//初始化 AttributeSet
	AttributeSet = CreateDefaultSubobject<UAuraAttributeSet>("AttributeSet");
	
	//设置网络更新频率
	NetUpdateFrequency = 100.f;
}

UAuraAbilitySystemComponent* AAuraPlayerState::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent;
}
