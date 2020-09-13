// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "MyPawn.generated.h"

class UCapsuleComponent;
class USpringArmComponent;
class USkeletalMeshComponent;
class UCameraComponent;

UCLASS()
class CREATECHARACTER_API AMyPawn : public APawn
{
	GENERATED_BODY()

private:
	UPROPERTY(VisibleAnyWhere, BlueprintReadWrite, Category = "Components", meta = (AllowPrivateAccess = "true"))
	UCapsuleComponent *CapsuleComp;
	UPROPERTY(VisibleAnyWhere, BlueprintReadWrite, Category = "Components", meta = (AllowPrivateAccess = "true"))
	USkeletalMeshComponent *BaseMesh;
	UPROPERTY(VisibleAnyWhere, BlueprintReadOnly, category = "Components", meta = (AllowPrivateAccess = "true"))
	USpringArmComponent *SpringArm;
	UPROPERTY(VisibleAnyWhere, BlueprintReadOnly, category = "Components", meta = (AllowPrivateAccess = "true"))
	UCameraComponent *Camera;

	// UPROPERTY(VisibleAnyWhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	// USkeletalMeshComponent *GunMesh;
	// UPROPERTY(VisibleAnyWhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	// USceneComponent *ProjectileSpawnPoint;
	UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = "Movement", meta = (AllowPrivateAccess = "true"))
	float MoveSpeed = 100.0f;
	UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = "Movement", meta = (AllowPrivateAccess = "true"))
	float RotateSpeed = 100.0f;
	FVector MoveDirection;
	FVector RotateDirectionVector;
	UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = "Movement", meta = (AllowPrivateAccess = "true"))
	bool Change;

	bool Fyring;

	FQuat RotateDirection;

	void Move();
	void Rotate();

	void Fire();
	void SetFire(bool stateFire);
	DECLARE_DELEGATE_OneParam(FSetFireDelegate,bool);
	void CheckFire();
	void CalculateMoveInputForward(float Value);
	void CalculateMoveInputTurns(float Value);

	void CalculateRotateInput(float Value);

public:
	// Sets default values for this pawn's properties
	AMyPawn();
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent *PlayerInputComponent) override;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	int getSing(float value);
};
