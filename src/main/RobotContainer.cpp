// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "RobotContainer.h"

#include <frc2/command/Commands.h>
#include <iostream>

RobotContainer::RobotContainer() {
	pathplanner::NamedCommands::registerCommand("GroundGrabCommand", GroundGrabCommand(&superStructure, &storage, &intake));
	pathplanner::NamedCommands::registerCommand("ClosedCommand", std::move(ClosedCommand(&superStructure, &intake, &storage, &shooter).ToPtr()));
	pathplanner::NamedCommands::registerCommand("VisionSpeakerCommand", std::move(VisionSpeakerCommand(&chassis, &superStructure, &shooter, &storage)).ToPtr());
	pathplanner::NamedCommands::registerCommand("VisionAmpCommand", std::move(VisionAmpCommand(&superStructure, &shooter, &storage)));
	pathplanner::NamedCommands::registerCommand("StorageCommand", std::move(StorageCommand(&storage, 3_V).ToPtr()));
	pathplanner::NamedCommands::registerCommand("ShooterCommand", std::move(ShooterCommand(&shooter, 4.00).ToPtr()));
	pathplanner::NamedCommands::registerCommand("VisionNoShoot", std::move(VisionSpeakerCommandNoShoot(&chassis, &superStructure, &shooter).ToPtr()));

	center6NoteAuto = pathplanner::AutoBuilder::buildAuto("CenterAuto-6Notes");
	center4NoteAuto = pathplanner::AutoBuilder::buildAuto("CenterAuto-4Notes");
	ampAuto = pathplanner::AutoBuilder::buildAuto("AMPAuto");
	sourceAuto = pathplanner::AutoBuilder::buildAuto("SourceAuto");

	autoChooser.SetDefaultOption("None, null, nada", defaultNoneAuto.get());
	autoChooser.AddOption("CenterAuto-6Notes", center6NoteAuto.get());
	autoChooser.AddOption("CenterAuto-4Notes", center4NoteAuto.get());
	autoChooser.AddOption("AMPAuto", ampAuto.get());
	autoChooser.AddOption("SourceAuto", sourceAuto.get());

	frc::SmartDashboard::PutData("Auto Chooser", &autoChooser);

	ConfigureBindings();
	// ConfigureSysIdBindings(&chassis, &characterization);
}

void RobotContainer::ConfigureBindings() {
	chassis.SetDefaultCommand(Drive(&chassis, &driver));
	// shooter.SetDefaultCommand(ShooterDefaultCommand(&chassis, &shooter));

	// tabulate.ToggleOnTrue(TabulateCommand(&chassis, &superStructure, &shooter).ToPtr());

	zeroHeading.OnTrue(ResetAngle(&chassis).ToPtr());

	ampV.WhileTrue(VisionAmpCommand(&superStructure, &shooter, &storage));
	ampV.OnFalse(ClosedCommand(&superStructure, &intake, &storage).ToPtr());

	speakerV.WhileTrue(VisionSpeakerCommand(&chassis, &superStructure, &shooter, &opertr).ToPtr());
	speakerV.OnFalse(ClosedCommand(&superStructure, &intake, &storage).ToPtr());

	// Operator 
	ampM.WhileTrue(AmpCommand(&superStructure, &shooter).ToPtr());
	ampM.OnFalse(ClosedCommand(&superStructure, &intake, &storage).ToPtr());

	climbM.WhileTrue(ManualClimb(&chassis, &superStructure, &supportArms, &aprilTagCamera, &opertr));
	climbM.OnFalse(
		frc2::cmd::Parallel(
			frc2::cmd::RunOnce([&] {
		aprilTagCamera.setPoseEstimator(true);
		supportArms.setTargetCoord({ 0 });
	}),
			ClosedCommand(&superStructure, &intake, &storage).ToPtr()
		)
	);

	shootM.WhileTrue(StorageCommand(&storage, StorageConstants::SpeakerScoreVolts).ToPtr());

	shootM.OnFalse(StorageCommand(&storage, 0_V).ToPtr());

	speakerM.WhileTrue(SpeakerCommand(&superStructure, &shooter).ToPtr());
	speakerM.OnFalse(ClosedCommand(&superStructure, &intake, &storage).ToPtr());

	closed.WhileTrue(ClosedCommand(&superStructure, &intake, &storage).ToPtr());

	intakeM.WhileTrue(GroundGrabCommand(&superStructure, &storage, &intake));
	intakeM.OnFalse(ClosedCommand(&superStructure, &intake, &storage).ToPtr());
}

frc2::Command* RobotContainer::GetAutonomousCommand() {
	return autoChooser.GetSelected();
}

frc2::CommandPtr RobotContainer::GetTeleopResetCommand() {
	return frc2::cmd::Deadline(
		StorageCommand(&storage, 0_V).ToPtr(),
		ShooterCommand(&shooter, 0).ToPtr(),
		IntakeCommand(&intake, 0_V).ToPtr()
	);
}
