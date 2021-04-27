#include "main.h"

// Basic control
void mh8_Drivetrain::mh8_driveLeft(int spd) {
  m_lFront.move(spd);
  m_lBack.move(spd);
}
void mh8_Drivetrain::mh8_driveRight(int spd) {
  m_rFront.move(spd);
  m_rBack.move(spd);
}

// DriveOp
void mh8_Drivetrain::mh8_tankDrive(int lStick, int rStick) {
  mh8_setBrake(M_BRAKE); // Set brake mode to coast

  mh8_driveLeft(lStick);
  mh8_driveRight(rStick);
}
void mh8_Drivetrain::mh8_arcadeDrive(int xInput, int yInput) {
  mh8_setBrake(M_BRAKE); // Set brake mode to coast

  mh8_driveLeft(yInput + xInput);
  mh8_driveRight(yInput - xInput);
}

// Sensor-based driving
void mh8_Drivetrain::mh8_driveToTower(float maxPower, float curveTime, double sensitivity){
  mh8_resetDrive();
  mh8_setBrake('b'); // Set brake mode, 0 is coast, 1 is brake, 2 is hold
  int lAvgTicks = 0;
  int rAvgTicks = 0;
  int avgTicks = 0;
  float currentPower = 0;
  float lPower = 0;
  float rPower = 0;
  float alignErr = 0;
  const float alignKp = 0; // Proportional constant used to keep robot straight.

  float lastTime = millis();
  float deltaTime = 0;          // Time between loop runs
  float total_Dt = 0;           // Total deltaTime
  float pctComplete = 0;        // Percent completion of the time

  float distToObj = towerDist.get();  // distance from tower
  const float deccelMM = 650.0;       // distance, in mm, from the tower where the bot should deccelerate

  auto atObj = objCheck.get() != errno && objCheck.get() < 125; // Sees tower at around 100 //towerDist.get() != errno && towerDist.get() < sensitivity;
  while( !atObj )
  {
    lAvgTicks = abs(getAvgDriveSideDeg('l'));
    rAvgTicks = abs(getAvgDriveSideDeg('r'));

    // Accel curve
    deltaTime = (millis()-lastTime);
    lastTime = millis();
    total_Dt += deltaTime;
    pctComplete = total_Dt/curveTime;
    currentPower = pctComplete*maxPower;

    if (currentPower <= 10) // Make sure the motor power is not 0
      currentPower = 10;

    //Decide which side is too far ahead, apply alignment and speed corretions.
    alignErr = 0;//abs((lAvgTicks - rAvgTicks)) * alignKp;
    if(lAvgTicks > rAvgTicks)
    {
      lPower = (currentPower) - alignErr;
      rPower = currentPower;
    }
    else if(rAvgTicks > lAvgTicks)
    {
      rPower = (currentPower) - alignErr;
      lPower = currentPower;
    }
    else
    {
      lPower = currentPower;
      rPower = currentPower;
    }

    // Deccel
    if (distToObj != errno && distToObj < deccelMM) {
      lPower *= distToObj/deccelMM;
      rPower *= distToObj/deccelMM;
    }

    if (lPower < 0 || rPower < 0) {
      lPower = 0;
      rPower = 0;
    }

    //Send velocity targets to both sides of the drivetrain.
    mh8_driveLeft(lPower);
    mh8_driveRight(rPower);

    /*
    cout << "left power: " << (m_lFront.get_actual_velocity()+m_lBack.get_actual_velocity())/2 << "        ";
    cout << "right power: " << (m_rFront.get_actual_velocity()+m_rBack.get_actual_velocity())/2 << endl;
    */

    atObj = objCheck.get() != errno && objCheck.get() < 125; // Update tower status
    distToObj = towerDist.get(); // update distance value

    delay(10); // Save brain resources
  }
  resetDrive();
  return;
}

