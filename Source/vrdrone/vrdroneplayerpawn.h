// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/ConstructorHelpers.h"
#include "Math/Quat.h"
#include "GameFramework/Pawn.h"
#include "HeadMountedDisplay.h"
#include "SteamVRChaperoneComponent.h"
#include "MotionControllerComponent.h"
#include "XRMotionControllerBase.h"
#include "GameFramework/FloatingPawnMovement.h"
#include "Camera/CameraComponent.h"
#include <vrdrone/cPlayerHandAnimBP.h>
#include "vrdroneplayerpawn.generated.h"


UCLASS()
class VRDRONE_API Avrdroneplayerpawn : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	Avrdroneplayerpawn();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	//called to make hand
	void CreateHandController(USceneComponent* a_compParent, FName a_strDisplayName, FName a_nameHandType);
	
	//For the hand
	USkeletalMeshComponent* m_meshLeftHand;
	USkeletalMeshComponent* m_meshRightHand;

	UcPlayerHandAnimBP* m_refLeftHandAnimBP;
	UcPlayerHandAnimBP* m_refRightHandAnimBP;

	void CacheHandAnimInstances();

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	//called to creat pawn parts
	virtual void CreateComponents();

	USkeletalMeshComponent* CreateHandMesh(UMotionControllerComponent* a_compParent, FName a_strDisplayName, FName a_nameHandType);
	/*
	void SetHandAnimationBlueprint(USkeletalMeshComponent* a_refHand);
	
	//function events for the motion controller
	UFUNCTION(BlueprintNativeEvent, Category = "Input")
		void GripLeftHand_Pressed();
	UFUNCTION(BlueprintNativeEvent, Category = "Input")
		void GripRightHand_Pressed();
	UFUNCTION(BlueprintNativeEvent, Category = "Input")
		void GripLeftHand_Released();
	UFUNCTION(BlueprintNativeEvent, Category = "Input")
		void GripRightHand_Released();
    */
};
