// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "SuperStructureMoveByDistance.h"

SuperStructureMoveByDistance::SuperStructureMoveByDistance(SuperStructure* superStructure, Profile profile, std::function<units::meter_t()> distanceToTargetProvider) {
	this->superStructure = superStructure;
	this->profile = profile;
	this->distanceToTargetProvider = distanceToTargetProvider;

	upperAngleTravel = profile.targetState.upperAngle - profile.startingState.upperAngle;
	lowerAngleTravel = profile.targetState.lowerAngle - profile.startingState.lowerAngle;
	AddRequirements(superStructure);
}

// Called when the command is initially scheduled.
void SuperStructureMoveByDistance::Initialize() {
	superStructure->setTargetCoord(profile.startingState);
}

// Called repeatedly when this Command is scheduled to run
void SuperStructureMoveByDistance::Execute() {
	distanceToTarget = units::math::abs(distanceToTargetProvider());
	frc::SmartDashboard::PutNumber("SuperStructureMoveByDistance/Distance", distanceToTarget.value());

	if (distanceToTarget < profile.profileActivationDistance) {
		SuperStructureState targetState;

		double inverseNormalizedDistance = 1.0 - (distanceToTarget / profile.profileActivationDistance).value();

		frc::SmartDashboard::PutNumber("SuperStructureMoveByDistance/InverseNormalizedDistance", inverseNormalizedDistance);


		targetState.upperAngle = profile.startingState.upperAngle + upperAngleTravel * inverseNormalizedDistance;
		targetState.lowerAngle = profile.startingState.lowerAngle + lowerAngleTravel * inverseNormalizedDistance;

		frc::SmartDashboard::PutNumber("SuperStructureMoveByDistance/TargetLower", targetState.lowerAngle.value());
		frc::SmartDashboard::PutNumber("SuperStructureMoveByDistance/TargetUpper", targetState.upperAngle.value());

		superStructure->setTargetCoord(targetState);
	}

}

// Called once the command ends or is interrupted.
void SuperStructureMoveByDistance::End(bool interrupted) {}

// Returns true when the command should end.
bool SuperStructureMoveByDistance::IsFinished() {
	return distanceToTarget < 0.01_m;
}
