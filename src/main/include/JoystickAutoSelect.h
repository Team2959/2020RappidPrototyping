#pragma once

#include <frc/Joystick.h>
#include <frc/XboxController.h>

class JoystickAutoSelect
{
public:
    JoystickAutoSelect();
    double GetX(frc::GenericHID::JoystickHand hand);
    double GetY(frc::GenericHID::JoystickHand hand);
    
private:
    enum class JoystickChoice
    {
        Xbox,
        Joysticks,
        Unknown,
    };

    JoystickChoice m_joystickChoice;
    frc::XboxController m_xbox{0};
    frc::Joystick m_left{0};
    frc::Joystick m_right{1};
};
