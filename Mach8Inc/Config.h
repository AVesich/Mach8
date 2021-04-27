#ifndef CONFIG_H
#define CONFIG_H

namespace mh8_Variables {

/*
Port declaration

"REV" variables change wether the motor is reversed (0 is not reversed 1 is reversed)
Port number 0 means the motor is unused - Default value
*/

#define M_LFRONT 1 // Front left motor
#define M_LFRONT_REV 1

#define M_LBACK 12 // Back left motor
#define M_LBACK_REV 1

#define M_RFRONT 10 // Front right motor
#define M_RFRONT_REV 0

#define M_RBACK 20 // Back right motor
#define M_RBACK_REV 0

#define M_DIST 0 // Distance sensor (optional but does disable some functionality when not in use)
#define M_INERT 0 // Distance sensor (optional but does disable some functionality when not in use)

#define M_BRAKE 'c' // Brake mode for driveOp

/*
Variable declaration

Tune PID values until the robot moves smoothly and consistently
Tune turn constant until 90 degree function input produces a 90 degree turn
*/

// Straight pid
#define SKP 0.4
#define SKI 0.07
#define SKD 7.53
#define ALIGN 1.5

// Turn pid
#define TKP 0.9
#define TKI 0.02
#define TKD 3.0

// Arc pid
#define AKP 0.9
#define AKI 0.02
#define AKD 3.0

// Constants for distance
#define STRIAGHTCONST .363 // Should be tuned until 24 inch input results in a drive length of 1 tile/24 inches
#define TURNCONST 1.03 // Should be tuned until 90 degree input results in a 90 degree robot turn
#define ARCCONSTL 1.91 // Should be tuned until 90 degree input results in a 90 degree robot arc left
#define ARCCONSTR 2.13 // Should be tuned until 90 degree input results in a 90 degree robot arc right

}

#endif
