# Mach8 Docs

## Manual Control
### Driver Control Functions
mh8_tankDrive - tank drive (left & right joystick) control for your robot's drivetrain
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

mh8_arcadeDrive - arcade drive (x&y control with one joystick) for your robot's drivetrain
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

## Autonomous Control
### Straight Autonomous Functions
```c++
void mh8_driveToTower(float maxPower, float curveTime, double sensitivity);
void mh8_DriveStraight(double inches, char dir);
```

### Turning Autonomous Functions
```c++
void mh8_Turn(double deg, int maxSp, char dir);
void mh8_Arc(double deg, char dir, char fwd);
```

## Utility Functions
```c++
void mh8_driveLeft(int spd);
void mh8_driveRight(int spd);
int mh8_getAvgDriveSideDeg(char side);
void mh8_resetDrive();
void mh8_setBrake(char mode);
```
