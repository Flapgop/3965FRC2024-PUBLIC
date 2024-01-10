
#pragma once

#include "frc/geometry/Translation2d.h"

class MotorDriver {
public:
    virtual void drive(frc::Translation2d amount);
};