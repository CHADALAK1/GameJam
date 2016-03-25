// Copyright 1998-2015 Epic Games, Inc. All Rights Reserved.

#include "GameJam.h"
#include "GameJamCharacter.h"

AGameJamCharacter::AGameJamCharacter()
{
	// Set size for player capsule
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);

	// Don't rotate character to camera direction
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	// Configure character movement
	GetCharacterMovement()->bOrientRotationToMovement = true; // Rotate character to moving direction
	GetCharacterMovement()->RotationRate = FRotator(0.f, 640.f, 0.f);
	GetCharacterMovement()->bConstrainToPlane = true;
	GetCharacterMovement()->bSnapToPlaneAtStart = true;

	// Create a camera boom...
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->AttachTo(RootComponent);
	CameraBoom->bAbsoluteRotation = true; // Don't want arm to rotate when character does
	CameraBoom->TargetArmLength = 1400.f;
	CameraBoom->RelativeRotation = FRotator(-60.f, 0.f, 0.f);
	CameraBoom->bDoCollisionTest = false; // Don't want to pull camera in when it collides with level

	// Create a camera...
	TopDownCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("TopDownCamera"));
	TopDownCameraComponent->AttachTo(CameraBoom, USpringArmComponent::SocketName);
	TopDownCameraComponent->bUsePawnControlRotation = false; // Camera does not rotate relative to arm

	EnemyDetection = CreateDefaultSubobject<USphereComponent>(TEXT("EnemyDetection"));
	EnemyDetection->AttachTo(RootComponent);
	EnemyDetection->OnComponentBeginOverlap.AddDynamic(this, &AGameJamCharacter::OnCollisionEnter);
	EnemyDetection->OnComponentEndOverlap.AddDynamic(this, &AGameJamCharacter::OnCollisionEnd);

}

void AGameJamCharacter::Tick(float DeltaSeconds)
{

}

void AGameJamCharacter::SetTarget(ACharacter * Char)
{
	if (Char)
	{
		Target = Char;
	}
}

void AGameJamCharacter::OnCollisionEnter(AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & Hit)
{
	ACharacter *Char = Cast<ACharacter>(OtherActor);

	if (Char == GetTarget())
	{
		GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Blue, "CorrectTarget");
		if (Char && Char != this)
		{
			GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Blue, "ENEMY IN COLLISION");
		}
	}
}

void AGameJamCharacter::OnCollisionEnd(AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex)
{
	ACharacter *Char = Cast<ACharacter>(OtherActor);

	if (Char && Char != this)
	{
		GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Blue, "ENEMY EXIT COLLISION");
	}
}
