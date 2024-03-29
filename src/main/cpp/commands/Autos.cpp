// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "commands/Autos.h"

#include <frc2/command/Commands.h>

#include <commands/ExampleCommand.h>
#include <commands/CVTestCommand.h>

frc2::CommandPtr autos::ExampleAuto(ExampleSubsystem* subsystem) {
  return frc2::cmd::Sequence(subsystem->ExampleMethodCommand(),
                             ExampleCommand(subsystem).ToPtr());
}

frc2::CommandPtr autos::ComputerVisionAuto(CVSubsystem* subsystem) {
  return frc2::cmd::Sequence(subsystem->SubsystemStartup(), CVTestCommand(subsystem).ToPtr());
}