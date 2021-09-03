// Fill out your copyright notice in the Description page of Project Settings.


#include "Units/Components/RTSAIHealthComponent.h"
#include "Perception/AISense_Damage.h"


DEFINE_LOG_CATEGORY_STATIC(LogRTSAIHealthComponent, All, All);
// Sets default values for this component's properties
URTSAIHealthComponent::URTSAIHealthComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void URTSAIHealthComponent::BeginPlay()
{
	Super::BeginPlay();

	
	SetHealth(MaxHealth);
	AActor* ComponentOwner = GetOwner();
	if (ComponentOwner)
	{
		ComponentOwner->OnTakeAnyDamage.AddDynamic(this, &URTSAIHealthComponent::OnTakeAnyDamage);
		ComponentOwner->OnTakePointDamage.AddDynamic(this, &URTSAIHealthComponent::OnTakePointDamage);
		ComponentOwner->OnTakeRadialDamage.AddDynamic(this, &URTSAIHealthComponent::OnTakeRadialDamage);
		
	}
	
	
}


// Called every frame
void URTSAIHealthComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void URTSAIHealthComponent::SetHealth(float NewHealth)
{
	const auto NextHealth = FMath::Clamp(NewHealth, 0.0f, MaxHealth);
	const auto HealthDelta = NextHealth - Health;
	
	Health = NextHealth;
	OnHealthChanged.Broadcast(Health, HealthDelta);
	
}

void URTSAIHealthComponent::OnTakeAnyDamage(AActor* DamagedActor, float Damage, const class UDamageType* DamageType,
                                          class AController* InstigatedBy, AActor* DamageCauser)
{
	UE_LOG(LogRTSAIHealthComponent, Display, TEXT("On Any Damage: %f"), Damage);
	
	
}

void URTSAIHealthComponent::OnTakePointDamage(AActor* DamagedActor, float Damage, class AController* InstigatedBy, FVector HitLocation, class UPrimitiveComponent* FHitComponent, FName BoneName, FVector ShotFromDirection, const class UDamageType* DamageType, AActor* DamageCauser )
{
	const auto FinalDamage = Damage /** GetPointDamageModifier(DamagedActor, BoneName)*/;
 	
	UE_LOG(LogRTSAIHealthComponent, Display, TEXT("On Point Damage: %f, bone: %s"), FinalDamage, *BoneName.ToString());

	ApplyDamage(FinalDamage, InstigatedBy);
	
}


void  URTSAIHealthComponent::OnTakeRadialDamage(AActor* DamagedActor, float Damage, const class UDamageType* DamageType, FVector Origin, FHitResult HitInfo, class AController* InstigatedBy, AActor* DamageCauser )
{
	UE_LOG(LogRTSAIHealthComponent, Display, TEXT("On Radial Damage: %f"), Damage);
	
	ApplyDamage(Damage, InstigatedBy);
}

void URTSAIHealthComponent::ApplyDamage(float Damage, AController* InstigatedBy)
{
	if (Damage <= 0.0f || IsDead() || !GetWorld()) return;
	
	SetHealth(Health - Damage);

	if (IsDead())
	{
	
		OnDeath.Broadcast();
	}

	
	ReportDamageEvent(Damage,InstigatedBy);
}

void URTSAIHealthComponent::ReportDamageEvent(float Damage, AController* InstigatedBy)
{
	if(!GetWorld() || ! GetOwner() || !InstigatedBy || !InstigatedBy->GetPawn() )
	UAISense_Damage::ReportDamageEvent(GetWorld(), GetOwner(), InstigatedBy->GetPawn(), Damage,  InstigatedBy->GetPawn()->GetActorLocation(), GetOwner()->GetActorLocation());
}
