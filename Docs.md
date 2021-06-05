# Mach8 Docs

## Manual Control
### Driver Control Functions
mh8_tankDrive: tank drive (left & right joystick) control for your robot's drivetrain
```c++
void mh8_tankDrive(int lStick, int rStick);
```
Example: 
```c++
void opcontrol() {
   while (true){
      m_Drivetrain.mh8_tankDrive(controller.get_analog(ANALOG_LEFT_Y), controller.get_analog(ANALOG_RIGHT_Y));
      
      delay(10);
   }
}
```
\
mh8_arcadeDrive: arcade drive (x&y control with one joystick) for your robot's drivetrain
```c++
void mh8_arcadeDrive(int xInput, int yInput);
```
Example:
```c++
void opcontrol() {
   while (true){
      m_Drivetrain.mh8_arcadeDrive(controller.get_analog(ANALOG_LEFT_X), controller.get_analog(ANALOG_LEFT_Y));
      
      delay(10);
   }
}
```
\

## Autonomous Control
### Straight Autonomous Functions
mh8_driveToTower: distance sensor based driving that accelerates over an adjustable period of time
```c++
void mh8_driveToTower(float maxPower, float curveTime, double sensitivity);
```
Example:
```c++
void auto1() {
   mh8_Drivetrain.mh8_driveToTower(95, 150, 45); // Max rpm will be 95, The robot will accelerate over 150 ms, The robot will stop moving 45mm from an object
}
```
\
mh8_DriveStraight: degree based straight driving that accelerates/decelerates using PID
```c++
void mh8_DriveStraight(double inches, char dir);
```
Example:
```c++
void auto1() {
   mh8_Drivetrain.mh8_DriveStraight(24, 'f'); // The robot will drive forward 24 inches in the forward direction
}
```
\

### Turning Autonomous Functions
mh8_Turn: degree based turning that accelerates/decelerates using PID
```c++
void mh8_Turn(double deg, int maxSp, char dir);
```
Example:
```c++
void auto1() {
   mh8_Drivetrain.mh8_Turn(90, 80, 'r'); // The robot will turn 90 degrees to the right with a maximum speed of 80
}
```
\
mh8_Turn: degree based arc movements that accelerate/decelerate using PID
```c++
void mh8_Arc(double deg, char dir, char fwd);
```
Example:
```c++
void auto1() {
   mh8_Drivetrain.mh8_Arc(90, 'r', 'f'); // The robot will follow a right arc path for 90 degrees in the forward direction
}
```
\
## Utility Functions
```c++
void mh8_driveLeft(int spd);
void mh8_driveRight(int spd);
int mh8_getAvgDriveSideDeg(char side);
void mh8_resetDrive();
void mh8_setBrake(char mode);
```
mh8_driveLeft: percent based drive for the left side of the drivetrain
```c++
void mh8_driveLeft(int spd);
```
Example:
```c++
void auto1() {
   mh8_Drivetrain.mh8_driveLeft(100); // The robot will move its left drive side at 100 percent power
}
```
\
mh8_driveRight: percent based drive for the right side of the drivetrain
```c++
void mh8_driveRight(int spd);
```
Example:
```c++
void auto1() {
   mh8_Drivetrain.mh8_driveRight(100); // The robot will move its right drive side at 100 percent power
}
```
\
mh8_getAvgDriveSideDeg: returns the average number of encoder ticks on the desired drivetrain side
```c++
void mh8_getAvgDriveSideDeg(char side);
```
Example:
```c++
void auto1() {
   cout << mh8_getAvgDriveSideDeg('r'); // Outputs the average encoder ticks of the right side of the drivetrain to the pros console
}
```
\
mh8_resetDrive: resets the encoders for all 4 drive motors (built into autonomous drive functions)
```c++
void mh8_resetDrive();
```
Example:
```c++
void auto1() {
   mh8_resetDrive(); // resets the drive encoders before an autonomous movement
}
```
\
mh8_setBrake: sets the brake mode for all 4 drive motors
```c++
void mh8_setBrake(char mode);
```
Example:
```c++
void auto1() {
   mh8_setBrake('h'); // sets the drive motor's brake mode to hold
}
```
