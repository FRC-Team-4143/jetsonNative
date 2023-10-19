// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include <iostream>
//#include <dlfcn.h>
//#include <fmt/format.h>
#include <frc/Joystick.h>
#include <frc/TimedRobot.h>
#include <frc/RobotController.h>
#include <rev/CANSparkMax.h>
#include <rev/CANBridge.h>
//#include <frc/CAN.h>

#define Phoenix_No_WPI
#include <ctre/Phoenix.h>
#include <ctre/phoenix/unmanaged/Unmanaged.h>

/**
 * This is a demo program showing the use of the DifferentialDrive class.
 * Runs the motors with arcade steering.
 */
class Robot : public frc::TimedRobot {
  frc::Joystick m_stick{0};
  rev::CANSparkMax m_leftCanMotor{1, rev::CANSparkMax::MotorType::kBrushed};
  TalonFX talRight{1};

 public:
  void TeleopPeriodic() override {
    talRight.Set(ControlMode::PercentOutput, m_stick.GetY());
    m_leftCanMotor.Set(m_stick.GetX());
    ctre::phoenix::unmanaged::Unmanaged::FeedEnable(100);
  }

};


#ifndef RUNNING_FRC_TESTS
int main() {
  HAL_Initialize(500, 0);
  int32_t status;
  std::cout << "registering canbridge" << std::endl;
  auto handle = CANBridge_Scan();
  CANBridge_RegisterDeviceToHAL(CANBridge_GetDeviceDescriptor(handle, 0), 0, 0, &status);
  std::cout << "CANBridge_Register status: " << status << std::endl;
  return frc::StartRobot<Robot>();
}
#endif
