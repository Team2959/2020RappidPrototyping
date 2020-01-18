#pragma once

#include <frc/Joystick.h>
#include <frc/XboxController.h>

class Joystick
{
public:
    enum class JoystickChoice
    {
        Xbox,
        Joysticks,
        Unknown,
    };
    Joystick();
    double GetX(frc::GenericHID::JoystickHand hand);
    double GetY(frc::GenericHID::JoystickHand hand);
    
private:
    JoystickChoice m_joystickChoice;
    frc::XboxController m_xbox{0};
    frc::Joystick m_left{1};
    frc::Joystick m_right{2};
    int m_xboxPort, m_leftJoystickPort, m_rightJoystickPort;
};
