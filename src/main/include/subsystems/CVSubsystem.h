

#pragma once

#include <vision/AutomatedVisionProcessor.hpp>
#include <frc2/command/CommandPtr.h>
#include <frc2/command/SubsystemBase.h>

class CVSubsystem : public frc2::SubsystemBase {
 public:
  CVSubsystem();

  /**
   * Command factory method.
   */
  frc2::CommandPtr SubsystemStartup();

  /**
   * If this subsystem should run (it probably should)
   *
   * @return value of some boolean subsystem state, such as a digital sensor or something.
   */
  bool ShouldRun();

  /**
   * Will be called periodically whenever the CommandScheduler runs.
   */
  void Periodic() override;

  /**
   * Will be called periodically whenever the CommandScheduler runs during
   * simulation.
   */
  void SimulationPeriodic() override;

 private:
  // Components (e.g. motor controllers and sensors) should generally be
  // declared private and exposed only through public methods.
  AVP* m_visionProcessor;
};