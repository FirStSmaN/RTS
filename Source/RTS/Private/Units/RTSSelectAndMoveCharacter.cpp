

#include "RTSSelectAndMoveCharacter.h"
#include "UObject/ConstructorHelpers.h"
#include "Camera/CameraComponent.h"
#include "Components/DecalComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/PlayerController.h"
#include "Components/RTSAIHealthComponent.h"
#include "HeadMountedDisplayFunctionLibrary.h"
#include "RTSGameModeBase.h"
#include "Units/Components/AIWeaponComponentComponent.h"
#include "Units/Components/RTSTeamComponent.h"
#include "Units/Components/RTSAIController.h"

#include "Blueprint/AIBlueprintHelperLibrary.h"
#include "Materials/Material.h"
#include "PaperSpriteComponent.h"
#include "BrainComponent.h"
#include "Components/WidgetComponent.h"
#include "DrawDebugHelpers.h"
#include "Engine/World.h"
#include "Kismet/GameplayStatics.h"
#include "UI/HealthBarWidget.h"

DEFINE_LOG_CATEGORY_STATIC(LogSelectAndMoveCharacter, All, All);

ARTSSelectAndMoveCharacter::ARTSSelectAndMoveCharacter()
{
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);



	// Configure character movement
	GetCharacterMovement()->bOrientRotationToMovement = true; // Rotate character to moving direction
	GetCharacterMovement()->RotationRate = FRotator(0.f, 640.f, 0.f);
	GetCharacterMovement()->bConstrainToPlane = true;
	GetCharacterMovement()->bSnapToPlaneAtStart = true;


	
	HealthBarWidgetComponent = CreateDefaultSubobject<UWidgetComponent>("HealthBarWidget");
	HealthBarWidgetComponent->SetupAttachment(GetRootComponent());
	HealthBarWidgetComponent->SetWidgetSpace(EWidgetSpace::Screen);
	
	HealthComponent = CreateDefaultSubobject<URTSAIHealthComponent>("HealthComponent");
	TeamComponent = CreateDefaultSubobject<URTSTeamComponent>("TeamComponent");
	WeaponComponent = CreateDefaultSubobject<UAIWeaponComponentComponent>("WeaponComponent");
	

	// Create a decal in the world to show the cursor's location
	CursorToWorld = CreateDefaultSubobject<UDecalComponent>("CursorToWorld");
	CursorToWorld->SetupAttachment(RootComponent);
	static ConstructorHelpers::FObjectFinder<UMaterial> DecalMaterialAsset(TEXT("Material'/Game/TopDownCPP/Blueprints/M_Cursor_Decal.M_Cursor_Decal'"));
	if (DecalMaterialAsset.Succeeded())
	{
		CursorToWorld->SetDecalMaterial(DecalMaterialAsset.Object);
	}
	CursorToWorld->DecalSize = FVector(16.0f, 32.0f, 32.0f);
	CursorToWorld->SetRelativeRotation(FRotator(90.0f, 0.0f, 0.0f).Quaternion());
	CursorToWorld->SetVisibility(false);

	MinimapSpriteComponent = CreateDefaultSubobject<UPaperSpriteComponent>("MinimapSpriteComponent");
	MinimapSpriteComponent->SetupAttachment(RootComponent);

	
	
	// Activate ticking in order to update the cursor every frame.
	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.bStartWithTickEnabled = true;

	AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;
	AIControllerClass = ARTSAIController::StaticClass();

	if(GetCharacterMovement())
	{
		GetCharacterMovement()->bUseControllerDesiredRotation = true;
		GetCharacterMovement()->RotationRate = FRotator(0.0, 200.0f, 0.0f);
	}


}

void ARTSSelectAndMoveCharacter::BeginPlay()
{
	
	Super::BeginPlay();
	
	check(HealthComponent);
	check(HealthBarWidgetComponent);
	check(WeaponComponent);
	check(CursorToWorld);
	HealthComponent->OnDeath.AddUObject(this, &ARTSSelectAndMoveCharacter::OnDeath);
	HealthComponent->OnHealthChanged.AddUObject(this, &ARTSSelectAndMoveCharacter::OnHealthChanged);

	
	
}


void ARTSSelectAndMoveCharacter::Tick(float DeltaSeconds)
{
    Super::Tick(DeltaSeconds);

	if (CursorToWorld != nullptr)
	{
		if (UHeadMountedDisplayFunctionLibrary::IsHeadMountedDisplayEnabled())
		{
			if (UWorld* World = GetWorld())
			{
				FHitResult HitResult;
				FCollisionQueryParams Params(NAME_None, FCollisionQueryParams::GetUnknownStatId());
				FVector StartLocation = GetActorLocation();// TopDownCameraComponent->GetComponentLocation();
				FVector EndLocation = GetActorRotation().Vector() * 2000.f; // TopDownCameraComponent->GetComponentRotation().Vector() * 2000.0f;
				Params.AddIgnoredActor(this);
				World->LineTraceSingleByChannel(HitResult, StartLocation, EndLocation, ECC_Visibility, Params);
				FQuat SurfaceRotation = HitResult.ImpactNormal.ToOrientationRotator().Quaternion();
				CursorToWorld->SetWorldLocationAndRotation(HitResult.Location, SurfaceRotation);
			}
		}
		else if (APlayerController* PC = Cast<APlayerController>(GetController()))
		{
			FHitResult TraceHitResult;
			PC->GetHitResultUnderCursor(ECC_Visibility, true, TraceHitResult);
			FVector CursorFV = TraceHitResult.ImpactNormal;
			FRotator CursorR = CursorFV.Rotation();
			CursorToWorld->SetWorldLocation(TraceHitResult.Location);
			CursorToWorld->SetWorldRotation(CursorR);
		}
	}
}

