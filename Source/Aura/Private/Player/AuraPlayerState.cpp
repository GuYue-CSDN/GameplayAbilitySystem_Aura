// Copyright  HuJiaHao


#include "Player/AuraPlayerState.h"
#include "AbilitySystem/AuraAbilitySystemComponent.h"
#include "AbilitySystem/AuraAttributeSet.h"

AAuraPlayerState::AAuraPlayerState()
{
	//初始化 AbilitySystemComponent（能力系统组件）
	AbilitySystemComponent = CreateDefaultSubobject<UAuraAbilitySystemComponent>("AbilitySystemComponent");
	AbilitySystemComponent->SetIsReplicated(true);
	//初始化 AttributeSet
	AttributeSet = CreateDefaultSubobject<UAuraAttributeSet>("AttributeSet");
	
	//设置网络更新频率
	NetUpdateFrequency = 100.f;
}

UAbilitySystemComponent* AAuraPlayerState::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent;
}
