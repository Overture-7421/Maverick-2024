// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "Robot.h"

#include <frc2/command/CommandScheduler.h>
#include <frc/DataLogManager.h>
#include <iostream>

void Robot::RobotInit() {
#ifndef __FRC_ROBORIO__
	simMotorManager.Init({
	  {2, "Sample Robot/motors/back_right_drive"},
	  {4, "Sample Robot/motors/back_left_drive"},
	  {6, "Sample Robot/motors/front_left_drive"},
	  {8, "Sample Robot/motors/front_right_drive"},

	  {1, "Sample Robot/motors/back_right_rotation"},
	  {3, "Sample Robot/motors/back_left_rotation"},
	  {5, "Sample Robot/motors/front_left_rotation"},
	  {7, "Sample Robot/motors/front_right_rotation"},

		});

	simPigeonManager.Init("Sample Robot/imu");

	simCANCoderManager.Init({
	  {9, "Sample Robot/cancoders/back_right_cancoder"},
	  {10, "Sample Robot/cancoders/back_left_cancoder"},
	  {11, "Sample Robot/cancoders/front_left_cancoder"},
	  {12, "Sample Robot/cancoders/front_right_cancoder"}
		});

	simDutyCycleEncoderManager.Init({});
#endif

	m_teleopResetCommand = m_container.GetTeleopResetCommand();
	AddPeriodic([&] {
		frc2::CommandScheduler::GetInstance().Run();
	}, RobotConstants::LoopTime, RobotConstants::TimingOffset);

	photon::PhotonCamera::SetVersionCheckEnabled(false);
	frc::DriverStation::SilenceJoystickConnectionWarning(true);
}

void Robot::RobotPeriodic() {
	m_container.UpdateTelemetry();
}

void Robot::DisabledInit() {
	frc2::CommandScheduler::GetInstance().CancelAll();
}

void Robot::DisabledPeriodic() {}

void Robot::DisabledExit() {}

void Robot::AutonomousInit() {
	m_autonomousCommand = m_container.GetAutonomousCommand();

	if (m_autonomousCommand) {
		m_autonomousCommand->Schedule();
	}

	VisionSpeakerCommand::LoadAllianceOffset();
}

void Robot::AutonomousPeriodic() {}

void Robot::AutonomousExit() {}

void Robot::TeleopInit() {
	if (m_autonomousCommand) {
		m_autonomousCommand->Cancel();
	}
	m_teleopResetCommand->Schedule();

	VisionSpeakerCommand::LoadAllianceOffset();
}

void Robot::TeleopPeriodic() {}

void Robot::TeleopExit() {}

void Robot::TestInit() {
	frc2::CommandScheduler::GetInstance().CancelAll();
}

void Robot::TestPeriodic() {}

void Robot::TestExit() {}

#ifndef RUNNING_FRC_TESTS
int main() {
	return frc::StartRobot<Robot>();
}
#endif

