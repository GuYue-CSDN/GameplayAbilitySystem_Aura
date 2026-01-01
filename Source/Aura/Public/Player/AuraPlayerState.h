// Copyright  HuJiaHao

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemInterface.h"
#include "GameFramework/PlayerState.h"
#include "AuraPlayerState.generated.h"


class UAuraAbilitySystemComponent;
class UAttributeSet;
/**
 * 
 */
UCLASS()
class AURA_API AAuraPlayerState : public APlayerState, public IAbilitySystemInterface
{
	GENERATED_BODY()
public:
	AAuraPlayerState();
	//让角色类（AAuraCharacterBase）符合 GAS 的规范，向引擎暴露 “能力系统组件” 的访问入口
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;
	UAttributeSet* GetAttributeSet() const {return AttributeSet;}
protected:
	UPROPERTY();
	TObjectPtr<UAuraAbilitySystemComponent> AbilitySystemComponent;
	UPROPERTY();
	TObjectPtr<UAttributeSet> AttributeSet;
};
