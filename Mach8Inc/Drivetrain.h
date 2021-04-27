#ifndef DRIVETRAIN_H
#define DRIVETRAIN_H

#include "pros/motors.hpp"
#include "Mach8Inc/Config.h"
using namespace pros;

namespace mh8_Drive {
  class mh8_Drivetrain {
    // Motor declarations
    Motor m_lFront = Motor(M_LFRONT, E_MOTOR_GEARSET_18, M_LFRONT_REV, E_MOTOR_ENCODER_DEGREES);;
    Motor m_lBack = Motor(M_LBACK, E_MOTOR_GEARSET_18, M_LBACK_REV, E_MOTOR_ENCODER_DEGREES);
    Motor m_rFront = Motor(M_RFRONT, E_MOTOR_GEARSET_18, M_RFRONT_REV, E_MOTOR_ENCODER_DEGREES);
    Motor m_rBack = Motor(M_RBACK, E_MOTOR_GEARSET_18, M_RBACK_REV, E_MOTOR_ENCODER_DEGREES);

    public:
      // Basic control
      void mh8_driveLeft(int spd);
      void mh8_driveRight(int spd);

      // DriveOp
      void mh8_tankDrive(int lStick, int rStick);
      void mh8_arcadeDrive(int xInput, int yInput);

      // Sensor-based driving
      void mh8_driveToTower(float maxPower, float curveTime, double sensitivity);

      // Normal inch-based funcs
      void mh8_DriveStraight(double inches, char dir);
      void mh8_Turn(double deg, int maxSp, char dir);
      void mh8_Arc(double deg, char dir, char fwd);

      // Utility
      int mh8_getAvgDriveSideDeg(char side);
      void mh8_resetDrive();
      void mh8_setBrake(char mode);
  };
}

#endif