// Normal inch-based funcs
void mh8_Drivetrain::mh8_DriveStraight(double inches, char dir) {
  mh8_resetDrive(); // Reset encoders
  mh8_setBrake('h'); // Brake mode hold

  const int wheelDiam = 4; // Should be set to the diameter of your drive wheels in inches.
  const double target = (inches / (wheelDiam * M_PI)) * 360 * STRIAGHTCONST; // Target is multiplied by .95 to get the desired distance when using speed carts

  const double maxSpStraight = 95;

  // Alignment variables
  double alignErr = 0.0;
  double alignKp = ALIGN;
  double lAvgTicks = 0;
  double rAvgTicks = 0;

  // Pid/speed variables
  double straightP = SKP;
  double straightI = SKI;
  double straightD = SKD;
  int power = 0;
  double lPower = 0.0;
  double rPower = 0.0;
  int error = 0;
  int prevError = 0;
  int integral = 0;
  int derivative = 0;
  int slewPower = 0;
  long escapeTime = millis(); // Get the time since the program started running (initial time)

  double absDriveDeg = ( abs(mh8_getAvgDriveSideDeg('r')) + abs(mh8_getAvgDriveSideDeg('l')) )/4; // gets the absolute value of all drive motor degrees

  while(millis() < escapeTime + 100){ // Escape time is when the bot should stop
    lAvgTicks = abs(mh8_getAvgDriveSideDeg('l'));
    rAvgTicks = abs(mh8_getAvgDriveSideDeg('r'));

    // PID for accel/deccel
    error = (target - absDriveDeg);
    integral += error * 0.1;
    if(error == 0 || abs(error) > 60)
      integral = 0;
    if(integral > 300)
      integral = 300;
    else if(integral < -300)
      integral = -300;
    derivative = error - prevError;
    power = (error * straightP) + (integral * straightI) + (derivative * straightD);
    if(power > slewPower){
      power = slewPower;
    }
    else if(power < -slewPower){
      power = -slewPower;
    }

    // Limit power ================
    // Too High
    if(power > maxSpStraight)
      power = maxSpStraight;
    else if(power < -maxSpStraight)
      power = -maxSpStraight;
    // Too Low
    /*if(power > 0 && power < 5)
      power = 10;
    else if(power < 0 && power > -5)
      power = -10;*/

    // Error adjustment between sides
    alignErr = abs(lAvgTicks - rAvgTicks) * alignKp;
    if(lAvgTicks > rAvgTicks)
    {
      lPower = power - alignErr;
      rPower = power;
    }
    else if(rAvgTicks > lAvgTicks)
    {
      rPower = power - alignErr;
      lPower = power;
    }
    else
    {
      lPower = power;
      rPower = power;
    }


    // Drive direction =============
    if (dir == 'b') { // Backward
      mh8_driveLeft(-lPower);
      mh8_driveRight(-rPower);
    } else { // Forward
      mh8_driveLeft(lPower);
      mh8_driveRight(rPower);
    }

    prevError = error; // Set the previous error to the error for this iteration
    absDriveDeg = ( abs(rAvgTicks) + abs(lAvgTicks) )/4; // update drive degrees

    if((absDriveDeg > target + 30) || (absDriveDeg < target -30)) // if the turn has over/undershot, allow time to fix it
      escapeTime = pros::millis();

    if(slewPower < 127){
      slewPower += 4;
    }

    delay(10);
  }
  mh8_resetDrive(); // Stop motors
}
void mh8_Drivetrain::mh8_Turn(double deg, int maxSp, char dir) {
  mh8_resetDrive(); // Reset encoders
  mh8_setBrake('h'); // Brake mode hold

  const double target = deg * TURNCONST;// Set the turn target // multiplying 90 by a factor of TURNCONST makes to bot turn exactly 90 degrees

  double turnP = TKP;
  double turnI = TKI;
  double turnD = TKD;
  int power = 0;
  int error = 0;
  int prevError = 0;
  int integral = 0;
  int derivative = 0;
  int slewPower = 0;
  long escapeTime = millis(); // Get the time since the program started running (initial time)

  double absDriveDeg = ( abs(mh8_getAvgDriveSideDeg('r')) + abs(mh8_getAvgDriveSideDeg('l')) )/4; // gets the absolute value of all drive motor degrees

  while(millis() < escapeTime + 100){ // Escape time is when the bot should stop,
    error = (target - absDriveDeg);
    integral += error * 0.1;
    if(error == 0 || abs(error) > 30)
      integral = 0;
    if(integral > 300)
      integral = 300;
    else if(integral < -300)
      integral = -300;
    derivative = error - prevError;
    power = (error * turnP) + (integral * turnI) + (derivative * turnD);
    if(power > slewPower){
      power = slewPower;
    }
    else if(power < -slewPower){
      power = -slewPower;
    }

    // Limit power ================
    if(power > maxSp)
      power = maxSp;
    else if(power < -maxSp)
      power = -maxSp;

    // Turn direction =============
    if (dir == 'r') { // Turn right
      mh8_driveLeft(power);
      mh8_driveRight(-power);
    } else { // Turn left
      mh8_driveLeft(-power);
      mh8_driveRight(power);
    }

    prevError = error; // Set the previous error to the error for this iteration
    absDriveDeg = ( abs(mh8_getAvgDriveSideDeg('r')) + abs(mh8_getAvgDriveSideDeg('l')) )/4; // update drive degrees

    if((absDriveDeg > target + 15) || (absDriveDeg < target -15)) // if the turn has overshot,
      escapeTime = pros::millis();

    if(slewPower < 130){
      slewPower += 4;
    }

    delay(10);
  }
  mh8_resetDrive(); // Stop motors
}
void mh8_Drivetrain::mh8_Arc(double deg, char dir, char fwd) {
  mh8_resetDrive(); // Reset encoders
  mh8_setBrake('h'); // Brake mode hold

  double target;

  if (dir == 'l') { // Get target for left
    target = deg * ARCCONSTL; // Set the turn target
  } else { // Get target for right
    target = deg * ARCCONSTR; // Set the turn target
  }

  const double maxSpArc = 60;

  double arcP = AKP;
  double arcI = AKI;
  double arcD = AKD;
  int power = 0;
  int error = 0;
  int prevError = 0;
  int integral = 0;
  int derivative = 0;
  int slewPower = 0;
  long escapeTime = millis(); // Get the time since the program started running (initial time)


  // Movingside is used to determine which side is moving and should have its values read
  char movingSide;
  if (dir == 'r')
    movingSide = 'l';
  else
    movingSide = 'r';

  double absDriveDeg = abs(mh8_getAvgDriveSideDeg(movingSide))/2; // gets the absolute value of all drive motor degrees

  while(millis() < escapeTime + 100){ // Escape time is when the bot should stop,
    error = (target - absDriveDeg);
    integral += error * 0.1;
    if(error == 0 || abs(error) > 30)
      integral = 0;
    if(integral > 300)
      integral = 300;
    else if(integral < -300)
      integral = -300;
    derivative = error - prevError;
    power = (error * arcP) + (integral * arcI) + (derivative * arcD);
    if(power > slewPower){
      power = slewPower;
    }
    else if(power < -slewPower){
      power = -slewPower;
    }

    // Limit power ================
    if(power > maxSpArc)
      power = maxSpArc;
    else if(power < -maxSpArc)
      power = -maxSpArc;

    // Flip forward/backward
    if (fwd == 'b')
      power = -power;

    // Turn direction =============
    if (dir == 'r') { // Turn right
      mh8_driveLeft(power);
      mh8_driveRight(0);
    } else { // Turn left
      mh8_driveLeft(0);
      mh8_driveRight(power);
    }

    prevError = error; // Set the previous error to the error for this iteration
    absDriveDeg = abs(mh8_getAvgDriveSideDeg(movingSide))/2; // update drive degrees

    if((absDriveDeg > target + 15) || (absDriveDeg < target -15)) // if the turn has overshot,
      escapeTime = pros::millis();

    if(slewPower < 130){
      slewPower += 4;
    }

    delay(10);
  }
  mh8_resetDrive(); // Stop motors
}

