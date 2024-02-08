#include "rev/SparkAbsoluteEncoder.h"

#include <drivers/MotorDriver.hpp>
#include <frc/motorcontrol/MotorController.h>

#include <cmath>
#include <iostream>

namespace RobotError {
    enum ErrorCode {
        NO_ERROR = 0,
        UNSUPPORTED_OPERATION
    };

    // TODO: Figure out why this causes problems
    // std::string getErrorString(ErrorCode code) {
    //     switch (code) {
    //     case NO_ERROR:
    //         return "No error.";
    //         break;
    //     case UNSUPPORTED_OPERATION:
    //         return "Unsupported Operation.";
    //         break;

    //     default:
    //         return "Unknown Error";
    //     }
    // }
}

class LeadFollowDriver : public MotorDriver  {
private:

    frc::MotorController* m_leadLeftMotor;
    frc::MotorController* m_leadRightMotor;
    frc::MotorController* m_followLeftMotors[8];
    frc::MotorController* m_followRightMotors[8];
    double m_maxSpeed;

public:
    LeadFollowDriver(
        double maxSpeed, // Hard limit so you don't overdo it.
        frc::MotorController* leadLeftMotor,
        frc::MotorController* leadRightMotor,
        frc::MotorController* followLeftMotors[8], 
        frc::MotorController* followRightMotors[8]):
        m_maxSpeed(maxSpeed),
        m_leadLeftMotor(leadLeftMotor),
        m_leadRightMotor(leadRightMotor)
    {
        for (int i = 0; i < 8; i++) {
            m_followLeftMotors[i] = followLeftMotors[i];
            m_followRightMotors[i] = followRightMotors[i];
        
            // TODO
            // m_followLeftMotors[i]->Follow(*m_leadLeftMotor);
            // m_followRightMotors[i]->Follow(*m_leadRightMotor);
        }
    }

    double getDistanceTraveled() {
        return 0.0; // TODO
    }

    void drive(frc::Translation2d vec) override {
        if (vec.X().value() != 0.0) {
            throw RobotError::ErrorCode::UNSUPPORTED_OPERATION;
        }
        m_leadLeftMotor->Set(std::clamp(vec.Y().value(), -m_maxSpeed, m_maxSpeed));
        m_leadRightMotor->Set(std::clamp(vec.Y().value(), -m_maxSpeed, m_maxSpeed));
        for (frc::MotorController* motor : m_followLeftMotors) 
            motor->Set(std::clamp(vec.Y().value(), -m_maxSpeed, m_maxSpeed));
        for (frc::MotorController* motor : m_followRightMotors)
            motor->Set(std::clamp(vec.Y().value(), -m_maxSpeed, m_maxSpeed));
    }

    void rotate(double amount) override {
        if (amount != 0.0) {
            throw RobotError::ErrorCode::UNSUPPORTED_OPERATION;
        }
        m_leadLeftMotor->Set(std::clamp(amount, -m_maxSpeed, m_maxSpeed));
        m_leadRightMotor->Set(std::clamp(-amount, -m_maxSpeed, m_maxSpeed));
        for (frc::MotorController* motor : m_followLeftMotors) 
            motor->Set(std::clamp(amount, -m_maxSpeed, m_maxSpeed));
        for (frc::MotorController* motor : m_followRightMotors)
            motor->Set(std::clamp(-amount, -m_maxSpeed, m_maxSpeed));
    }

    ~LeadFollowDriver() {
        delete[] m_followLeftMotors;
        delete[] m_followRightMotors;
    }
};