#pragma once

#include <rev/CANSparkMax.h>
#include <string>

class DriveSystem
{
private:
  const double kCloseToSameValue = 0.0000001;
  
  rev::CANSparkMax m_rightMotorPrimary{1, rev::CANSparkMaxLowLevel::MotorType::kBrushless};
  rev::CANSparkMax m_rightMotorFollower{2, rev::CANSparkMaxLowLevel::MotorType::kBrushless};
  rev::CANSparkMax m_leftMotorPrimary{3, rev::CANSparkMaxLowLevel::MotorType::kBrushless};
  rev::CANSparkMax m_leftMotorFollower{4, rev::CANSparkMaxLowLevel::MotorType::kBrushless};
  rev::CANPIDController m_rightPID{m_rightMotorPrimary};
  rev::CANPIDController m_leftPID{m_leftMotorPrimary};
  rev::CANEncoder m_rightEncoder{m_rightMotorPrimary};
  rev::CANEncoder m_leftEncoder{m_leftMotorPrimary};

  const std::string kName = "DriveSystem";
  const double kFF = 0.0005;
public:
  constexpr static double kMaxVelocity = 5500;
  // Init happens here
  DriveSystem();

  void TankDrive(double leftSpeed, double rightSpeed);

  void ShowPIDGains();
  void UpdatePIDGains();
  void ShowVelocity(); // And Output and Current
};
