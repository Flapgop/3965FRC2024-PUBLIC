// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

// NOTE: We're using SPARK MAX motors

// NOTE: If uncomment this line if you're using omni wheels (adds extra functionality)
// #define OMNI_WHEELS

#include <frc/TimedRobot.h>
#include <frc2/command/CommandPtr.h>
#include <frc2/command/CommandScheduler.h>

// TODO: Maybe add more driver methods
#ifdef OMNI_WHEELS
#include "OmniDriver.cpp"
#else
#include "LeadFollowDriver.cpp"
#endif

#include "Constants.h"
#include "RobotContainer.h"
#include MOTOR_INCLUDE

class Robot : public frc::TimedRobot {
private:
  // Have it empty by default so that if testing teleop it
  // doesn't have undefined behavior and potentially crash.
  std::optional<frc2::CommandPtr> m_autonomousCommand;

  RobotContainer m_container;

  // Motor ids, lf = left front, rb = right back, etc etc.
  // TODO: Configure these in Spark MAX Client
  static const int g_lfid = 0, g_rfid = 1, g_lbid = 2, g_rbid = 3;
  MOTOR m_leftFrontMotor{g_lfid, rev::CANSparkMaxLowLevel::MotorType::kBrushed};
  MOTOR m_rightFrontMotor{g_rfid, rev::CANSparkMaxLowLevel::MotorType::kBrushed};
  MOTOR m_leftBackMotor{g_lbid, rev::CANSparkMaxLowLevel::MotorType::kBrushed};
  MOTOR m_rightBackMotor{g_rbid, rev::CANSparkMaxLowLevel::MotorType::kBrushed};

  frc::XboxController m_controller{0};
  MotorDriver m_driver;

public:

  void Robot::RobotInit() {
    #ifdef OMNI_WHEELS
    m_driver = OmniDriver{&m_leftFrontMotor, &m_rightFrontMotor, new MOTOR*[]{&m_leftBackMotor}, new MOTOR*[]{&m_rightBackMotor}};
    #else
    m_driver = LeadFollowDriver{1.0f, &m_leftFrontMotor, &m_rightFrontMotor, new MOTOR*[]{&m_leftBackMotor}, new MOTOR*[]{&m_rightBackMotor}};
    #endif
  }

  /**
   * This function is called every 20 ms, no matter the mode. Use
   * this for items like diagnostics that you want to run during disabled,
   * autonomous, teleoperated and test.
   *
   * <p> This runs after the mode specific periodic functions, but before
   * LiveWindow and SmartDashboard integrated updating.
   */
  void Robot::RobotPeriodic() override {
    frc2::CommandScheduler::GetInstance().Run();
  }

  /**
   * This function is called once each time the robot enters Disabled mode. You
   * can use it to reset any subsystem information you want to clear when the
   * robot is disabled.
   */
  void Robot::DisabledInit() override {}

  void Robot::DisabledPeriodic() override {}

  /**
   * This autonomous runs the autonomous command selected by your {@link
   * RobotContainer} class.
   */
  void Robot::AutonomousInit() override {
    m_autonomousCommand = m_container.GetAutonomousCommand();

    if (m_autonomousCommand) {
      m_autonomousCommand->Schedule();
    }
  }

  void Robot::AutonomousPeriodic() override {

  }

  void Robot::TeleopInit() override {
    // This makes sure that the autonomous stops running when
    // teleop starts running. If you want the autonomous to
    // continue until interrupted by another command, remove
    // this line or comment it out.
    if (m_autonomousCommand) {
      m_autonomousCommand->Cancel();
    }
  }

  /**
   * This function is called periodically during operator control.
   */
  void Robot::TeleopPeriodic() override {
    #ifdef OMNI_WHEELS
    // TODO: Omni support
    #else
    m_driver.drive(frc::Translation2d{units::meter_t(m_controller.GetLeftY()), units::meter_t(0.0)});
    m_driver.rotate(m_controller.GetLeftX());
    #endif
  }

  /**
   * This function is called periodically during test mode.
   */
  void Robot::TestPeriodic() override {}

  /**
   * This function is called once when the robot is first started up.
   */
  void Robot::SimulationInit() override {
    
  }

  /**
   * This function is called periodically whilst in simulation.
   */
  void Robot::SimulationPeriodic() override {

  }

};

#ifndef RUNNING_FRC_TESTS
int main() {
  return frc::StartRobot<Robot>();
}
#endif
