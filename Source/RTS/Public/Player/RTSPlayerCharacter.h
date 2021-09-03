// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "BasePlayerController.h"
#include "RTSPlayerCharacter.generated.h"
class UCameraComponent;

UCLASS()
class RTS_API ARTSPlayerCharacter : public ACharacter
{
	GENERATED_BODY()


public:
	URTSTeamComponent* GetTeam()const {return TeamComponent;}
	ARTSPlayerCharacter();
	virtual void Tick(float DeltaTime) override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

protected:

	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
	UCameraComponent* CameraComponent;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Components")
	URTSTeamComponent* TeamComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class USpringArmComponent* CameraBoom;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Camera", meta = (ClampMin = "501", ClampMax = "2000"))
	float SpringArmMaxLenght = 501;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Camera", meta = (ClampMin = "100", ClampMax = "500"))
	float SpringArmMinLenght = 200;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Camera", meta = (ClampMin = "10", ClampMax = "200"))
	float SpringArmLengthDelta = 50.0f;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Camera")
	float CameraSpeed = 3.0f;	

	UPROPERTY()
	ABasePlayerController* PC; 
	

private:	

	UFUNCTION()
	void MoveForward(float Amount);
	
	UFUNCTION()
	void MoveRight(float Amount);

	UFUNCTION()
	void MouseScrollUp();

	UFUNCTION()
    void MouseScrollDown();

	UFUNCTION()
	void MoveCamera(FVector PanDirection);
	
};
