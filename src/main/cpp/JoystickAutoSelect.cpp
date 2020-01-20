#include "JoystickAutoSelect.h"

#include <frc/DriverStation.h>
#include <iostream>

JoystickAutoSelect::JoystickAutoSelect()
{
    if(frc::DriverStation::GetInstance().GetJoystickIsXbox(0))
    {
        m_joystickChoice = JoystickChoice::Xbox;
    }
    else
    {
        m_joystickChoice = JoystickChoice::Joysticks;
    }
}

double JoystickAutoSelect::GetY(frc::GenericHID::JoystickHand hand)
{
    if(m_joystickChoice == JoystickChoice::Joysticks)
    {
        return (hand == frc::GenericHID::kRightHand) ? m_right.GetY() : m_left.GetY(); 
    }
    else if(m_joystickChoice == JoystickChoice::Xbox)
    {
        return m_xbox.GetY(hand);
    }
    else
    {
        std::cout << "JoystickAutoSelect::GetY Warning: JoystickAutoSelect Choice in Unknown" << std::endl;
    }
    return 0;
}

double JoystickAutoSelect::GetX(frc::GenericHID::JoystickHand hand)
{
    if(m_joystickChoice == JoystickChoice::Joysticks)
    {
        return (hand == frc::GenericHID::kRightHand) ? m_right.GetX() : m_left.GetX(); 
    }
    else if(m_joystickChoice == JoystickChoice::Xbox)
    {
        return m_xbox.GetX(hand);
    }
    else
    {
        std::cout << "JoystickAutoSelect::GetX Warning: JoystickAutoSelect Choice in Unknown" << std::endl;
    }
    return 0;
}