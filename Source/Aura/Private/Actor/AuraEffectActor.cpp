// Copyright  HuJiaHao


#include "Actor/AuraEffectActor.h"
#include "AbilitySystemBlueprintLibrary.h"
#include "AbilitySystemComponent.h"


AAuraEffectActor::AAuraEffectActor()
{
	PrimaryActorTick.bCanEverTick = false;
	
	SetRootComponent(CreateDefaultSubobject<USceneComponent>("SceneRoot"));
}

void AAuraEffectActor::BeginPlay()
{
	Super::BeginPlay();
	
}

void AAuraEffectActor::ApplyEffectToTarget(AActor* TargetActor, TSubclassOf<UGameplayEffect> GameplayEffectClass)
{
	UAbilitySystemComponent* TargetASC = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(TargetActor);
	if (TargetASC == nullptr) return;

	check(GameplayEffectClass);
	
	//创建效果上下文（Context）
	//MakeEffectContext()：创建一个 FGameplayEffectContextHandle，用于存储效果的上下文信息（比如效果来源、触发位置等）。
	//AddSourceObject(this)：将当前对象（通常是技能发起者或效果施加者）设置为效果的 “源对象”，方便在效果逻辑中追溯来源。
	FGameplayEffectContextHandle EffectContextHandle = TargetASC->MakeEffectContext();
	EffectContextHandle.AddSourceObject(this);
	
	//生成效果规格（Spec）,效果规格包含了效果的所有参数（如伤害值、持续时间、叠加规则等）
	const FGameplayEffectSpecHandle EffectSpecHandle = TargetASC->MakeOutgoingSpec(GameplayEffectClass, 1.f, EffectContextHandle);
	//ApplyGameplayEffectSpecToSelf()：将生成的效果规格应用到目标的 ASC 上，完成效果的施加（比如造成伤害、恢复生命值等）。
	TargetASC->ApplyGameplayEffectSpecToSelf(*EffectSpecHandle.Data.Get());
}


