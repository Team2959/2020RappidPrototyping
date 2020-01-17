/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

 #include "Robot.h"

 #include <iostream>

 #include <frc/smartdashboard/SmartDashboard.h>

 void Robot::RobotInit()
 {
//   // Color Sensor  
//   m_colorMatcher.AddColorMatch(kBlueTarget);
//   m_colorMatcher.AddColorMatch(kGreenTarget);
//   m_colorMatcher.AddColorMatch(kRedTarget);
//   m_colorMatcher.AddColorMatch(kYellowTarget);

  // m_shooter.Init();
  m_DriveSystem.ShowPIDGains();
}

/**
 * This function is called every robot packet, no matter the mode. Use
 * this for items like diagnostics that you want ran during disabled,
 * autonomous, teleoperated and test.
 *
 * <p> This runs after the mode specific periodic functions, but before
 * LiveWindow and SmartDashboard integrated updating.
 */
void Robot::RobotPeriodic() 
{
  m_skips++;

  if(m_skips % 5 == 0)
  {
    // UpdateColorSensorValues();
  }

  if(m_skips % 51 == 0)
  {
    // m_shooter.UpdatePIDValues();
  }

  if(m_skips % 49 == 0)
  {
    m_DriveSystem.UpdatePIDGains();
  }

}

void Robot::AutonomousInit() {}

void Robot::AutonomousPeriodic() {}

void Robot::TeleopInit() {}

void Robot::TeleopPeriodic() 
{
  m_DriveSystem.TankDrive(m_uniformJoystick.Condition(-m_controller.GetY(frc::GenericHID::JoystickHand::kLeftHand)) * DriveSystem::kMaxVelocity,
                         m_uniformJoystick.Condition(-m_controller.GetY(frc::GenericHID::JoystickHand::kRightHand)) * DriveSystem::kMaxVelocity);
  
  // m_shooter.UpdateVelocity();
  m_DriveSystem.ShowVelocity();
}

void Robot::TestPeriodic() {}

void Robot::UpdateColorSensorValues()
{
//     frc::Color detectedColor = m_colorSensor.GetColor();
//     std::string colorString;
//     double confidence = 0.0;
//     frc::Color matchedColor = m_colorMatcher.MatchClosestColor(detectedColor, confidence);

//     if (matchedColor == kBlueTarget) {
//       colorString = "Blue";
//     } else if (matchedColor == kRedTarget) {
//       colorString = "Red";
//     } else if (matchedColor == kGreenTarget) {
//       colorString = "Green";
//     } else if (matchedColor == kYellowTarget) {
//       colorString = "Yellow";
//     } else {
//       colorString = "Unknown";
//     }

//     frc::SmartDashboard::PutNumber("Red", detectedColor.red);
//     frc::SmartDashboard::PutNumber("Green", detectedColor.green);
//     frc::SmartDashboard::PutNumber("Blue", detectedColor.blue);
//     frc::SmartDashboard::PutNumber("Confidence", confidence);
//     frc::SmartDashboard::PutString("Detected Color", colorString);
//     frc::SmartDashboard::PutNumber("Proximity", m_colorSensor.GetProximity());
}

#ifndef RUNNING_FRC_TESTS
int main() { return frc::StartRobot<Robot>(); }
#endif
