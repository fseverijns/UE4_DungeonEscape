// Copyright Frank Severijns 2020
// Based on the tutorial https://docs.unrealengine.com/en-US/Programming/Tutorials/FirstPersonShooter/2/

#include "FPSCharacter.h"

// Sets default values
AFPSCharacter::AFPSCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AFPSCharacter::BeginPlay()
{
	Super::BeginPlay();
	
	MaxWalkSpeed = GetCharacterMovement()->MaxWalkSpeed;
}

// Called every frame
void AFPSCharacter::Tick(float DeltaTime)
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

// Called to bind functionality to input
void AFPSCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	// Set up movement bindings
	PlayerInputComponent->BindAxis("MoveForward", this, &AFPSCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &AFPSCharacter::MoveRight);

	// Set up look rotation bindings
	PlayerInputComponent->BindAxis("LookVertical", this, &AFPSCharacter::LookVertical);
	PlayerInputComponent->BindAxis("LookHorizontal", this, &AFPSCharacter::LookHorizontal);

	// Set up jump action bindings
	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &AFPSCharacter::StartJump);
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &AFPSCharacter::StopJump);

	// Set up crouch action bindings
	PlayerInputComponent->BindAction("Crouch_Keyboard", IE_Pressed, this, &AFPSCharacter::ToggleCrouch);
	PlayerInputComponent->BindAction("Crouch_Keyboard", IE_Released, this, &AFPSCharacter::StopCrouch);
	PlayerInputComponent->BindAction("Crouch_Gamepad", IE_Pressed, this, &AFPSCharacter::ToggleCrouch);

	// Set up sprint action bindings
	PlayerInputComponent->BindAction("Sprint_Keyboard", IE_Pressed, this, &AFPSCharacter::StartSprint);
	PlayerInputComponent->BindAction("Sprint_Keyboard", IE_Released, this, &AFPSCharacter::StopSprint);
	PlayerInputComponent->BindAction("Sprint_Gamepad", IE_Pressed, this, &AFPSCharacter::StartSprint);
}

void AFPSCharacter::MoveForward(float Axis)
{
	FVector Direction = FRotationMatrix(Controller->GetControlRotation()).GetScaledAxis(EAxis::X);

	if(bPressedSprint && Axis > 0.0f)
	{
		SprintIdleTimer = 0.0f;
	}

	AddMovementInput(Direction, Axis);
}

void AFPSCharacter::MoveRight(float Axis)
{
	FVector Direction = FRotationMatrix(Controller->GetControlRotation()).GetScaledAxis(EAxis::Y);

	AddMovementInput(Direction, Axis);
}

void AFPSCharacter::LookVertical(float Axis)
{
	AddControllerPitchInput(-Axis);
}

void AFPSCharacter::LookHorizontal(float Axis)
{
	AddControllerYawInput(Axis);
}

void AFPSCharacter::StartJump()
{
	bPressedJump = true;
}

void AFPSCharacter::StopJump()
{
	bPressedJump = false;
}

void AFPSCharacter::ToggleCrouch()
{
	if(bIsCrouched)
	{
		StopCrouch();
		return;
	}

	Crouch();
}

void AFPSCharacter::StopCrouch()
{
	UnCrouch();
}

void AFPSCharacter::StartSprint()
{
	UE_LOG(LogTemp, Warning, TEXT("Start sprint"));
	bPressedSprint = true;
	SprintIdleTimer = 0.0f;
	GetCharacterMovement()->MaxWalkSpeed = MaxSprintSpeed;
}

void AFPSCharacter::StopSprint()
{
	UE_LOG(LogTemp, Warning, TEXT("Stop sprint"));
	bPressedSprint = false;
	GetCharacterMovement()->MaxWalkSpeed = MaxWalkSpeed;
}
