#pragma once

#include <units/length.h>
#include <frc/geometry/Translation2d.h>

namespace ChassisConstants {
    const static double RotationGearRatio = 150.0 / 7.0;
    const static double DriveGearRatio =  5.9027777;
    const static units::meter_t WheelDiameter = 0.1016_m;

    const static frc::Translation2d FrontLeftModuleTranslation = {7.506890_in, 10.375_in};
    const static frc::Translation2d FrontRightModuleTranslation = {7.506890_in, -10.375_in};
     const static frc::Translation2d BackLeftModuleTranslation = {-13.243110_in, 10.375_in};
    const static frc::Translation2d BackRightModuleTranslation = {-13.243110_in, -10.375_in};
};