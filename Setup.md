# Mach8
An object-oriented drive function library to make Vex c++ programming in PROS faster and easier

# Notes:
- The core functions are sourced from retired Vex team 491A.
- Distance sensor logic and acceleration/deceleration was developed for mach8 by 1233A.
- PID straight alignment was developed by 1233F.
- These functions were further adapted to the object oriented format by 1233A during their 2020-2021 season.

# How to use:
- First, download the files and drag the "Mach8Src" and "Mach8Inc" folders into the Src and Include folders (respectively) for your pros project.
- Second, edit the "Config.h" file in the Mach8Inc folder and convigure the port numbers & reversal variables for all of the drive motors (lines 13-23)
- Third, Imu and Distance sensor ports as well as the brake mode for driver control can be configured (Imu and distance sensors are currently not supported)
- Forth, add the following lines to your main.h file in order to access all of mach8's functions, sensors, and variables
```c++
#include "Mach8Inc/Api.h"
using namespace mh8_Drive;
using namespace mh8_Variables;
using namespace mh8_Sensors;

extern mh8_Drivetrain <Drivetrain Name>;
```
- Lastly, declare your drivetrain in a c++ file of your choice like this: ```c++ mh8_Drivetrain <Drivetrain Name>;```

# Using mach8
To begin using mach8 type your drivetrain's name and access any of the functions by typing ".<Function Name>" after it.

Example: ```c++ m_driveTrain.mh8_arcadeDrive(master.get_analog(ANALOG_LEFT_X), master.get_analog(ANALOG_LEFT_Y));```

# Tuning PID
You will most likely need to tune the various PID constants withing mach8's "Config.h" file, since every gear ratio will change the rotation of a robot's wheel.
- I personally recommend running one autonomous function at a time (mh8_driveStraight, mh8_turn, etc.) and tuning the distance constants until you see a consistent drive distance (90 degree input makes the robot turn 90 degrees, 24 inch input makes it drive 24 inches, etc.)
- The "ALIGN" variable should be tweaked until driving straight does not visibly oscillate
- The P variable should be increased/decreased for each drive mode until acceleration is quick and smooth, but not to an extent that the robot wheelies when it comes to a stop.
- I recommend not tuning the I variable
- The D variable should be increased/decreased until the robot comes to a desireably smooth stop and does not oscillate or jump forwards/backwards after reaching its target.
