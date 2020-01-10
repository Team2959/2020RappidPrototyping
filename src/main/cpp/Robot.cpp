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
  // use this line for both motors directly driving the shaft at opposite ends
  m_shooterFollower.Follow(m_shooterPrimary, true);
  // use this line if both in a gear box turning the same way
  //m_shooterFollower.Follow(m_shooterPrimary);

  // Color Sensor  
  m_colorMatcher.AddColorMatch(kBlueTarget);
  m_colorMatcher.AddColorMatch(kGreenTarget);
  m_colorMatcher.AddColorMatch(kRedTarget);
  m_colorMatcher.AddColorMatch(kYellowTarget);

  frc::SmartDashboard::PutNumber("Shooter: Target Velocity", 0);
  
  // This shows all PID values and Velocity
  ShowPIDAndVelocityValues();
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
    // Update Color Sensor Values
    UpdateColorSensorValues();
  }

  if(m_skips % 50 == 0)
  {
    UpdatePIDValues();
  }
}

void Robot::AutonomousInit() {}

void Robot::AutonomousPeriodic() {}

void Robot::TeleopInit() {}

void Robot::TeleopPeriodic() 
{
  m_DriveSystem.TankDrive(-m_controller.GetY(frc::GenericHID::JoystickHand::kLeftHand),
                         -m_controller.GetY(frc::GenericHID::JoystickHand::kRightHand));
  
  // Update Velocity on shooter
  UpdateVelocity();
}

void Robot::TestPeriodic() {}

void Robot::ShowPIDAndVelocityValues() 
{
  frc::SmartDashboard::PutNumber("Shooter: P Gain", m_shooterPID.GetP());
  frc::SmartDashboard::PutNumber("Shooter: I Gain", m_shooterPID.GetI());
  frc::SmartDashboard::PutNumber("Shooter: D Gain", m_shooterPID.GetD());
  frc::SmartDashboard::PutNumber("Shooter: I Zone", m_shooterPID.GetIZone());
  frc::SmartDashboard::PutNumber("Shooter: Feed Forward", m_shooterPID.GetFF());
  frc::SmartDashboard::PutNumber("Shooter: Ouput Min", m_shooterPID.GetOutputMin());
  frc::SmartDashboard::PutNumber("Shooter: Ouput Max", m_shooterPID.GetOutputMax());
  frc::SmartDashboard::PutNumber("Shooter: Velocity", m_shooterEncoder.GetVelocity());
}

void Robot::UpdatePIDValues()
{
  auto myP = frc::SmartDashboard::GetNumber("Shooter: P Gain", m_shooterPID.GetP());
  auto myI = frc::SmartDashboard::GetNumber("Shooter: I Gain", m_shooterPID.GetI());
  auto myD = frc::SmartDashboard::GetNumber("Shooter: D Gain", m_shooterPID.GetD());
  auto myIZone = frc::SmartDashboard::GetNumber("Shooter: I Zone", m_shooterPID.GetIZone());
  auto myFF = frc::SmartDashboard::GetNumber("Shooter: Feed Forward", m_shooterPID.GetFF());
  auto myOutputMin = frc::SmartDashboard::GetNumber("Shooter: Ouput Min", m_shooterPID.GetOutputMin());
  auto myOutputMax = frc::SmartDashboard::GetNumber("Shooter: Ouput Max", m_shooterPID.GetOutputMax());

  if(fabs(myP - m_shooterPID.GetP()) > kCloseToSameValue)
  {
    m_shooterPID.SetP(myP);
  }
  if(fabs(myI - m_shooterPID.GetI()) > kCloseToSameValue)
  {
    m_shooterPID.SetI(myI);
  }
  if(fabs(myD - m_shooterPID.GetD()) > kCloseToSameValue)
  {
    m_shooterPID.SetD(myD);
  }
  if(fabs(myIZone - m_shooterPID.GetIZone()) > kCloseToSameValue)
  {
    m_shooterPID.SetIZone(myIZone);
  }
  if(fabs(myFF - m_shooterPID.GetFF()) > kCloseToSameValue)
  {
    m_shooterPID.SetFF(myFF);
  }
  if(fabs(myOutputMin - m_shooterPID.GetOutputMin()) > kCloseToSameValue || 
    fabs(myOutputMax - m_shooterPID.GetOutputMax()) > kCloseToSameValue)
  {
    m_shooterPID.SetOutputRange(myOutputMin, myOutputMax);
  }
}

void Robot::UpdateVelocity()
{
  auto myVelocity = frc::SmartDashboard::GetNumber("Shooter: Target Velocity", 0);
  m_shooterPID.SetReference(myVelocity, rev::ControlType::kVelocity);
  frc::SmartDashboard::PutNumber("Shooter: Velocity", m_shooterEncoder.GetVelocity());
}

void Robot::UpdateColorSensorValues()
{
    frc::Color detectedColor = m_colorSensor.GetColor();
    std::string colorString;
    double confidence = 0.0;
    frc::Color matchedColor = m_colorMatcher.MatchClosestColor(detectedColor, confidence);

    if (matchedColor == kBlueTarget) {
      colorString = "Blue";
    } else if (matchedColor == kRedTarget) {
      colorString = "Red";
    } else if (matchedColor == kGreenTarget) {
      colorString = "Green";
    } else if (matchedColor == kYellowTarget) {
      colorString = "Yellow";
    } else {
      colorString = "Unknown";
    }

    frc::SmartDashboard::PutNumber("Red", detectedColor.red);
    frc::SmartDashboard::PutNumber("Green", detectedColor.green);
    frc::SmartDashboard::PutNumber("Blue", detectedColor.blue);
    frc::SmartDashboard::PutNumber("Confidence", confidence);
    frc::SmartDashboard::PutString("Detected Color", colorString);
    frc::SmartDashboard::PutNumber("Proximity", m_colorSensor.GetProximity());
}

#ifndef RUNNING_FRC_TESTS
int main() { return frc::StartRobot<Robot>(); }
#endif
