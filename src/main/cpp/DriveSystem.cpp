#include "DriveSystem.h"

#include <frc/smartdashboard/SmartDashboard.h>

DriveSystem::DriveSystem()
{
    m_leftMotorFollower.Follow(m_leftMotorPrimary);
    m_leftMotorFollower2.Follow(m_leftMotorPrimary);
    m_rightMotorFollower.Follow(m_rightMotorPrimary);
    m_rightMotorFollower2.Follow(m_rightMotorPrimary);
    m_leftPID.SetFF(kFF);
    m_rightPID.SetFF(kFF);
}

void DriveSystem::TankDrive(double leftSpeed, double rightSpeed)
{
    m_leftPID.SetReference(leftSpeed, rev::ControlType::kVelocity);
    m_rightPID.SetReference(-rightSpeed, rev::ControlType::kVelocity);
}

void DriveSystem::ShowPIDGains()
{
    frc::SmartDashboard::PutNumber(kName + ": P Gain",  m_leftPID.GetP());
    frc::SmartDashboard::PutNumber(kName + ": I Gain", m_leftPID.GetI());
    // frc::SmartDashboard::PutNumber(kName + ": D Gain", m_leftPID.GetD());
    frc::SmartDashboard::PutNumber(kName + ": Feed Forward", m_leftPID.GetFF());
    frc::SmartDashboard::PutNumber(kName + ": I Zone", m_leftPID.GetIZone());
}

void DriveSystem::UpdatePIDGains()
{
    auto currentP = m_leftPID.GetP();
    auto currentI = m_leftPID.GetI();
    // auto currentD = m_leftPID.GetD();
    auto currentFF = m_leftPID.GetFF();
    auto currentIZone = m_leftPID.GetIZone();

    auto myP = frc::SmartDashboard::GetNumber(kName + ": P Gain", currentP);
    auto myI = frc::SmartDashboard::GetNumber(kName + ": I Gain", currentI);
    // auto myD = frc::SmartDashboard::GetNumber(kName + ": D Gain", currentD);
    auto myFF = frc::SmartDashboard::GetNumber(kName + ": Feed Forward", currentFF);
    auto myIZone = frc::SmartDashboard::GetNumber(kName + ": I Zone", currentIZone);
    if(fabs(myP - currentP) > kCloseToSameValue)
    {
        m_rightPID.SetP(myP);
        m_leftPID.SetP(myP);
    }
    if(fabs(myI - currentI) > kCloseToSameValue)
    {
        m_rightPID.SetI(myI);
        m_leftPID.SetI(myI);
    }
    // if(fabs(myD - currentD) > kCloseToSameValue)
    // {
    //     m_rightPID.SetD(myD);
    //     m_leftPID.SetD(myD);
    // }
    if(fabs(myFF - currentFF) > kCloseToSameValue)
    {
        m_rightPID.SetFF(myFF);
        m_leftPID.SetFF(myFF);
    }
    if(fabs(myIZone - currentIZone) > kCloseToSameValue)
    {
        m_rightPID.SetIZone(myIZone);
        m_leftPID.SetIZone(myIZone);
    }
}

void DriveSystem::ShowVelocity()
{
    frc::SmartDashboard::PutNumber(kName + ": Right Velocity", m_rightEncoder.GetVelocity());
    frc::SmartDashboard::PutNumber(kName + ": Right Position", m_rightEncoder.GetPosition());
    frc::SmartDashboard::PutNumber(kName + ": Right Output", m_rightMotorPrimary.GetAppliedOutput());
    frc::SmartDashboard::PutNumber(kName + ": Right Output Current", m_rightMotorPrimary.GetOutputCurrent());

    frc::SmartDashboard::PutNumber(kName + ": Left Velocity", m_leftEncoder.GetVelocity());
    frc::SmartDashboard::PutNumber(kName + ": Left Position", m_leftEncoder.GetPosition());
    frc::SmartDashboard::PutNumber(kName + ": Left Output", m_leftMotorPrimary.GetAppliedOutput());
    frc::SmartDashboard::PutNumber(kName + ": Left Current", m_leftMotorPrimary.GetOutputCurrent());
}