// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "Robot.h"

#include <frc2/command/CommandScheduler.h>

void Robot::RobotInit() {
#ifndef __FRC_ROBORIO__
  simMotorManager->Init("GLIP", {{0, "chassis_to_arm_joint"}, {1, "arm_to_shooter_intake_joint"}});
  simPigeonManager->Init("GLIP", "imu");
  simCANCoderManager->Init("GLIP", {{2, "cancoder_one"}, {3, "cancoder_two"}});
#endif
}

void Robot::RobotPeriodic() {
  frc2::CommandScheduler::GetInstance().Run();
}

void Robot::DisabledInit() {
}

void Robot::DisabledPeriodic() {
}

void Robot::DisabledExit() {
}

void Robot::AutonomousInit() {
  m_autonomousCommand = m_container.GetAutonomousCommand();

  if (m_autonomousCommand) {
     m_autonomousCommand->Schedule();
  }
}

void Robot::AutonomousPeriodic() {
}

void Robot::AutonomousExit() {
}

void Robot::TeleopInit() {
  if (m_autonomousCommand) {
    m_autonomousCommand->Cancel();
  }
}

void Robot::TeleopPeriodic() {
}

void Robot::TeleopExit() {
}

void Robot::TestInit() {
  frc2::CommandScheduler::GetInstance().CancelAll();
}

void Robot::TestPeriodic() {
}

void Robot::TestExit() {
}

#ifndef RUNNING_FRC_TESTS
int main() {
  return frc::StartRobot<Robot>();
}
#endif