// Utility
int mh8_Drivetrain::mh8_getAvgDriveSideDeg(char side) {
  int avg = 0;

  if (side == 'l') {
    avg = (m_lFront.get_position() + m_lBack.get_position())/2;
  }
  else if (side == 'r') {
    avg = (m_rFront.get_position() + m_rBack.get_position())/2;
  }

  return avg;
}
void mh8_Drivetrain::mh8_resetDrive() {
  m_lFront.tare_position();
  m_lBack.tare_position();
  m_rFront.tare_position();
  m_rBack.tare_position();
  driveLeft(0);
  driveRight(0);
}
void mh8_Drivetrain::mh8_setBrake(char mode) {
  motor_brake_mode_e_t m_brakeMode;
  switch(mode){
    case 'c': case 'C':
      m_brakeMode = E_MOTOR_BRAKE_COAST;
      break;
    case 'b': case 'B':
      m_brakeMode = E_MOTOR_BRAKE_BRAKE;
      break;
    case 'h': case 'H':
      m_brakeMode = E_MOTOR_BRAKE_HOLD;
      break;
  }

  m_lFront.set_brake_mode(m_brakeMode);
  m_lBack.set_brake_mode(m_brakeMode);
  m_rFront.set_brake_mode(m_brakeMode);
  m_rBack.set_brake_mode(m_brakeMode);
}
