#pragma once

#include <rev/CANSparkMax.h>

class Shooter
{
private:
    const double kCloseToSameValue = 0.0000001;
    rev::CANSparkMax m_shooterPrimary{5, rev::CANSparkMaxLowLevel::MotorType::kBrushless};
    rev::CANSparkMax m_shooterFollower{6, rev::CANSparkMaxLowLevel::MotorType::kBrushless};
    rev::CANPIDController m_shooterPID {m_shooterPrimary};
    rev::CANEncoder m_shooterEncoder {m_shooterPrimary};

    void ShowPIDAndVelocityValues();

public:
    Shooter();

    void Init();

    void UpdatePIDValues();
    void UpdateVelocity();
};
