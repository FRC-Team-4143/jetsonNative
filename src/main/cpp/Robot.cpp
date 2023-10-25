#include <iostream>

#include <frc/Joystick.h>
#include <frc/TimedRobot.h>
#include <frc/RobotController.h>
#include <frc/drive/DifferentialDrive.h>

#include <rev/CANSparkMax.h>

#include <ctre/phoenix6/TalonFX.hpp>
#include <ctre/Phoenix.h>

class Robot : public frc::TimedRobot {
  frc::Joystick m_stick{0};
  rev::CANSparkMax m_shooterMotor{1, rev::CANSparkMax::MotorType::kBrushless};
  WPI_TalonSRX talLeft{3};
  WPI_TalonSRX talRight{2};
  frc::DifferentialDrive m_drive{talLeft, talRight};

 public:
  void RobotInit() {
    talLeft.SetInverted(true); // if you want to invert motor outputs, you must do so here
  }

  void TeleopPeriodic() override {
    m_shooterMotor.Set(m_stick.GetZ());
    m_drive.ArcadeDrive(-m_stick.GetY(), -m_stick.GetX());
  }
};


#ifndef RUNNING_FRC_TESTS
int main() {
  return frc::StartRobot<Robot>();
}
#endif
