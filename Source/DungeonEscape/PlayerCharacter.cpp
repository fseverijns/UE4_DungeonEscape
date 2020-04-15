// Copyright Frank Severijns 2020
// Based on the tutorial https://docs.unrealengine.com/en-US/Programming/Tutorials/FirstPersonShooter/2/

#include "PlayerCharacter.h"

// Sets default values
APlayerCharacter::APlayerCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void APlayerCharacter::BeginPlay()
{
	Super::BeginPlay();
	
	MaxWalkSpeed = GetCharacterMovement()->MaxWalkSpeed;
}

// Called every frame
void APlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if(bPressedSprint)
	{
		SprintIdleTimer += DeltaTime;

		if(SprintIdleTimer >= SprintIdleTime)
		{
			StopSprint();
		}
	}
}

void APlayerCharacter::SetPlayerMovementAllowed(const bool bAllowed)
{
	bMovementAllowed = bAllowed;
}

// Called to bind functionality to input
void APlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	// Set up movement bindings
	PlayerInputComponent->BindAxis("MoveForward", this, &APlayerCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &APlayerCharacter::MoveRight);

	// Set up look rotation bindings
	PlayerInputComponent->BindAxis("LookVertical", this, &APlayerCharacter::LookVertical);
	PlayerInputComponent->BindAxis("LookHorizontal", this, &APlayerCharacter::LookHorizontal);

	// Set up jump action bindings
	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &APlayerCharacter::StartJump);
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &APlayerCharacter::StopJump);

	// Set up crouch action bindings
	PlayerInputComponent->BindAction("Crouch_Keyboard", IE_Pressed, this, &APlayerCharacter::ToggleCrouch);
	PlayerInputComponent->BindAction("Crouch_Keyboard", IE_Released, this, &APlayerCharacter::StopCrouch);
	PlayerInputComponent->BindAction("Crouch_Gamepad", IE_Pressed, this, &APlayerCharacter::ToggleCrouch);

	// Set up sprint action bindings
	PlayerInputComponent->BindAction("Sprint_Keyboard", IE_Pressed, this, &APlayerCharacter::StartSprint);
	PlayerInputComponent->BindAction("Sprint_Keyboard", IE_Released, this, &APlayerCharacter::StopSprint);
	PlayerInputComponent->BindAction("Sprint_Gamepad", IE_Pressed, this, &APlayerCharacter::StartSprint);
}

void APlayerCharacter::MoveForward(float Axis)
{
	if(!bMovementAllowed)
	{
		return;
	}

	FVector Direction = FRotationMatrix(Controller->GetControlRotation()).GetScaledAxis(EAxis::X);

	if(bPressedSprint && Axis > 0.0f)
	{
		SprintIdleTimer = 0.0f;
	}

	AddMovementInput(Direction, Axis);
}

void APlayerCharacter::MoveRight(float Axis)
{
	if(!bMovementAllowed)
	{
		return;
	}

	FVector Direction = FRotationMatrix(Controller->GetControlRotation()).GetScaledAxis(EAxis::Y);

	AddMovementInput(Direction, Axis);
}

void APlayerCharacter::LookVertical(float Axis)
{
	if(!bMovementAllowed)
	{
		return;
	}

	AddControllerPitchInput(-Axis);
}

void APlayerCharacter::LookHorizontal(float Axis)
{
	if(!bMovementAllowed)
	{
		return;
	}

	AddControllerYawInput(Axis);
}

void APlayerCharacter::StartJump()
{
	if(!bMovementAllowed)
	{
		return;
	}
	
	bPressedJump = true;
}

void APlayerCharacter::StopJump()
{
	bPressedJump = false;
}

void APlayerCharacter::ToggleCrouch()
{
	if(bIsCrouched)
	{
		StopCrouch();
		return;
	}

	if(!bMovementAllowed)
	{
		return;
	}

	Crouch();
}

void APlayerCharacter::StopCrouch()
{
	UnCrouch();
}

void APlayerCharacter::StartSprint()
{
	if(!bMovementAllowed)
	{
		return;
	}
	
	UE_LOG(LogTemp, Warning, TEXT("Start sprint"));
	bPressedSprint = true;
	SprintIdleTimer = 0.0f;
	GetCharacterMovement()->MaxWalkSpeed = MaxSprintSpeed;
}

void APlayerCharacter::StopSprint()
{
	UE_LOG(LogTemp, Warning, TEXT("Stop sprint"));
	bPressedSprint = false;
	GetCharacterMovement()->MaxWalkSpeed = MaxWalkSpeed;
}

float APlayerCharacter::GetWeight()
{
	return WeightInKg;
}
