
#include "LimelightHelpers.h"
#include <cmath>

// REQUIRES ENCODERS

// ideally, limelight is mounted lower or higher than the targets
// never position the limelight at the same height as targets

// inches
#define LIMELIGHT_HEIGHT 24.0
// degrees
#define LIMELIGHT_ANGLE 45.0 
// inches
#define TARGET_HEIGHT 52.0


class AVP {
private:
    MotorDriver* m_driver;
    float Kp = -0.1f;
    float min_command = 0.05f;

public:
    AVP(MotorDriver* driver) : m_driver(driver) {

    }

    void periodic() {
        // adjust rotation to match target
        double tx = LimelightHelpers::getTX();
        float heading_error = -tx;
        float steering_adjust = 0.0f;
        if (fabsf(heading_error) > 1.0) {
            if (heading_error < 0) {
                steering_adjust = Kp * heading_error + min_command;
            } else {
                steering_adjust = Kp * heading_error - min_command;
            }
        }
        m_driver->rotate(steering_adjust);

        // calculate distance to target in inches
        double ty = LimelightHelpers::getTY();
        double distance = (TARGET_HEIGHT-LIMELIGHT_HEIGHT) / tan((LIMELIGHT_ANGLE+ty)*(3.14159 / 180.0));

    }
};