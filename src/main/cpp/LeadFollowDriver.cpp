
#include "Errors.cpp"
#include "Constants.h"
#include "MotorDriver.hpp"
#include MOTOR_INCLUDE
#include <cmath>

// WARNING::::::::::::::::::::::::::::::::::::::::::::::::::::::
// This class is extremely motor dependant, expect errors when changing MOTOR constants

class LeadFollowDriver : public MotorDriver  {
private:
    MOTOR* m_leadLeftMotor;
    MOTOR* m_leadRightMotor;
    MOTOR* m_followLeftMotors[8];
    MOTOR* m_followRightMotors[8];
    double m_maxSpeed;

public:
    LeadFollowDriver(
        double maxSpeed, // Hard limit so you don't overdo it.
        MOTOR* leadLeftMotor,
        MOTOR* leadRightMotor,
        MOTOR* followLeftMotors[8], 
        MOTOR* followRightMotors[8]):
        m_maxSpeed(maxSpeed),
        m_leadLeftMotor(leadLeftMotor),
        m_leadRightMotor(leadRightMotor)
    {
        for (int i = 0; i < 8; i++) {
            m_followLeftMotors[i] = followLeftMotors[i];
            m_followRightMotors[i] = followRightMotors[i];
        
            m_followLeftMotors[i]->Follow(*m_leadLeftMotor);
            m_followRightMotors[i]->Follow(*m_leadRightMotor);
        }
    }

    void drive(frc::Translation2d vec) override {
        if (vec.X().value() != 0.0) {
            throw Error::ErrorCode::UNSUPPORTED_OPERATION;
        }
        m_leadLeftMotor->Set(std::clamp(vec.Y().value(), -m_maxSpeed, m_maxSpeed));
        m_leadRightMotor->Set(std::clamp(vec.Y().value(), -m_maxSpeed, m_maxSpeed));
    }

    void rotate(double amount) override {
        if (amount != 0.0) {
            throw Error::ErrorCode::UNSUPPORTED_OPERATION;
        }
        m_leadLeftMotor->Set(std::clamp(amount, -m_maxSpeed, m_maxSpeed));
        m_leadRightMotor->Set(std::clamp(-amount, -m_maxSpeed, m_maxSpeed));
    }

    ~LeadFollowDriver() {
        delete[] m_followLeftMotors;
        delete[] m_followRightMotors;
    }
};