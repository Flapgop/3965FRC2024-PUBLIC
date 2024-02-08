
#pragma once

#include <frc2/command/Command.h>
#include <frc2/command/CommandHelper.h>

#include "subsystems/CVSubsystem.h"

/**
 * An example command that uses an example subsystem.
 *
 * <p>Note that this extends CommandHelper, rather extending Command
 * directly; this is crucially important, or else the decorator functions in
 * Command will *not* work!
 */
class CVTestCommand
    : public frc2::CommandHelper<frc2::Command, CVTestCommand> {
 public:
  /**
   * Creates a new CVTestCommand.
   *
   * @param subsystem The subsystem used by this command.
   */
  explicit CVTestCommand(CVSubsystem* subsystem);

 private:
  CVSubsystem* m_subsystem;
};
