#include "Player/RTSPlayerCharacter.h"

#include "RTSGameModeBase.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "Blueprint/UserWidget.h"

// Sets default values
ARTSPlayerCharacter::ARTSPlayerCharacter()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	


	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->SetUsingAbsoluteRotation(true); // Don't want arm to rotate when character does
	CameraBoom->TargetArmLength = 800.f;
	CameraBoom->SetRelativeRotation(FRotator(0.f, -60.f, 0.f));
	CameraBoom->bDoCollisionTest = false; // Don't want to pull camera in when it collides with level


	CameraComponent = CreateDefaultSubobject<UCameraComponent>("CameraComponent");
	CameraComponent->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
	CameraComponent->bUsePawnControlRotation = false;

	

	
}


void ARTSPlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	PlayerInputComponent->BindAxis("MoveForward", this, &ARTSPlayerCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &ARTSPlayerCharacter::MoveRight);

	PlayerInputComponent->BindAction("MouseScrollUp",IE_Pressed, this, &ARTSPlayerCharacter::MouseScrollUp);
	PlayerInputComponent->BindAction("MouseScrollDown", IE_Pressed ,this, &ARTSPlayerCharacter::MouseScrollDown);
	

}

// Called when the game starts or when spawned
void ARTSPlayerCharacter::BeginPlay()
{
	Super::BeginPlay();
	PC = Cast<ABasePlayerController>(GetController());

	const auto GameMode = Cast<ARTSGameModeBase>(GetWorld()->GetAuthGameMode());
	if(GameMode)
		TeamComponent = GameMode->OrganismTeamComponent;
	if(TeamComponent == nullptr) UE_LOG(LogTemp, Warning, TEXT("Player TeamComponent is NULL!"))

	
}

// Called every frame
void ARTSPlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if(PC) 	MoveCamera(PC->GetPanDirection());
}


void ARTSPlayerCharacter::MoveForward(float Amount)
{
	AddMovementInput(GetActorForwardVector(), Amount);
	
	
}


void ARTSPlayerCharacter::MoveRight(float Amount)
{
	AddMovementInput(GetActorRightVector(), Amount);
}

void ARTSPlayerCharacter::MouseScrollUp()
{
	
	CameraBoom->TargetArmLength = FMath::Clamp(CameraBoom->TargetArmLength - SpringArmLengthDelta, SpringArmMinLenght, SpringArmMaxLenght); 

}

void ARTSPlayerCharacter::MouseScrollDown()
{
	CameraBoom->TargetArmLength = FMath::Clamp(CameraBoom->TargetArmLength + SpringArmLengthDelta, SpringArmMinLenght, SpringArmMaxLenght); 

}

void ARTSPlayerCharacter::MoveCamera(FVector PanDirection)
{
	
	if(PanDirection == FVector::ZeroVector) return;
	AddActorWorldOffset(PanDirection * CameraSpeed * (CameraBoom->TargetArmLength / SpringArmMaxLenght));
}
