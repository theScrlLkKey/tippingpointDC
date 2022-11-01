// ---- START VEXCODE CONFIGURED DEVICES ----
// Robot Configuration:
// [Name]               [Type]        [Port(s)]
// Controller1          controller                    
// FRONT_LEFT           motor         9               
// FRONT_RIGHT          motor         10              
// BACK_LEFT            motor         19              
// BACK_RIGHT           motor         18              
// ROLLER_SPINNER       motor         12              
// SPOOL                motor         14              
// VISION_SENSOR        vision        6               
// ---- END VEXCODE CONFIGURED DEVICES ----
// ---- START VEXCODE CONFIGURED DEVICES ----
// Robot Configuration:
// [Name]               [Type]        [Port(s)]
// Controller1          controller
// FRONT_LEFT           motor         9
// FRONT_RIGHT          motor         10
// BACK_LEFT            motor         19
// BACK_RIGHT           motor         18
// ROLLER_SPINNER       motor         12
// SPOOL                motor         14
// VISION_SENSOR        vision        6
// ---- END VEXCODE CONFIGURED DEVICES ----
/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       main.cpp                                                  */
/*    Author:       Carter Wobbe                                              */
/*    Created:      Sun Nov 30 2022                                           */
/*    Description:  spin up                                                   */
/*                                                                            */
/*----------------------------------------------------------------------------*/
#define COLOR TeamColor::Blue

#include "vex.h"

#include "drivetrain.h"
#include "rollerSpinner.h"
#include "spool.h"
#include "vision.h"


using namespace vex;

competition Competition;

void pre_auton(void) {
  // Initializing Robot Configuration. DO NOT REMOVE!
  vexcodeInit();
  if (COLOR == TeamColor::Red) {
    VISION_SENSOR.setLedColor(255, 0, 0);
  } else if (COLOR == TeamColor::Blue) {
    VISION_SENSOR.setLedColor(0, 0, 255);
  }
}
// drives forward then suddely reverse to dump disks sitting on the front of the
// motor
void dumpy(Drivetrain *d) {
  d->AutonomousDrive(100, 100, 2);
  d->AutonomousDrive(-100, -100, 1.75);
}

void autonomous(void) {
  ROLLER_SPINNER.setVelocity(40, percent);
  Drivetrain drive =
      Drivetrain(&FRONT_LEFT, &FRONT_RIGHT, &BACK_LEFT, &BACK_RIGHT, brake);
  dumpy(&drive);
  drive.stop();
}

void usercontrol(void) {
  // create a drivetrain labeled as "drive" by passing in motors and stop type
  Drivetrain drive =
      Drivetrain(&FRONT_LEFT, &FRONT_RIGHT, &BACK_LEFT, &BACK_RIGHT, coast);

  // initalize roller spinner with lower velocity to prevent chain slipage
  RollerSpinner rollerSpinner = RollerSpinner(&ROLLER_SPINNER, 60, &drive);

  // inititalize spool with velocity 100
  Spool spool = Spool(&SPOOL, 100, &drive);

  Vision vision = Vision(&VISION_SENSOR, COLOR);

  // core user input loop
  while (1) {
    Controller1.Screen.clearScreen();
    Controller1.Screen.newLine();
    Controller1.Screen.print(vision.red_on_top());
    // vision.rolor_state();
    // control left or right wheels based of respective sticks and straife if a
    // trigger is pressed
    drive.userControl(
        Controller1.Axis3.position(), Controller1.Axis2.position(),
        Controller1.ButtonL2.pressing(), Controller1.ButtonR2.pressing());
 
    // continuously unwind the spool when a is pressed and wind the spool while
    // b is pressed
    spool.update(Controller1.ButtonA.pressing(),
                 Controller1.ButtonB.pressing());

    rollerSpinner.update(Controller1.ButtonL1.pressing(),
                         Controller1.ButtonR1.pressing());
    // causes the drivetrain to execute the movement which was set above
    drive.drive();

    // freeze coude for 20ms every loop to prevent the robot from
    // overheating(motors still work, just no input)
    wait(20, msec);
  }
}

// Main will set up the competition functions and callbacks.
int main() {
  // Set up callbacks for autonomous and driver control periods.
  Competition.autonomous(autonomous);
  Competition.drivercontrol(usercontrol);

  // Run the pre-autonomous function.
  pre_auton();

  // Prevent main from exiting with an infinite loop.
  while (true) {
    wait(100, msec);
  }
}