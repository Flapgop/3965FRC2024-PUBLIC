#ifndef MOTOR_DRIVER_H
#define MOTOR_DRIVER_H
#pragma once

#include "frc/geometry/Translation2d.h"

class MotorDriver {
public:
    virtual void drive(frc::Translation2d amount);
    virtual void rotate(double amount);
};
#endif