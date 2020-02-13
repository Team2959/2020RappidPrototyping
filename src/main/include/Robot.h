/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#pragma once

#include <string>
#include <thread>
#include <tuple>
#include <chrono>

#include <frc/TimedRobot.h>
#include <frc/XboxController.h>

#include <frc/Spark.h>

#include "DriveSystem.h"
#include "conditioning.h"
#include "shooter.h"
#include "ColorWheel.h"
#include "JoystickAutoSelect.h"

class Robot : public frc::TimedRobot {
public:
  void RobotInit() override;
  void RobotPeriodic() override;
  void AutonomousInit() override;
  void AutonomousPeriodic() override;
  void TeleopInit() override;
  void TeleopPeriodic() override;
  void TestPeriodic() override;

 private:
  
  // JoystickAutoSelect m_controller;
  // DriveSystem m_DriveSystem;
  // Shooter m_shooter;

  // frc::Spark m_quick{0};

  // Color Sensor
  ColorWheel m_colorWheel;

  int m_skips = 0;

  cwtech::UniformConditioning m_uniformJoystick;

  std::thread m_poseThread;
  std::vector<std::tuple<int64_t, double, double>> m_pose;
  void PoseEstimator();
  void WritePoseToCSV();
  const std::string kCSVHeader = "Time,LeftVelocity,RightVelocity";
};
