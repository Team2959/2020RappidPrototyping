/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#pragma once

#include <string>

#include <frc/TimedRobot.h>
#include <frc/XboxController.h>

#include <frc/util/Color.h>
#include <rev/ColorSensorV3.h>
#include <rev/ColorMatch.h>

#include "DriveSystem.h"
#include "conditioning.h"
#include "shooter.h"

class Robot : public frc::TimedRobot {
 public:
  void RobotInit() override;
  void RobotPeriodic() override;
  void AutonomousInit() override;
  void AutonomousPeriodic() override;
  void TeleopInit() override;
  void TeleopPeriodic() override;
  void TestPeriodic() override;

  void UpdateColorSensorValues();

 private:
  frc::XboxController m_controller{0};

  DriveSystem m_DriveSystem{};
  // Shooter m_shooter{};

  // // Color Sensor
  // static constexpr auto i2cPort = frc::I2C::Port::kOnboard;
  // static constexpr frc::Color kBlueTarget = frc::Color(0.143, 0.427, 0.429);
  // static constexpr frc::Color kGreenTarget = frc::Color(0.197, 0.561, 0.240);
  // static constexpr frc::Color kRedTarget = frc::Color(0.561, 0.232, 0.114);
  // static constexpr frc::Color kYellowTarget = frc::Color(0.361, 0.524, 0.113);
  // rev::ColorSensorV3 m_colorSensor{i2cPort};
  // rev::ColorMatch m_colorMatcher;

  int m_skips = 0;

  cwtech::UniformConditioning m_uniformJoystick;
};
