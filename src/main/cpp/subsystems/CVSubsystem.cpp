
#include <subsystems/CVSubsystem.h>

CVSubsystem::CVSubsystem() {

}

frc2::CommandPtr CVSubsystem::SubsystemStartup() {
    return RunOnce([] {});
}

bool CVSubsystem::ShouldRun() {
    return true;
}

void CVSubsystem::Periodic() {
    // do nothing, this is a purely autonomous system
}

void CVSubsystem::SimulationPeriodic() {
    m_visionProcessor->periodic();
}