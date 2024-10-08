// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#pragma once

#include <frc2/command/SubsystemBase.h>
#include <frc2/command/Commands.h>

#include <OvertureLib/MotorControllers/OverTalonFX/OverTalonFX.h>
#include <OvertureLib/MotorControllers/ControllerNeutralMode/ControllerNeutralMode.h>
#include "Constants.h"

#include <wpi/DataLog.h>
#include <frc/DataLogManager.h>

class Intake : public frc2::SubsystemBase {
public:
	Intake();
	void setVoltage(units::volt_t voltage);
	double getVoltage();
	void Periodic() override;
	void shuffleboardPeriodic();
	frc2::CommandPtr intakeCommand(units::volt_t voltage);
	double voltageOut = 0.0;

private:
	OverTalonFX intakeMotorLeft{ 20, ControllerNeutralMode::Brake, false, "rio" };


	wpi::log::DataLog& log = frc::DataLogManager::GetLog();
	wpi::log::DoubleLogEntry voltage = wpi::log::DoubleLogEntry(log, "/intake/voltage");
	wpi::log::DoubleLogEntry currentLeft = wpi::log::DoubleLogEntry(log, "/intake/current_left");
};
