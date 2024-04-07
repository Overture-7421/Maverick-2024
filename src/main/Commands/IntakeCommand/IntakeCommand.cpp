// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "IntakeCommand.h"

#include "Commands/IntakeCommand/IntakeCommand.h"

IntakeCommand::IntakeCommand(Intake* intake, units::volt_t voltage) {
    this->intake = intake;
    this->voltage = voltage;
    AddRequirements({intake});
}

// Called when the command is initially scheduled.
void IntakeCommand::Initialize() {
    intake->setVoltage(voltage);
}

// Called repeatedly when this Command is scheduled to run
void IntakeCommand::Execute() {}


// Called once the command ends or is interrupted.
void IntakeCommand::End(bool interrupted) {}


// Returns true when the command should end.
bool IntakeCommand::IsFinished() {
  return true;
}
