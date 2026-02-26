// Copyright  HuJiaHao


#include "AbilitySystem/AuraAbilitySystemComponent.h"

#include "AuraGameplayTags.h"

void UAuraAbilitySystemComponent::AbilityActorInfoSet()
{
	//OnGameplayEffectAppliedDelegateToSelf：这是 GAS 内置的多播委托，当有游戏效果（Gameplay Effect）应用到当前 ASC 自身时，该委托会被自动广播。
	OnGameplayEffectAppliedDelegateToSelf.AddUObject(this, &UAuraAbilitySystemComponent::EffectApplied);
	
}

void UAuraAbilitySystemComponent::EffectApplied(UAbilitySystemComponent* AbilitySystemComponent,
                                                const FGameplayEffectSpec& EffectSpec, FActiveGameplayEffectHandle ActiveEffectHandle)
{
	FGameplayTagContainer TagContainer;
	//从效果规范中提取出所有的资产标签（Asset Tags），并存储到 TagContainer 容器中。
	EffectSpec.GetAllAssetTags(TagContainer);
	//通过项目自定义的多播委托 EffectAssetTags，将包含所有标签的容器广播出去。任何绑定了这个委托的对象（如 UI 控制器）都会收到这些标签
	EffectAssetTags.Broadcast(TagContainer);
}
