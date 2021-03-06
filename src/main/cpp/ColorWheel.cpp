#include "ColorWheel.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <fcntl.h>
#include <sstream>
#include <sys/stat.h>
#include <frc/smartdashboard/SmartDashboard.h>
#include <frc/DriverStation.h>

inline bool exists (const std::string& filename)
{
    struct stat buffer;   
    return (stat (filename.c_str(), &buffer) == 0); 
}

void ColorWheel::OnRobotInit()
{
    m_colorSensor.ConfigureColorSensor(
        rev::ColorSensorV3::ColorResolution::k16bit,
        rev::ColorSensorV3::ColorMeasurementRate::k25ms);

    m_colorMatcher.AddColorMatch(kBlueTarget);
    m_colorMatcher.AddColorMatch(kGreenTarget);
    m_colorMatcher.AddColorMatch(kRedTarget);
    m_colorMatcher.AddColorMatch(kYellowTarget);
    m_colorMatcher.AddColorMatch(kBlueGreenTarget);
    m_colorMatcher.AddColorMatch(kBlueYellowTarget);
    m_colorMatcher.AddColorMatch(kGreenRedTarget);
    m_colorMatcher.AddColorMatch(kRedYellowTarget);

    frc::SmartDashboard::PutBoolean("Count Color", false);
    frc::SmartDashboard::PutNumber("Color Counted", 0);
    frc::SmartDashboard::PutBoolean("Log Color", false);
    frc::SmartDashboard::PutString("Color to Count", ColorName(m_countedColor));

    if (exists("/home/lvuser/colors.csv"))
    {
        remove("/home/lvuser/colors.csv");
    }
}

void ColorWheel::UpdateColorSensorValues(int skips)
{
    frc::Color detectedColor = m_colorSensor.GetColor();
    double confidence = 0.0;
    frc::Color matchedColor = m_colorMatcher.MatchClosestColor(detectedColor, confidence);

    if (m_countColors)
    {
        if (m_logColors)
        {
            // tracking colors
            m_colorTracking.push_back(std::tuple<std::string,double,double,double>(
                ColorName(matchedColor),
                detectedColor.red,
                detectedColor.green,
                detectedColor.blue
            ));
        }

        if (m_lastColor == m_countedColor && !(m_lastColor == matchedColor))
        {
            m_colorCount++;
        }
        m_lastColor = matchedColor;
    }

    // when counting is disabled reset counter
    if (!m_countColors)
    {
        m_colorCount = 0;
        m_lastColor = kBlack;

        if (m_colorTracking.size() > 0)
        {
            bool headerNotThere = !exists("/home/lvuser/colors.csv");
            std::fstream stream;
            stream.open("/home/lvuser/colors.csv", std::fstream::app | std::fstream::out | std::fstream::in);
            if (stream.is_open())
            {
                std::cout << "stream failed to open" << std::endl;
            }
            stream << "\n";
            stream << "\n";
            stream << "\n";
            if (headerNotThere)
            {
                stream << "Guess,Red,Green,Blue\n";
            }

            for (auto& item : m_colorTracking)
            {
                std::string guess = std::get<0>(item);
                double red = std::get<1>(item);
                double green = std::get<2>(item);
                double blue = std::get<3>(item);
                stream << guess << ',' <<
                    std::to_string(red) << ',' <<
                    std::to_string(green) << ',' <<
                    std::to_string(blue) << "\n";
            }
            stream.close();
            m_colorTracking.clear();
        }
    }

    if (skips % 50 == 0)
    {
        frc::SmartDashboard::PutNumber("Color Counted", m_colorCount);
        m_countColors = frc::SmartDashboard::GetBoolean("Count Color", false);
        m_logColors = frc::SmartDashboard::GetBoolean("Log Colors", false);
        m_countedColor = GetColorFromName(
            frc::SmartDashboard::GetString("Color to Count", ColorName(m_countedColor)));

        frc::SmartDashboard::PutNumber("Red", detectedColor.red);
        frc::SmartDashboard::PutNumber("Green", detectedColor.green);
        frc::SmartDashboard::PutNumber("Blue", detectedColor.blue);
        frc::SmartDashboard::PutNumber("Confidence", confidence);
        frc::SmartDashboard::PutString("Detected Color", ColorName(matchedColor));
        // frc::SmartDashboard::PutNumber("Proximity", m_colorSensor.GetProximity());
    }
}

void ColorWheel::SetTargetColorFromGameData()
{
    m_gameDataTargetColor = GetColorFromName(frc::DriverStation::GetInstance().GetGameSpecificMessage());
    frc::SmartDashboard::PutString("Game Data Color", ColorName(m_gameDataTargetColor));
}

std::string ColorWheel::ColorName(frc::Color matchedColor)
{
    if (matchedColor == kBlueTarget)
        return "Blue";
    if (matchedColor == kGreenTarget)
        return "Green";
    if (matchedColor == kRedTarget)
        return "Red";
    if (matchedColor == kYellowTarget)
        return "Yellow";
    if (matchedColor == kBlueGreenTarget)
        return "Green/Blue";
    if (matchedColor == kBlueYellowTarget)
        return "Blue/Yellow";
    if (matchedColor == kGreenRedTarget)
        return "Red/Green";
    if (matchedColor == kRedYellowTarget)
        return "Yellow/Red";
    if (matchedColor == kBlack)
        return "Black";

    return "Unknown";
}

frc::Color ColorWheel::GetColorFromName(std::string colorName)
{
    if(colorName.length() > 0)
    {
        switch (toupper(colorName[0]))
        {
        case 'B':
            return kBlueTarget;
        case 'G':
            return kGreenTarget;
        case 'R':
            return kRedTarget;
        case 'Y':
            return kYellowTarget;
        }
    }

    return kBlack;
}
