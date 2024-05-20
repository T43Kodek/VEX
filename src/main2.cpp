#pragma region VEXcode Generated Robot Configuration
// Make sure all required headers are included.
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
#include <string.h>


#include "vex.h"

using namespace vex;

// Brain should be defined by default
brain Brain;


// START V5 MACROS
#define waitUntil(condition)                                                   \
  do {                                                                         \
    wait(5, msec);                                                             \
  } while (!(condition))

#define repeat(iterations)                                                     \
  for (int iterator = 0; iterator < iterations; iterator++)
// END V5 MACROS


// Robot configuration code.
/*vex-vision-config:begin*/
vision::signature Vision21__H = vision::signature (1, -3303, -2565, -2934,9657, 12303, 10980,5, 0);
vision::signature Vision21__REDBOX = vision::signature (2, 0, 0, 0,0, 0, 0,3, 0);
vision::signature Vision21__GREENBOX = vision::signature (3, 0, 0, 0,0, 0, 0,3, 0);
vision Vision21 = vision (PORT21, 50, Vision21__H, Vision21__REDBOX, Vision21__GREENBOX);
/*vex-vision-config:end*/
motor LeftDriveSmart = motor(PORT20, ratio18_1, false);
motor RightDriveSmart = motor(PORT11, ratio18_1, true);
inertial DrivetrainInertial = inertial(PORT3);
smartdrive Drivetrain = smartdrive(LeftDriveSmart, RightDriveSmart, DrivetrainInertial, 319.19, 320, 40, mm, 1);

motor arm = motor(PORT1, ratio18_1, false);

motor claw = motor(PORT13, ratio18_1, false);


bool vexcode_initial_drivetrain_calibration_completed = false;
void calibrateDrivetrain() {
  wait(200, msec);
  Brain.Screen.print("Calibrating");
  Brain.Screen.newLine();
  Brain.Screen.print("Inertial");
  DrivetrainInertial.calibrate();
  while (DrivetrainInertial.isCalibrating()) {
    wait(25, msec);
  }
  vexcode_initial_drivetrain_calibration_completed = true;
  // Clears the screen and returns the cursor to row 1, column 1.
  Brain.Screen.clearScreen();
  Brain.Screen.setCursor(1, 1);
}

// Helper to make playing sounds from the V5 in VEXcode easier and
// keeps the code cleaner by making it clear what is happening.
void playVexcodeSound(const char *soundName) {
  printf("VEXPlaySound:%s\n", soundName);
  wait(5, msec);
}

#pragma endregion VEXcode Generated Robot Configuration
// Include the V5 Library
#include "vex.h"
  
// Allows for easier use of the VEX Library
using namespace vex;

int Vision21_objectIndex = 0;

float myVariable;

event checkRed = event();
event checkBlue = event();
event checkGreen = event();
event message1 = event();

// "when started" hat block
int whenStarted1() {
  while (true) {
    Vision21.takeSnapshot(Vision21__H);
    if (Vision21.objectCount > 0) {
      if (Vision21.objects[Vision21_objectIndex].centerX > 100.0) {
        Drivetrain.drive(forward);
      }
      if (Vision21.objects[Vision21_objectIndex].centerX < 60.0) {
        Drivetrain.drive(reverse);
      }
      if (Vision21.objects[Vision21_objectIndex].centerX > 60.0 && Vision21.objects[Vision21_objectIndex].centerX < 100.0) {
        if (Vision21.objects[Vision21_objectIndex].width < 125.0) {
          Drivetrain.drive(forward);
        }
        else {
          Drivetrain.stop();
        }
      }
    }
    else {
      Drivetrain.setTurnVelocity(25.0, percent);
      Drivetrain.turn(right);
    }
  wait(5, msec);
  }
  return 0;
}


int main() {
  // Calibrate the Drivetrain
  calibrateDrivetrain();

  // post event registration

  // set default print color to black
  printf("\033[30m");

  // wait for rotation sensor to fully initialize
  wait(30, msec);

  whenStarted1();
}