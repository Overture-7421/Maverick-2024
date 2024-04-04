// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#pragma once

#include <frc2/command/SubsystemBase.h>
#include <frc/DigitalInput.h>
#include <frc/DigitalOutput.h>
#include <rev/ColorSensorV3.h>
#include <rev/Rev2mDistanceSensor.h>
#include <units/length.h>

#include "OvertureLib/MotorControllers/OverTalonFX/OverTalonFX.h"
#include "OvertureLib/MotorControllers/ControllerNeutralMode/ControllerNeutralMode.h"

#include "Constants.h"

#include <wpi/DataLog.h>
#include <frc/DataLogManager.h>
#include <frc/Ultrasonic.h>

class Storage : public frc2::SubsystemBase {
public:
	Storage();
	void setVoltage(units::volt_t voltage);
	bool isNoteOnForwardSensor();
	bool isSensorAvailable();
	void Periodic() override;
	void shuffleboardPeriodic();
private:
	OverTalonFX storageMotor{ 30, ControllerNeutralMode::Brake, false, "rio" };
	// rev::ColorSensorV3 colorSensor{frc::I2C::Port::kMXP};
	// int IRvalue = 0;
	frc::DigitalInput echoPin {5}; // 10-25 are on the MXP port, DIO15  
	frc::DigitalOutput pingPin {6}; //10-25 are on the MXP port, DIO14
	frc::Ultrasonic distanceSensor {pingPin, echoPin};

	units::centimeter_t lastRange;
	units::second_t timeLastReading, timeSinceLastReading;
	bool isDistanceSensorConnected = true;

	wpi::log::DataLog& log = frc::DataLogManager::GetLog();
	wpi::log::BooleanLogEntry noteOnForward = wpi::log::BooleanLogEntry(log, "/storage/note_on_forward");
	wpi::log::DoubleLogEntry voltage = wpi::log::DoubleLogEntry(log, "/storage/voltage");
	wpi::log::DoubleLogEntry current = wpi::log::DoubleLogEntry(log, "/storage/current");
	wpi::log::DoubleLogEntry distance = wpi::log::DoubleLogEntry(log, "/storage/distance_sensor");
	wpi::log::BooleanLogEntry sensorAvailable = wpi::log::BooleanLogEntry(log, "/storage/sensor_available");

};
