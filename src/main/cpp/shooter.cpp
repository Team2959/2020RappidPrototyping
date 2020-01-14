#include "shooter.h"
#include <frc/smartdashboard/SmartDashboard.h>

Shooter::Shooter()
{
    // use this line for both motors directly driving the shaft at opposite ends
    m_shooterFollower.Follow(m_shooterPrimary, true);
    // use this line if both in a gear box turning the same way
    // m_shooterFollower.Follow(m_shooterPrimary);

    m_shooterPID.SetP(0.002);
    m_shooterPID.SetFF(0.000193);
}

void Shooter::Init()
{
    ShowPIDAndVelocityValues();
}

void Shooter::ShowPIDAndVelocityValues() 
{
    frc::SmartDashboard::PutNumber("Shooter: P Gain", m_shooterPID.GetP());
    frc::SmartDashboard::PutNumber("Shooter: I Gain", m_shooterPID.GetI());
    // frc::SmartDashboard::PutNumber("Shooter: D Gain", m_shooterPID.GetD());
    frc::SmartDashboard::PutNumber("Shooter: I Zone", m_shooterPID.GetIZone());
    frc::SmartDashboard::PutNumber("Shooter: Feed Forward", m_shooterPID.GetFF());
    // frc::SmartDashboard::PutNumber("Shooter: Ouput Min", m_shooterPID.GetOutputMin());
    // frc::SmartDashboard::PutNumber("Shooter: Ouput Max", m_shooterPID.GetOutputMax());
    frc::SmartDashboard::PutNumber("Shooter: Velocity", m_shooterEncoder.GetVelocity());
    frc::SmartDashboard::PutNumber("Shooter: Output", m_shooterPrimary.GetAppliedOutput());
    frc::SmartDashboard::PutNumber("Shooter: Current", m_shooterPrimary.GetOutputCurrent());
    frc::SmartDashboard::PutNumber("Shooter: Current Follower", m_shooterFollower.GetOutputCurrent());
    frc::SmartDashboard::PutNumber("Shooter: Temp", m_shooterPrimary.GetMotorTemperature());
    frc::SmartDashboard::PutNumber("Shooter: Target Velocity", 0);
}

void Shooter::UpdatePIDValues()
{
    auto currentP = m_shooterPID.GetP();
    auto currentI = m_shooterPID.GetI();
    // auto currentD = m_shooterPID.GetD();
    auto currentFF = m_shooterPID.GetFF();
    auto currentIZone = m_shooterPID.GetIZone();

    auto myP = frc::SmartDashboard::GetNumber("Shooter: P Gain", currentP);
    auto myI = frc::SmartDashboard::GetNumber("Shooter: I Gain", currentI);
    // auto myD = frc::SmartDashboard::GetNumber("Shooter: D Gain", currentD);
    auto myIZone = frc::SmartDashboard::GetNumber("Shooter: I Zone", currentIZone);
    auto myFF = frc::SmartDashboard::GetNumber("Shooter: Feed Forward", currentFF);
    // auto myOutputMin = frc::SmartDashboard::GetNumber("Shooter: Ouput Min", m_shooterPID.GetOutputMin());
    // auto myOutputMax = frc::SmartDashboard::GetNumber("Shooter: Ouput Max", m_shooterPID.GetOutputMax());

    if(fabs(myP - currentP) > kCloseToSameValue)
    {
        m_shooterPID.SetP(myP);
    }
    if(fabs(myI - currentI) > kCloseToSameValue)
    {
        m_shooterPID.SetI(myI);
    }
    // if(fabs(myD - currentD) > kCloseToSameValue)
    // {
    //   m_shooterPID.SetD(myD);
    // }
    if(fabs(myIZone - currentIZone) > kCloseToSameValue)
    {
        m_shooterPID.SetIZone(myIZone);
    }
    if(fabs(myFF - currentFF) > kCloseToSameValue)
    {
        m_shooterPID.SetFF(myFF);
    }
    /*
    if(fabs(myOutputMin - m_shooterPID.GetOutputMin()) > kCloseToSameValue || 
    fabs(myOutputMax - m_shooterPID.GetOutputMax()) > kCloseToSameValue)
    {
    m_shooterPID.SetOutputRange(myOutputMin, myOutputMax);
    }
    */
}

void Shooter::UpdateVelocity()
{
    auto myVelocity = frc::SmartDashboard::GetNumber("Shooter: Target Velocity", 0);
    m_shooterPID.SetReference(myVelocity, rev::ControlType::kVelocity);
    frc::SmartDashboard::PutNumber("Shooter: Velocity", m_shooterEncoder.GetVelocity());
    frc::SmartDashboard::PutNumber("Shooter: Output", m_shooterPrimary.GetAppliedOutput());
    frc::SmartDashboard::PutNumber("Shooter: Current", m_shooterPrimary.GetOutputCurrent());
    frc::SmartDashboard::PutNumber("Shooter: Temp", m_shooterPrimary.GetMotorTemperature());
}
