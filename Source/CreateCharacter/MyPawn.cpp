// Fill out your copyright notice in the Description page of Project Settings.

#include "MyPawn.h"

#include "Components/InputComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Engine/EngineBaseTypes.h"

// Sets default values
AMyPawn::AMyPawn()
{
	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	CapsuleComp = CreateDefaultSubobject<UCapsuleComponent>(TEXT("Capsule Colaider"));
	BaseMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Base Mesh"));
	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("Spring Arm"));
	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));

	// DECLARE_DELEGATE_RetVal_OneParam(FFooDelegate, bool);
	RootComponent = CapsuleComp;
	BaseMesh->SetupAttachment(CapsuleComp);
	SpringArm->SetupAttachment(RootComponent);
	Camera->SetupAttachment(SpringArm);
}

// Called when the game starts or when spawned
void AMyPawn::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void AMyPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	Move();
	Rotate();
	CheckFire();
}

// Called to bind functionality to input
void AMyPawn::SetupPlayerInputComponent(UInputComponent *PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	PlayerInputComponent->BindAxis("Forward", this, &AMyPawn::CalculateMoveInputForward);
	PlayerInputComponent->BindAxis("Turns", this, &AMyPawn::CalculateMoveInputTurns);
	PlayerInputComponent->BindAxis("Rotate", this, &AMyPawn::CalculateRotateInput);
	PlayerInputComponent->BindAction<FSetFireDelegate>("Fire", EInputEvent::IE_Pressed, this, &AMyPawn::SetFire, true);
	PlayerInputComponent->BindAction<FSetFireDelegate>("Fire", EInputEvent::IE_Released, this, &AMyPawn::SetFire, false);
}

void AMyPawn::CalculateMoveInputForward(float Value)
{
	MoveDirectionForward = FVector(Value * MoveSpeed * GetWorld()->DeltaTimeSeconds, 0, 0);
}

void AMyPawn::CalculateMoveInputTurns(float Value)
{
	MoveDirectionTurns = FVector(0, Value * MoveSpeed * GetWorld()->DeltaTimeSeconds, 0);
}

void AMyPawn::CalculateRotateInput(float Value)
{
	FRotator Rotation = FRotator(0, Value * MoveSpeed * GetWorld()->DeltaTimeSeconds, 0);
	RotateDirection = FQuat(Rotation);
}

void AMyPawn::Move()
{	
	
	AddActorLocalOffset(MoveDirectionForward+MoveDirectionTurns);
}

void AMyPawn::Rotate()
{
	SpringArm->AddLocalRotation(RotateDirection);
	// SpringArm->AddActorLocalRotation(RotateDirection);
}

void AMyPawn::Fire()
{
	UE_LOG(LogTemp, Warning, TEXT("Disparando"));
}

void AMyPawn::SetFire(bool stateFire)
{
	Fyring = stateFire;
}

void AMyPawn::CheckFire()
{
	if (Fyring)
	{
		Fire();
	}
}
