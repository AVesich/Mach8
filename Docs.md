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
