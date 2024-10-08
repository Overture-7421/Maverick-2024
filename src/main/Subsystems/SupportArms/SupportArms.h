// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#pragma once

#include <frc2/command/SubsystemBase.h>
#include <frc/Servo.h>
#include <frc2/command/Commands.h>


class SupportArms : public frc2::SubsystemBase {
 public:
 
  SupportArms();

  /**
   * Will be called periodically whenever the CommandScheduler runs.
   */
  void Periodic() override;

  void 	SetAngle (double angle);

  frc2::CommandPtr freeArmsCommand(double angle);


 private:
  // Components (e.g. motor controllers and sensors) should generally be
  // declared private and exposed only through public methods.
  frc::Servo leftServo {7};
  frc::Servo rightServo {6};

};