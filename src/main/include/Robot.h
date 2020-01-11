/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#pragma once

#include <string>

#include <frc/TimedRobot.h>
#include <frc/smartdashboard/SendableChooser.h>
#include <frc/Joystick.h>
#include <frc/XboxController.h>

#include <rev/CANSparkMax.h>

#include <frc/drive/DifferentialDrive.h>
#include <frc/SpeedControllerGroup.h>

#include <frc/util/color.h>
#include <rev/ColorSensorV3.h>
#include <rev/ColorMatch.h>

#include "DriveSystem.h"

#include "conditioning.h"

class Robot : public frc::TimedRobot {
 public:
  const double kCloseToSameValue = 0.0000001;
  void RobotInit() override;
  void RobotPeriodic() override;
  void AutonomousInit() override;
  void AutonomousPeriodic() override;
  void TeleopInit() override;
  void TeleopPeriodic() override;
  void TestPeriodic() override;

  void ShowPIDAndVelocityValues();
  void UpdatePIDValues();
  void UpdateVelocity();
  void UpdateColorSensorValues();

 private:
  frc::XboxController m_controller{0};

  DriveSystem m_DriveSystem{};

  //Shooter
  rev::CANSparkMax m_shooterPrimary{5, rev::CANSparkMaxLowLevel::MotorType::kBrushless};
  rev::CANSparkMax m_shooterFollower{6, rev::CANSparkMaxLowLevel::MotorType::kBrushless};
  rev::CANPIDController m_shooterPID {m_shooterPrimary};
  rev::CANEncoder m_shooterEncoder {m_shooterPrimary};

  // Color Sensor
  static constexpr auto i2cPort = frc::I2C::Port::kOnboard;
  static constexpr frc::Color kBlueTarget = frc::Color(0.143, 0.427, 0.429);
  static constexpr frc::Color kGreenTarget = frc::Color(0.197, 0.561, 0.240);
  static constexpr frc::Color kRedTarget = frc::Color(0.561, 0.232, 0.114);
  static constexpr frc::Color kYellowTarget = frc::Color(0.361, 0.524, 0.113);
  rev::ColorSensorV3 m_colorSensor{i2cPort};
  rev::ColorMatch m_colorMatcher;

  int m_skips = 0;

  cwtech::UniformConditioning m_uniformJoystick;
};
