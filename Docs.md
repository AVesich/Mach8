# Mach8 Docs

## Manual Control
### Driver Control Functions
``void mh8_tankDrive(int lStick, int rStick);

  void mh8_arcadeDrive(int xInput, int yInput);``

## Autonomous Control
### Straight Autonomous Functions
``void mh8_driveToTower(float maxPower, float curveTime, double sensitivity);

  void mh8_DriveStraight(double inches, char dir);``

### Turning Autonomous Functions
``void mh8_Turn(double deg, int maxSp, char dir);

  void mh8_Arc(double deg, char dir, char fwd);``

## Utility Functions
``void mh8_driveLeft(int spd);

   void mh8_driveRight(int spd);
   
   int mh8_getAvgDriveSideDeg(char side);
   
   void mh8_resetDrive();
   
   void mh8_setBrake(char mode);``
