#pragma once

#include <units/length.h>
#include <units/velocity.h>
#include <frc/geometry/Translation2d.h>
#include <OvertureLib/Subsystems/Swerve/SwerveModule/ModuleConfig.h>

namespace ChassisConstants {
	const static double TurnGearRatio = 150.0 / 7.0;
	const static double DriveGearRatio = 5.9027777;
	const static units::meters_per_second_t MaxModuleSpeed = 5.39_mps;
	const static units::radians_per_second_t MaxAngularSpeed = 1.5_tps;
	const static units::meter_t DriveBaseRadius = 0.3732276_m;
	const static units::meter_t WheelDiameter = 4_in;

	const static frc::Translation2d FrontLeftModuleTranslation = { 7.625_in, 10.375_in };
	const static frc::Translation2d FrontRightModuleTranslation = { 7.625_in, -10.375_in };
	const static frc::Translation2d BackLeftModuleTranslation = { -13.125_in, 10.375_in };
	const static frc::Translation2d BackRightModuleTranslation = { -13.125_in, -10.375_in };

	const static std::string CanBus = "OverCANivore";

	static ModuleConfig GetFrontLeftModuleConfig() {
		static ModuleConfig config{
			{0.22436_V, 2.0254_V / 1_mps, 0.2019_V / 1_mps_sq}
		};

		config.DrivedId = 6;
		config.TurnId = 5;
		config.CanCoderId = 11;
		config.ModuleName = "FrontLeftModule";

#ifndef __FRC_ROBORIO__
		config.Offset = -90_deg;
#else
		config.Offset = 0.057373046875_tr;
#endif

		config.CanBus = ChassisConstants::CanBus;
		config.DriveNeutralMode = ControllerNeutralMode::Brake;
		config.TurnNeutralMode = ControllerNeutralMode::Coast;
		config.DriveGearRatio = ChassisConstants::DriveGearRatio;
		config.TurnGearRatio = ChassisConstants::TurnGearRatio;
		config.WheelDiameter = ChassisConstants::WheelDiameter;
		config.kP = 53.0;

		return config;
	}

	static ModuleConfig GetFrontRightModuleConfig() {
		static ModuleConfig config{
			{0.22436_V, 2.0254_V / 1_mps, 0.2019_V / 1_mps_sq}
		};

		config.DrivedId = 8;
		config.TurnId = 7;
		config.CanCoderId = 12;
		config.ModuleName = "FrontRightModule";

#ifndef __FRC_ROBORIO__
		config.Offset = -90_deg;
#else
	config.Offset = 0.377197265625_tr;
#endif

		config.CanBus = ChassisConstants::CanBus;
		config.DriveNeutralMode = ControllerNeutralMode::Brake;
		config.TurnNeutralMode = ControllerNeutralMode::Coast;
		config.DriveGearRatio = ChassisConstants::DriveGearRatio;
		config.TurnGearRatio = ChassisConstants::TurnGearRatio;
		config.WheelDiameter = ChassisConstants::WheelDiameter;
		config.kP = 53.0;

		return config;
	}

	static ModuleConfig GetBackLeftModuleConfig() {
		static ModuleConfig config{
			{0.22436_V, 2.0254_V / 1_mps, 0.2019_V / 1_mps_sq}
		};

		config.DrivedId = 4;
		config.TurnId = 3;
		config.CanCoderId = 10;
		config.ModuleName = "BackLeftModule";

#ifndef __FRC_ROBORIO__
		config.Offset = -90_deg;
#else
		config.Offset =  -0.451171875_tr;
#endif

		config.CanBus = ChassisConstants::CanBus;
		config.DriveNeutralMode = ControllerNeutralMode::Brake;
		config.TurnNeutralMode = ControllerNeutralMode::Coast;
		config.DriveGearRatio = ChassisConstants::DriveGearRatio;
		config.TurnGearRatio = ChassisConstants::TurnGearRatio;
		config.WheelDiameter = ChassisConstants::WheelDiameter;
		config.kP = 53.0;

		return config;
	}

	static ModuleConfig GetBackRightModuleConfig() {
		static ModuleConfig config{
			{0.22436_V, 2.0254_V / 1_mps, 0.2019_V / 1_mps_sq}
		};

		config.DrivedId = 2;
		config.TurnId = 1;
		config.CanCoderId = 9;

#ifndef __FRC_ROBORIO__
		config.Offset = -90_deg;
#else
		config.Offset = -0.42041015625_tr;
#endif

		config.ModuleName = "BackRightModule";
		config.CanBus = ChassisConstants::CanBus;
		config.DriveNeutralMode = ControllerNeutralMode::Brake;
		config.TurnNeutralMode = ControllerNeutralMode::Coast;
		config.DriveGearRatio = ChassisConstants::DriveGearRatio;
		config.TurnGearRatio = ChassisConstants::TurnGearRatio;
		config.WheelDiameter = ChassisConstants::WheelDiameter;
		config.kP = 53.0;

		return config;
	}
};