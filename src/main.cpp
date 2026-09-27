#include "vex.h"
#include <array>

vex::brain Brain;

const int32_t leftMotorPort = vex::PORT1;
bool leftMotorReversed = false;
const int32_t rightMotorPort = vex::PORT2;
bool rightMotorReversed = false;

vex::gearSetting motorGearType = vex::ratio18_1;

vex::motor leftMotor(leftMotorPort, motorGearType, leftMotorReversed);
vex::motor rightMotor(rightMotorPort, motorGearType, rightMotorReversed);


enum terminalColourName
{
    black,
    red,
    green,
    yellow,
    blue,
    purple,
    cyan,
    white,
    orange,
    transparent,
    COUNT
};

struct terminalColourPallete
{
    std::array<const char*, terminalColourName::COUNT> data;

    const char* operator[](terminalColourName name) const
    {
        return data[static_cast<size_t>(name)];
    }
};

const terminalColourPallete terminalColours =
{
    "\033[30m",
    "\033[31m",
    "\033[32m",
    "\033[33m",
    "\033[34m",
    "\033[35m",
    "\033[36m",
    "\033[37m",
    "\033[91m",
    "\033[97m"
};


void clearTerminal()
{
    printf("\033[2J");
}

void setTerminalColour(const char* colour)
{
    printf("%s", colour);
}

void resetTerminalColour()
{
    printf("%s", terminalColours[terminalColourName::white]);
}

void motorInstallCheck(vex::motor& motor, const char* name, int32_t port)
{
    if(!motor.installed())
    {
        setTerminalColour(terminalColours[terminalColourName::red]);
        printf("%s is not installed!\n", name);
        printf("port: %ld\n", port);

        while(!motor.installed())
        {
            vex::wait(0.1, vex::seconds);
        }

        resetTerminalColour();
        clearTerminal();
    }
}

int main()
{
    motorInstallCheck(leftMotor, "left motor", leftMotorPort);
    motorInstallCheck(rightMotor, "right motor", rightMotorPort);

    clearTerminal();
    resetTerminalColour();    
    return 0;
}