// Fill out your copyright notice in the Description page of Project Settings.


#include "vrdroneplayerpawn.h"


// Sets default values
Avrdroneplayerpawn::Avrdroneplayerpawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//create pawn parts
	CreateComponents();

}

// Called when the game starts or when spawned
void Avrdroneplayerpawn::BeginPlay()
{

	Super::BeginPlay();
	//Avrdroneplayerpawn::CacheHandAnimInstances();
}

// Called every frame
void Avrdroneplayerpawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void Avrdroneplayerpawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	/*
	//Due to  the hand animation implementation causing crashes and time constraints tis code is commented out.
	InputComponent->BindAction("Grip_Left_Hand", IE_Pressed, this, &Avrdroneplayerpawn::GripLeftHand_Pressed);
	InputComponent->BindAction("Grip_Right_Hand", IE_Pressed, this, &Avrdroneplayerpawn::GripRightHand_Pressed);
	InputComponent->BindAction("Grip_Left_Hand", IE_Released, this, &Avrdroneplayerpawn::GripLeftHand_Released);
	InputComponent->BindAction("Grip_Right_Hand", IE_Released, this, &Avrdroneplayerpawn::GripRightHand_Released);
	*/
	
}

void Avrdroneplayerpawn::CreateComponents()
{
	//The default root component for the pawn.
	USceneComponent* rootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("SceneRoot"));
	RootComponent = rootComponent;

	//Component that will be used for the movement based on input
	UFloatingPawnMovement* compFloatingMovement = CreateDefaultSubobject<UFloatingPawnMovement>(TEXT("FloatingMovementComp"));

	//Chaperone component that is required for Steam VR plugin
	USteamVRChaperoneComponent* chaperone = CreateDefaultSubobject<USteamVRChaperoneComponent>(TEXT("SteamVR Chaperone"));

	//Create a scene component that will act as the parent for the camera. This might come in handy later.
	USceneComponent* compVRCameraRoot = CreateDefaultSubobject<USceneComponent>(TEXT("VR Camera Root"));
	compVRCameraRoot->SetupAttachment(rootComponent);
	compVRCameraRoot->SetRelativeLocationAndRotation(FVector::ZeroVector, FQuat::Identity);
	compVRCameraRoot->SetRelativeScale3D(FVector::OneVector);

	//Create a camera component and attach this to the camera root.
	UCameraComponent* compVRCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("HMD Camera"));
	compVRCamera->SetupAttachment(compVRCameraRoot);
	compVRCamera->SetRelativeLocationAndRotation(FVector::ZeroVector, FQuat::Identity);
	compVRCamera->SetRelativeScale3D(FVector::OneVector);

	//to create the hands
	CreateHandController(compVRCameraRoot, "MC_Left", FXRMotionControllerBase::LeftHandSourceId);
	CreateHandController(compVRCameraRoot, "MC_Right", FXRMotionControllerBase::RightHandSourceId);

}

//for the hand
void  Avrdroneplayerpawn::CreateHandController(USceneComponent* a_compParent, FName a_strDisplayName, FName a_nameHandType)
{
	UMotionControllerComponent* compMotionController = CreateDefaultSubobject<UMotionControllerComponent>(a_strDisplayName);
	compMotionController->SetRelativeLocationAndRotation(FVector::ZeroVector, FQuat::Identity);
	compMotionController->SetRelativeScale3D(FVector::OneVector);

	compMotionController->MotionSource = a_nameHandType;
	compMotionController->SetupAttachment(a_compParent);

	//Create the hand mesh for visualization
	FName strMeshDisplayName = a_nameHandType == FXRMotionControllerBase::LeftHandSourceId ? FName(TEXT("Hand_Left")) : FName(TEXT("Hand_Right"));
	USkeletalMeshComponent* refHandMesh = CreateHandMesh(compMotionController, strMeshDisplayName, a_nameHandType);
	if (a_nameHandType == FXRMotionControllerBase::LeftHandSourceId)
		m_meshLeftHand = refHandMesh;
	else
		m_meshRightHand = refHandMesh;
}

