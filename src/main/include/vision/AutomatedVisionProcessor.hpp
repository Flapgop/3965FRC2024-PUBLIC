
#include <drivers/MotorDriver.hpp>
#include <vision/LimelightHelpers.h>

class AVP {
private:
    MotorDriver* m_driver;
    float Kp = -0.1f;
    float min_command = 0.05f;

public:
    AVP(MotorDriver* driver);   
    void periodic();
};