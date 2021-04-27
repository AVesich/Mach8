# Mach8
An object-oriented drive function library to make Vex c++ programming in PROS faster and easier

# Notes:
- The core functions are sourced from retired Vex team 491A.
- These functions were further adapted to the object oriented format by 1233A during their 2020-2021 season.

# How to use:
- First, download the files and drag the "Mach8Src" and "Mach8Inc" folders into the Src and Include folders (respectively) for your pros project.
- Second, edit the "Config.h" file in the Mach8Inc folder and convigure the port numbers & reversal variables for all of the drive motors (lines 13-23)
- Third, Imu and Distance sensor ports as well as the brake mode for driver control can be configured (Imu and distance sensors are currently not supported)
- Forth, add the following lines to your main.h file in order to access all of mach8's functions, sensors, and variables
```#include "Mach8Inc/Api.h"
using namespace mh8_Drive;
using namespace mh8_Variables;
using namespace mh8_Sensors;

extern mh8_Drivetrain <Drivetrain Name>;
```
- Lastly, declare your drivetrain in a c++ file of your choice like this: ```mh8_Drivetrain <Drivetrain Name>;```

# Using mach8
To begin using mach8 type your drivetrain's name and access any of the functions by typing ".<Function Name>" after it.
  Example: ```m_driveTrain.mh8_arcadeDrive(master.get_analog(ANALOG_LEFT_X), master.get_analog(ANALOG_LEFT_Y));```
