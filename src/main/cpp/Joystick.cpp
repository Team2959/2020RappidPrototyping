#include "Joystick.h"

#include <frc/DriverStation.h>
#include <iostream>

Joystick::Joystick()
{
    if(frc::DriverStation::GetInstance().GetJoystickIsXbox(0))
    {
        m_joystickChoice = JoystickChoice::Xbox;
        m_xbox = frc::XboxController{0};
    }
    else
    {
        m_joystickChoice = JoystickChoice::Joysticks;
        m_left = frc::Joystick{0};
        m_right = frc::Joystick{1};
    }
}

double Joystick::GetY(frc::GenericHID::JoystickHand hand)
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
        std::cout << "Joystick::GetY Warning: Joystick Choice in Unknown" << std::endl;
    }
    return 0;
}

double Joystick::GetX(frc::GenericHID::JoystickHand hand)
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
        std::cout << "Joystick::GetX Warning: Joystick Choice in Unknown" << std::endl;
    }
    return 0;
}