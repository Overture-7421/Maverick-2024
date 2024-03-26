// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "AprilTagCamera.h"
AprilTagCamera::AprilTagCamera(Chassis* chassis) {
    this->swerveChassis = chassis;
    setCameraAndLayout(&camera, &tagLayout, &cameraToRobot);
}

frc::Translation2d AprilTagCamera::GetSpeakerLocation() {
    if (isRedAlliance()) {
        return tagLayout.GetTagPose(4).value().ToPose2d().Translation();
    } else {
        return tagLayout.GetTagPose(7).value().ToPose2d().Translation();
    }
};
