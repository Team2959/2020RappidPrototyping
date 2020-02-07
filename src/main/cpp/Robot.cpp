/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "Robot.h"

#include <iostream>

#include <frc/smartdashboard/SmartDashboard.h>

#include <fstream>
#include <sstream>
#include <experimental/filesystem>
#include <fcntl.h>
#include <ctime>

#include <hal/cpp/fpga_clock.h>

void Robot::RobotInit()
{
  //  m_poseThread = std::thread(&Robot::PoseEstimator, this);
  // Color Sensor  
  m_colorMatcher.AddColorMatch(kBlueTarget);
  m_colorMatcher.AddColorMatch(kGreenTarget);
  m_colorMatcher.AddColorMatch(kRedTarget);
  m_colorMatcher.AddColorMatch(kYellowTarget);
  // m_colorSensor.ConfigureColorSensor(rev::ColorSensorV3::ColorResolution::k20bit, rev::ColorSensorV3::ColorMeasurementRate::k25ms);
  frc::SmartDashboard::PutBoolean("Count Color", false);
  frc::SmartDashboard::PutNumber("Color Counted", 0);

  // m_shooter.Init();
  // m_DriveSystem.ShowPIDGains();
  // m_uniformJoystick.SetDeadband(0.05);
  // m_uniformJoystick.SetExponent(5);
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

  // if(m_skips % 5 == 0)
  {
    UpdateColorSensorValues();
  }

  if(m_skips % 51 == 0)
  {
    // m_shooter.UpdatePIDValues();
  }

  if(m_skips % 49 == 0)
  {
    // m_DriveSystem.UpdatePIDGains();
  }

}

void Robot::AutonomousInit() {}

void Robot::AutonomousPeriodic() {}

void Robot::TeleopInit() 
{
}

void Robot::TeleopPeriodic() 
{
  // m_DriveSystem.TankDrive(m_uniformJoystick.Condition(-m_controller.GetY(frc::GenericHID::JoystickHand::kLeftHand))/* * DriveSystem::kMaxVelocity*/,
                        //  m_uniformJoystick.Condition(-m_controller.GetY(frc::GenericHID::JoystickHand::kRightHand))/* * DriveSystem::kMaxVelocity*/);
  
  // m_quick.Set(m_controller.GetRightThrottle());

  // m_shooter.UpdateVelocity();
  // m_DriveSystem.ShowVelocity();
}

void Robot::TestPeriodic() {}

void Robot::UpdateColorSensorValues()
{
    frc::Color detectedColor = m_colorSensor.GetColor();
    std::string colorString;
    double confidence = 0.0;
    frc::Color matchedColor = m_colorMatcher.MatchClosestColor(detectedColor, confidence);

    if (m_countColors && !(m_lastColor == matchedColor))
    {
      m_lastColor = matchedColor;
      if(m_lastColor == kCountedColor)
      {
        m_colorCount++;
      }
    }

// when counting is disabled reset counter
    if(!m_countColors)
    {
      m_colorCount = 0;
      m_lastColor = frc::Color(0,0,0);
    }

  if(m_skips % 50 == 0)
  {
    frc::SmartDashboard::PutNumber("Color Counted", m_colorCount);
    m_countColors = frc::SmartDashboard::GetBoolean("Count Color", false);
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
}

void Robot::PoseEstimator () {
  // while (true) {
  //   // Calculater the robot pose
  //   int64_t time = std::chrono::duration_cast<std::chrono::milliseconds>(hal::fpga_clock::now().time_since_epoch()).count();
  //   m_pose.push_back(std::make_tuple(time, m_DriveSystem.GetLeftVelocity(), m_DriveSystem.GetRightVelocity()));
  //   if(m_pose.size() >= 100) WritePoseToCSV();
  //   std::this_thread::sleep_for(std::chrono::duration<int, std::milli>(10));
  // }
}

void Robot::WritePoseToCSV()
{
  bool header = false;
  if(!std::ifstream{"/home/lvuser/pose.csv"}.good())
  {
    header = true;
  }
  std::fstream stream;
  // /home/lvuser was recomended here: https://www.chiefdelphi.com/t/text-files-on-the-roborio/141334/3
  stream.open("/home/lvuser/pose.csv", std::fstream::app | std::fstream::out | std::fstream::in);
  if(!stream.is_open())
  {
    frc::SmartDashboard::PutString("DEBUG", "Stream failed to open");
    return; 
  }
  #define write(x) stream << x << "\n"
  if(header) write(kCSVHeader);
  for(auto& tuple : m_pose)
  {
    int64_t time = std::get<0>(tuple);
    double left = std::get<1>(tuple);
    double right = std::get<2>(tuple);
    // usage of std::tie found here: https://en.cppreference.com/w/cpp/utility/tuple/tie
    write(std::to_string(time) + "," + std::to_string(left) + "," + std::to_string(right));
  }
  stream.close();
  #undef write
  m_pose.clear();
}

#ifndef RUNNING_FRC_TESTS
int main() { return frc::StartRobot<Robot>(); }
#endif
