#include "Constants.h"
#include "MotorDriver.hpp"
#include MOTOR_INCLUDE

class OmniDriver : public MotorDriver {
private:
    const MOTOR* m_frontLeftMotor;
    const MOTOR* m_frontRightMotor;
    const MOTOR* m_backLeftMotor;
    const MOTOR* m_backRightMotor;
public:
    OmniDriver(
        MOTOR* frontLeftMotor,
        MOTOR* frontRightMotor,
        MOTOR* backLeftMotor, 
        MOTOR* backRightMotor):
        m_frontLeftMotor(frontLeftMotor),
        m_frontRightMotor(frontRightMotor),
        m_backLeftMotor(backLeftMotor),
        m_backRightMotor(backRightMotor)
    {
        
    }
};