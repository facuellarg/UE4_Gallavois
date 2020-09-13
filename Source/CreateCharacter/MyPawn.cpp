// Fill out your copyright notice in the Description page of Project Settings.


#include "MyPawn.h"

#include "Components/InputComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Engine/EngineBaseTypes.h"
#include "Math/UnrealMathVectorCommon.h"

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
	RotateDirectionVector = FVector::ZeroVector;
	MoveDirection = FVector::ZeroVector;
}

// Called when the game starts or when spawned
void AMyPawn::BeginPlay()
{
	Super::BeginPlay();
}

int AMyPawn::getSing(float value) 
{
	if(value > 0.0) return 1;
	return -1;
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
	Change = false;
	PlayerInputComponent->BindAxis("Forward", this, &AMyPawn::CalculateMoveInputForward);
	PlayerInputComponent->BindAxis("Turns", this, &AMyPawn::CalculateMoveInputTurns);
	PlayerInputComponent->BindAction<FSetFireDelegate>("Fire", EInputEvent::IE_Pressed, this, &AMyPawn::SetFire, true);
	PlayerInputComponent->BindAction<FSetFireDelegate>("Fire", EInputEvent::IE_Released, this, &AMyPawn::SetFire, false);
}

void AMyPawn::CalculateMoveInputForward(float Value)
{
	if (Value != 0){
		Change = true;
	}RotateDirectionVector.Y = -Value;
	float value = Value  * GetWorld()->DeltaTimeSeconds;
	MoveDirection.X = value;
}

void AMyPawn::CalculateMoveInputTurns(float Value)
{
	if (Value!=0){
		Change=true;
	}
	RotateDirectionVector.X  = Value;
	MoveDirection.Y =  Value  * GetWorld()->DeltaTimeSeconds;
}

void AMyPawn::Move()
{	
	
	AddActorLocalOffset(MoveDirection.GetSafeNormal(0)*MoveSpeed);
}

void AMyPawn::Rotate()
{
	if (RotateDirectionVector.X+RotateDirectionVector.Y!=0){

		RotateDirection = FQuat( RotateDirectionVector.ToOrientationRotator());
		// UE_LOG(LogTemp, Warning, TEXT("%s"),*BaseMesh->GetRelativeRotation().ToString());
		// UE_LOG(LogTemp, Warning, TEXT("%s"),*RotateDirectionVector.ToOrientationRotator().ToString());
		BaseMesh->SetRelativeRotation(RotateDirection);
	}
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
