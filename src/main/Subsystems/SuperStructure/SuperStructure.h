// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#pragma once

#include <frc2/command/SubsystemBase.h>
#include <frc/controller/ArmFeedforward.h>
#include <frc/controller/ProfiledPIDController.h>
#include <frc/trajectory/TrapezoidProfile.h>

#include <OvertureLib/MotorControllers/OverTalonFX/OverTalonFX.h>
#include <OvertureLib/Sensors/OverCANCoder/OverCANCoder.h>
#include <OvertureLib/MotorControllers/ControllerNeutralMode/ControllerNeutralMode.h>
#include <OvertureLib/Sensors/OverDutyCycleEncoder/OverDutyCycleEncoder.h>
#include <frc2/command/sysid/SysIdRoutine.h>
#include <frc2/command/Commands.h>
#include <units/angular_velocity.h>
#include <units/angular_acceleration.h>
#include <units/angle.h>

#include <numbers>
#include <frc/estimator/KalmanFilter.h>
#include <frc/controller/LinearQuadraticRegulator.h>
#include <frc/system/LinearSystemLoop.h>
#include <frc/system/plant/LinearSystemId.h>

#include "Constants.h"
#include "SuperStructureState.h"
#include <OvertureLib/Robots/OverRobot/RobotConstants.h>

#include <frc2/command/Commands.h>

//Offset Lower  -0.32608
//Offset Upper -0.21753

class SuperStructure : public frc2::SubsystemBase {
public:
	SuperStructure();
	void setTargetCoord(SuperStructureState targetState);
	units::degree_t getLowerAngle();
	units::degree_t getUpperAngle();
	bool reachedTargetPosition(SuperStructureState targetState);
	frc2::CommandPtr superStructureCommand(SuperStructureState targetState);

	void setArbitraryFeedForwardUpper(units::volt_t feedforward);

	frc2::CommandPtr sysIdQuasistaticLower(frc2::sysid::Direction direction) {
		return sysIdRoutineLower.Quasistatic(direction);
	}

	frc2::CommandPtr sysIdDynamicLower(frc2::sysid::Direction direction) {
		return sysIdRoutineLower.Dynamic(direction);
	}

	frc2::CommandPtr sysIdQuasistaticUpper(frc2::sysid::Direction direction) {
		return frc2::cmd::Sequence(
			frc2::cmd::Run([this] {setTargetCoord({ 0_deg, 0_deg });}).WithTimeout(1.5_s),
			sysIdRoutineUpper.Quasistatic(direction)
		);
	}

	frc2::CommandPtr sysIdDynamicUpper(frc2::sysid::Direction direction) {
		return frc2::cmd::Sequence(
			frc2::cmd::Run([this] {setTargetCoord({ 0_deg, 0_deg });}).WithTimeout(1.5_s),
			sysIdRoutineUpper.Dynamic(direction)
		);
	}

	SuperStructureState getCurrentState();
	void Periodic() override;
	void shuffleboardPeriodic();

private:

	units::volt_t arbitraryFeedForwardUpper = 0_V;
	// LowerMotors
	OverTalonFX lowerRightMotor{ 21, ControllerNeutralMode::Brake, false, "rio" };
	OverTalonFX lowerLeftMotor{ 22, ControllerNeutralMode::Brake, true, "rio" };

	// Upper Motors
	OverTalonFX upperMotor{ 23, ControllerNeutralMode::Brake, true, "rio" };

	// Encoders
	OverCANCoder lowerCANCoder{ 28, -0.3132_tr, "rio" };
	OverCANCoder upperCANCoder{ 27, 183.779297_deg , "rio" };

	// State
	SuperStructureState targetState, actualTarget;
	SuperStructureState currentState;

	//Feed Forward
	frc::ArmFeedforward lowerFeedForward{ 0.3_V, 0.385_V, 0.44488_V / 1_tps, 6.753_V / 1_tr_per_s_sq };
	frc::ArmFeedforward upperFeedForward{ 0.7_V, 0.9_V, 0.6_V / 1_tps, 4_V / 1_tr_per_s_sq };

	frc2::sysid::SysIdRoutine sysIdRoutineLower{
		frc2::sysid::Config{0.5_V / 1_s, 7_V, 10_s,
							std::nullopt},
		frc2::sysid::Mechanism{
			[this](units::volt_t driveVoltage) {
				lowerLeftMotor.SetVoltage(driveVoltage);
			},
			[this](frc::sysid::SysIdRoutineLog* log) {

			log->Motor("SuperStructureLower")
				.voltage(lowerLeftMotor.GetMotorVoltage().GetValue())
				.position(lowerLeftMotor.GetPosition().GetValue())
				.velocity(lowerLeftMotor.GetVelocity().GetValue());
			},
			this} };

	frc2::sysid::SysIdRoutine sysIdRoutineUpper{
		frc2::sysid::Config{0.25_V / 1_s, 4_V, 10_s,
							std::nullopt},
		frc2::sysid::Mechanism{
			[this](units::volt_t driveVoltage) {
				upperMotor.SetVoltage(driveVoltage);
			},
			[this](frc::sysid::SysIdRoutineLog* log) {

			log->Motor("SuperStructureUpper")
				.voltage(upperMotor.GetMotorVoltage().GetValue())
				.position(upperMotor.GetPosition().GetValue())
				.velocity(upperMotor.GetVelocity().GetValue());
			},
			this} };
};
