// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

// FIXME: Figure out what speed controllers we're using
// TODO: Teleop Control
// TODO: - Decide on a control scheme
// TODO: X Drive Train
// TODO: - Hide all of it behind a nice class that makes it look friendly and not scary at all
// TODO: - Fake swivel drives with omindirs and a fancy coordinate system

#include "XDriveRobot.hpp"

#include <frc2/command/CommandScheduler.h>

void XDriveRobot::RobotInit() {
  m_controller = frc::XboxController{0};
}

/**
 * This function is called every 20 ms, no matter the mode. Use
 * this for items like diagnostics that you want to run during disabled,
 * autonomous, teleoperated and test.
 *
 * <p> This runs after the mode specific periodic functions, but before
 * LiveWindow and SmartDashboard integrated updating.
 */
void XDriveRobot::RobotPeriodic() {
  frc2::CommandScheduler::GetInstance().Run();
}

/**
 * This function is called once each time the robot enters Disabled mode. You
 * can use it to reset any subsystem information you want to clear when the
 * robot is disabled.
 */
void XDriveRobot::DisabledInit() {}

void XDriveRobot::DisabledPeriodic() {}

/**
 * This autonomous runs the autonomous command selected by your {@link
 * RobotContainer} class.
 */
void XDriveRobot::AutonomousInit() {
  m_autonomousCommand = m_container.GetAutonomousCommand();

  if (m_autonomousCommand) {
    m_autonomousCommand->Schedule();
  }
}

void XDriveRobot::AutonomousPeriodic() {

}

void XDriveRobot::TeleopInit() {
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
void XDriveRobot::TeleopPeriodic() {

}

/**
 * This function is called periodically during test mode.
 */
void XDriveRobot::TestPeriodic() {}

/**
 * This function is called once when the robot is first started up.
 */
void XDriveRobot::SimulationInit() {
  
}

/**
 * This function is called periodically whilst in simulation.
 */
void XDriveRobot::SimulationPeriodic() {

}

#ifndef RUNNING_FRC_TESTS
int main() {
  return frc::StartRobot<XDriveRobot>();
}
#endif