// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "VehicleAnimInstance.h"
#include "cPlayerHandAnimBP.generated.h"

/**
 * 
 */
UCLASS()
class VRDRONE_API UcPlayerHandAnimBP : public UVehicleAnimInstance
{
	GENERATED_BODY()
    public:
        UcPlayerHandAnimBP(const FObjectInitializer& ObjectInitializer);
        UFUNCTION()
            virtual void SetGripValue(float a_fGrip);
    protected:
        UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Blend")
            float m_fGripVal;
};