void ARTSSelectAndMoveCharacter::SetSelection(bool Value)
{
	CursorToWorld->SetVisibility(Value);
}

 void ARTSSelectAndMoveCharacter::Select()
{
	CursorToWorld->SetVisibility(true);
}

 void ARTSSelectAndMoveCharacter::DisSelect()
{
	CursorToWorld->SetVisibility(false);
}

void ARTSSelectAndMoveCharacter::OnDeath()
{
	GetCharacterMovement()->DisableMovement();
	SetLifeSpan(5.0f);
	GetCapsuleComponent()->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);
	GetMesh()->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	GetMesh()->SetSimulatePhysics(true);
	
	CursorToWorld->DecalSize = FVector::ZeroVector;
	MinimapSpriteComponent->SetVisibility(false);
	
	Controller = nullptr;
	if(Controller)
	UE_LOG(LogTemp, Display, TEXT("Controller : %s"), *GetController()->GetName() );
	DisSelect();
	

	const auto RTSAIController = Cast<AAIController>(Controller);

	if(RTSAIController && RTSAIController->BrainComponent)
	{
		RTSAIController->BrainComponent->Cleanup();
	}

	UGameplayStatics::SpawnDecalAtLocation(GetWorld(), DecalOnDeathMaterial, FVector(5, 200, 200), GetActorLocation() - GetCapsuleComponent()->GetScaledCapsuleHalfHeight(),FRotator(-90, 0, 0), 5);   // декаль крови при смерти TODO ПОФИКСИТЬ КОСТЫЛЬ С РАЗМЕЩЕНИЕМ ДЕКАЛИ
	
	
	FVector StartTrace = GetActorLocation();  // TODO попытка сделать проверку на необходимость смены команды клетки при смерти
	FVector EndTrace = GetActorLocation() - FVector(0, 0, 400);
	FHitResult HitResult;
	
	if (!GetWorld())return;
	FCollisionQueryParams CollisionParams;
	CollisionParams.AddIgnoredActor(GetOwner());
	CollisionParams.bReturnPhysicalMaterial = false;

	GetWorld()->LineTraceSingleByChannel(HitResult, StartTrace, EndTrace, ECollisionChannel::ECC_WorldStatic, CollisionParams);
	//DrawDebugLine(GetWorld(), StartTrace, EndTrace, FColor::Green, false, 4, 0, 5);
	auto Title = Cast<ABaseTitle>(HitResult.Actor);
	
	if(!Title)
	{
		
		return;
	}
	

	TArray<AActor*> OverlappingActors;
	Title->GetOverlappingActors(OverlappingActors, this->StaticClass());
	

	int32 SameTeamUnits = 0;
	int32 OppositeTeamUnits = 0;
	for(auto OverlappedActor: OverlappingActors)
	{
		const auto OverLappedCharacter = Cast<ARTSSelectAndMoveCharacter>(OverlappedActor);
		if(!OverLappedCharacter) continue;

		if(Title->GetTeam() == OverLappedCharacter->GetTeam())
		{
			SameTeamUnits++;
		}
		if(Title->IsOppositeTeam(OverLappedCharacter->GetTeam()))
		{
			OppositeTeamUnits++;
		}


		
	}

	if(!GetWorld() || !GetWorld()->GetAuthGameMode()) return;
	const auto RTSGameModeBase = Cast<ARTSGameModeBase>(GetWorld()->GetAuthGameMode());
	if(SameTeamUnits == 0 && OppositeTeamUnits != 0)
	{
		
		Title->ChangeTeam(RTSGameModeBase->GetOppositeTeam(Title->GetTeam()));
	}
	
	
}
void ARTSSelectAndMoveCharacter::OnHealthChanged(float Health, float HealthDelta)
{
	
	const auto HealthBarWidget = Cast<UHealthBarWidget>(HealthBarWidgetComponent->GetUserWidgetObject());
	if(!HealthBarWidget) return;

	HealthBarWidget->SetHealthPercent(HealthComponent->GetHealthPercent());
}

void ARTSSelectAndMoveCharacter::SetTeam(URTSTeamComponent* ValueTeamComponent)
{
	TeamComponent = ValueTeamComponent;
}

URTSTeamComponent* ARTSSelectAndMoveCharacter::GetTeam()
{
	return TeamComponent;
}

