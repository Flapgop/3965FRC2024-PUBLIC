// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

// NOTE: We're using SPARK MAX motor controllers
// NOTE: We may have to use Talon motor controllers if we don't have enough sparks

// ==============================================

#include "Constants.h"
#include <wpinet/PortForwarder.h>
#include <frc/TimedRobot.h>
#include <frc/motorcontrol/MotorController.h>
#include <frc2/command/CommandPtr.h>
#include <frc2/command/CommandScheduler.h>

// TODO: Maybe add more driver methods
#ifdef OMNI_WHEELS
#include "OmniDriver.cpp"
#else
#include "LeadFollowDriver.cpp"
#endif

#ifdef LIMELIGHT
#include "AutomatedVisionProcessor.cpp"
#endif

#include "RobotContainer.h"
#include "rev/CANSparkMax.h"

class Robot : public frc::TimedRobot {
private:
  // Have it empty by default so that if testing teleop it
  // doesn't have undefined behavior and potentially crash.
  std::optional<frc2::CommandPtr> m_autonomousCommand;

  RobotContainer m_container;

  // Motor ids, lf = left front, rb = right back, etc etc.
  // TODO: Configure these in Spark MAX Client
  static const int g_lfid = 0, g_rfid = 1, g_lbid = 2, g_rbid = 3;
  rev::CANSparkMax m_leftFrontMotor{g_lfid, rev::CANSparkMaxLowLevel::MotorType::kBrushed};
  rev::CANSparkMax m_rightFrontMotor{g_rfid, rev::CANSparkMaxLowLevel::MotorType::kBrushed};
  rev::CANSparkMax m_leftBackMotor{g_lbid, rev::CANSparkMaxLowLevel::MotorType::kBrushed};
  rev::CANSparkMax m_rightBackMotor{g_rbid, rev::CANSparkMaxLowLevel::MotorType::kBrushed};

  frc::XboxController m_controller{0};
  MotorDriver* m_driver;
  #ifdef LIMELIGHT
  AVP* m_visionProcessor;
  #endif

public:

  void RobotInit() {
    #ifdef OMNI_WHEELS
    m_driver = new OmniDriver(&m_leftFrontMotor, &m_rightFrontMotor, new frc::MotorController*[]{&m_leftBackMotor}, new frc::MotorController*[]{&m_rightBackMotor});
    #else
    m_driver = new LeadFollowDriver(1.0f, &m_leftFrontMotor, &m_rightFrontMotor, new frc::MotorController*[]{&m_leftBackMotor}, new frc::MotorController*[]{&m_rightBackMotor});
    #endif

    #ifdef LIMELIGHT
    m_visionProcessor = new AVP(m_driver);
    for (int port = 5800; port <= 5805; port++)
    {
        wpi::PortForwarder::GetInstance().Add(port, "limelight.local", port);
    }
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
  void RobotPeriodic() override {
    frc2::CommandScheduler::GetInstance().Run();
  }

  /**
   * This function is called once each time the robot enters Disabled mode. You
   * can use it to reset any subsystem information you want to clear when the
   * robot is disabled.
   */
  void DisabledInit() override {}

  void DisabledPeriodic() override {}

  /**
   * This autonomous runs the autonomous command selected by your {@link
   * RobotContainer} class.
   */
  void AutonomousInit() override {
    m_autonomousCommand = m_container.GetAutonomousCommand();

    if (m_autonomousCommand) {
      m_autonomousCommand->Schedule();
    }
  }

  void AutonomousPeriodic() override {
    #ifdef LIMELIGHT
    m_visionProcessor->periodic();
    #endif
  }

  void TeleopInit() override {
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
  void TeleopPeriodic() override {
    #ifdef OMNI_WHEELS
    // TODO: Omni support
    #else
    m_driver->drive(frc::Translation2d{units::meter_t(m_controller.GetLeftY()), units::meter_t(0.0)});
    m_driver->rotate(m_controller.GetLeftX());
    #endif
  }

  /**
   * This function is called periodically during test mode.
   */
  void TestPeriodic() override {}

  /**
   * This function is called once when the robot is first started up.
   */
  void SimulationInit() override {
    
  }

  /**
   * This function is called periodically whilst in simulation.
   */
  void SimulationPeriodic() override {

  }

};

#ifndef RUNNING_FRC_TESTS
int main() {
  return frc::StartRobot<Robot>();
}
#endif
