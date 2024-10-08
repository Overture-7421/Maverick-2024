// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "ClosedCommand.h"

// NOTE:  Consider using this command inline, rather than writing a subclass.
// For more information, see:
// https://docs.wpilib.org/en/stable/docs/software/commandbased/convenience-features.html
frc2::CommandPtr ClosedCommand(SuperStructure* superStructure, Intake* intake, Storage* storage, Shooter* shooter) {

	return frc2::cmd::Parallel(
		storage->storageCommand(StorageConstants::StopVolts),
		intake->intakeCommand(IntakeConstants::StopVolts),
		shooter->shooterCommand(ShooterConstants::IdleSpeed),
		superStructure->superStructureCommand(SuperStructureConstants::ClosedState)
	);
}
