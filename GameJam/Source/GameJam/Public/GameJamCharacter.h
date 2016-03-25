// Copyright 1998-2015 Epic Games, Inc. All Rights Reserved.
#pragma once
#include "GameFramework/Character.h"
#include "GameJamCharacter.generated.h"

UENUM(BlueprintType)
enum EPlayerState
{
	E_Attack	UMETA(DisplayName = "Attack"),
	E_Walk		UMETA(DisplayName = "Walk")
};

UCLASS(Blueprintable)
class AGameJamCharacter : public ACharacter
{
	GENERATED_BODY()

	/** Top down camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* TopDownCameraComponent;

	/** Camera boom positioning the camera above the character */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class USpringArmComponent* CameraBoom;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Collision, meta = (AllowPrivateAccess = "true"))
	class USphereComponent *EnemyDetection;



public:
	AGameJamCharacter();

	virtual void Tick(float DeltaSeconds) override;

	void SetTarget(ACharacter *Char);

	UFUNCTION()
	virtual void OnCollisionEnter(AActor *OtherActor, UPrimitiveComponent *OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult &Hit);

	UFUNCTION()
	virtual void OnCollisionEnd(AActor *OtherActor, UPrimitiveComponent *OtherComp, int32 OtherBodyIndex);

private:

	ACharacter *Target;


public:

	/** Returns TopDownCameraComponent subobject **/
	FORCEINLINE class UCameraComponent* GetTopDownCameraComponent() const { return TopDownCameraComponent; }
	/** Returns CameraBoom subobject **/
	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }
	FORCEINLINE class USphereComponent *GetEnemyDetection() const { return EnemyDetection; }
	FORCEINLINE class ACharacter *GetTarget() const { return Target; }
};