USkeletalMeshComponent* Avrdroneplayerpawn::CreateHandMesh(UMotionControllerComponent* a_compParent, FName a_strDisplayName, FName a_nameHandType)
{
	USkeletalMeshComponent* refComponentHand = NULL;

	//Find the default cube that ships with the engine content
	static ConstructorHelpers::FObjectFinder<USkeletalMesh>HandMeshObject(TEXT("SkeletalMesh'/Game/VirtualReality/Mannequin/Character/Mesh/MannequinHand_Right.MannequinHand_Right'"));
	if (!HandMeshObject.Object)
	{
		UE_LOG(LogTemp, Error, TEXT("Could not load the default cube for hand mesh"));
		return NULL;
	}

	//create the mesh component
	refComponentHand = CreateDefaultSubobject<USkeletalMeshComponent>(a_strDisplayName);
	//set the mesh to the component
	refComponentHand->SetSkeletalMesh(HandMeshObject.Object);

	//Set the defaults
	refComponentHand->SetAutoActivate(true);
	refComponentHand->SetVisibility(true);
	refComponentHand->SetHiddenInGame(false);
	FQuat qRotation = FQuat::Identity;
	FVector vec3Scale = FVector::OneVector;
	if (a_nameHandType == FXRMotionControllerBase::LeftHandSourceId)
	{
		qRotation = FQuat(FVector(1, 0, 0), FMath::DegreesToRadians(90));
		vec3Scale = FVector(1, -1, 1);
		//a_refHand->SetVisibility(false);
		//a_refHand->SetHiddenInGame(true);
	}
	else
	{
		qRotation = FQuat(FVector(1, 0, 0), FMath::DegreesToRadians(270));
	}
	refComponentHand->SetRelativeLocationAndRotation(FVector::ZeroVector, qRotation);
	refComponentHand->SetRelativeScale3D(vec3Scale);
	refComponentHand->SetupAttachment(a_compParent);
	return refComponentHand;
}
/*  
* Due to the animation leading to crashes and time constraint the code is commented out.
void Avrdroneplayerpawn::SetHandAnimationBlueprint(USkeletalMeshComponent* a_refHand)
{
	static ConstructorHelpers::FObjectFinder<UClass>HandAnimBP(TEXT("AnimBlueprintGeneratedClass'/Game/RightHand_AnimBP'"));
	if (HandAnimBP.Succeeded())
	{
		a_refHand->AnimClass = HandAnimBP.Object;
		a_refHand->SetAnimationMode(EAnimationMode::AnimationBlueprint);
		a_refHand->SetAnimInstanceClass(HandAnimBP.Object);
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("Could not load the hand anim BP"));
	}
}
//Functions for hand grip implementation
void Avrdroneplayerpawn::GripLeftHand_Pressed_Implementation()
{
	UE_LOG(LogTemp, Log, TEXT("Left Hand Grip Pressed"));
	m_refLeftHandAnimBP->SetGripValue(1.0f);
}

void Avrdroneplayerpawn::GripRightHand_Pressed_Implementation()
{
	UE_LOG(LogTemp, Log, TEXT("Right Hand Grip Pressed"));
	m_refRightHandAnimBP->SetGripValue(1.0f);
}

void Avrdroneplayerpawn::GripLeftHand_Released_Implementation()
{
	UE_LOG(LogTemp, Log, TEXT("Left Hand Grip Released"));
	m_refLeftHandAnimBP->SetGripValue(0.0f);
}

void Avrdroneplayerpawn::GripRightHand_Released_Implementation()
{
	UE_LOG(LogTemp, Log, TEXT("Left Hand Grip Released"));
	m_refRightHandAnimBP->SetGripValue(0.0f);
}

void Avrdroneplayerpawn::CacheHandAnimInstances()
{
	m_refLeftHandAnimBP = Cast<UcPlayerHandAnimBP>(m_meshLeftHand->GetAnimInstance());
	if (!IsValid(m_refLeftHandAnimBP))
		UE_LOG(LogTemp, Error, TEXT("Could not cast Hand Anim to the right class"));
	m_refRightHandAnimBP = Cast<UcPlayerHandAnimBP>(m_meshRightHand->GetAnimInstance());
	if (!IsValid(m_refRightHandAnimBP))
		UE_LOG(LogTemp, Error, TEXT("Could not cast Hand Anim to the right class"));
}
*/

