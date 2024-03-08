#include "drivers/MotorDriver.hpp"
#include <frc/motorcontrol/MotorController.h>

class OmniDriver : public MotorDriver {
private:
    const frc::MotorController* m_frontLeftMotor;
    const frc::MotorController* m_frontRightMotor;
    const frc::MotorController* m_backLeftMotor;
    const frc::MotorController* m_backRightMotor;
public:
    OmniDriver(
        frc::MotorController* frontLeftMotor,
        frc::MotorController* frontRightMotor,
        frc::MotorController* backLeftMotor, 
        frc::MotorController* backRightMotor):
        m_frontLeftMotor(frontLeftMotor),
        m_frontRightMotor(frontRightMotor),
        m_backLeftMotor(backLeftMotor),
        m_backRightMotor(backRightMotor)
    {
        
    }

    double getDistanceTraveled() {
        return 0.0; // TODO;
    }

    void drive(frc::Translation2d vec) override {
        // TODO:
    }

    void rotate(double amount) override {
        // TODO:
    }
};