/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       main.cpp                                                  */
/*    Author:       VEX                                                       */
/*    Created:      Thu Sep 26 2019                                           */
/*    Description:  Competition Template                                      */
/*                                                                            */
/*----------------------------------------------------------------------------*/

// ---- START VEXCODE CONFIGURED DEVICES ----
// Robot Configuration:
// [Name]               [Type]        [Port(s)]
// Controller1          controller                    
// LEFT_FR              motor         9               
// LEFT_BK              motor         19              
// RIGHT_FR             motor         10              
// RIGHT_BK             motor         18              
// SPIN                 motor         12              
// ---- END VEXCODE CONFIGURED DEVICES ----

#include "vex.h"

using namespace vex;

// A global instance of competition
competition Competition;

// define your global instances of motors and other devices here

/*---------------------------------------------------------------------------*/
/*                          Pre-Autonomous Functions                         */
/*                                                                           */
/*  You may want to perform some actions before the competition starts.      */
/*  Do them in the following function.  You must return from this function   */
/*  or the autonomous and usercontrol tasks will not be started.  This       */
/*  function is only called once after the V5 has been powered on and        */
/*  not every time that the robot is disabled.                               */
/*---------------------------------------------------------------------------*/

//manual drivetrain implementation
class Drivetrain {
  int horizontalVelocity = 70;
  //fr = front right drivetrain moter power in %
  //fl = front left drivetrain moter power in %
  //br = back right drivetrain moter power in %
  //bl = back left drivetrain moter power in %

  public: int fl;
  public: int fr;
  public: int bl;
  public: int br;
  public: bool sidewaysPressed;


  public: void horizontal(bool left, bool right){
 //move left
    if (left){
      sidewaysPressed=true;
      fr = -horizontalVelocity;
      br =  horizontalVelocity;

      fl =  horizontalVelocity;
      bl = -horizontalVelocity;

      //move right
    } else if (right){
      sidewaysPressed=true;
      fr =  horizontalVelocity;
      br = -horizontalVelocity;

      fl = -horizontalVelocity;
      bl =  horizontalVelocity;

    }
  }
  public: void stickMove(float LeftStick, float RightStick){
  //move based of stick if stick is pressed
    if (LeftStick != 0 || RightStick != 0){
      //mix horizontal and stick
      if (sidewaysPressed) {
        fr *=0.5;
        br *=0.5;
        fl *=0.5;
        bl *=0.5;

        fl+=LeftStick*0.5;
        bl+=LeftStick*0.5;

        fr+=RightStick*0.5;
        br+=RightStick*0.5;
        //full stick
      } else {
        fl+=LeftStick;
        bl+=LeftStick;

        fr+=RightStick;
        br+=RightStick; 

      }
    }
    
  }
  
  //spin drivetrain motors based of internal power variables
  public: void drive(){
      RIGHT_FR.setVelocity(-fr, percent);
      RIGHT_BK.setVelocity(-br, percent);
      LEFT_FR.setVelocity(fl, percent);
      LEFT_BK.setVelocity(bl, percent);

      LEFT_FR.spin(forward);
      LEFT_BK.spin(forward);
      RIGHT_FR.spin(forward);
      RIGHT_BK.spin(forward);
  }

  //resets power vars to 0 and resets sideways bool
  public: void reset(){
    sidewaysPressed = false;
    fl = 0;
    fr = 0;
    bl = 0;
    br = 0;
  }
};

void SPINNER(bool clockwise, Drivetrain *dr) {
    if(clockwise) {
      dr->fr = -8;
      dr->fl = -8;
      dr->bl = -8;
      dr->br = -8;
      SPIN.spin(reverse);
  } else {
      SPIN.stop();
    }
}

void pre_auton(void) {
  // Initializing Robot Configuration. DO NOT REMOVE!
  vexcodeInit();

  // All activities that occur before the competition starts
  // Example: clearing encoders, setting servo positions, ...
}

/*---------------------------------------------------------------------------*/
/*                                                                           */
/*                              Autonomous Task                              */
/*                                                                           */
/*  This task is used to control your robot during the autonomous phase of   */
/*  a VEX Competition.                                                       */
/*                                                                           */
/*  You must modify the code to add your own robot specific commands here.   */
/*---------------------------------------------------------------------------*/

void autonomous(void) {
  // ..........................................................................
  // Insert autonomous user code here.
  // ..........................................................................
}

/*---------------------------------------------------------------------------*/
/*                                                                           */
/*                              User Control Task                            */
/*                                                                           */
/*  This task is used to control your robot during the user control phase of */
/*  a VEX Competition.                                                       */
/*                                                                           */
/*  You must modify the code to add your own robot specific commands here.   */
/*---------------------------------------------------------------------------*/

void usercontrol(void) {
  //initalize drivetrain labeled as "d" and set velocities to 0
  Drivetrain d;
  d.reset();
  //set inital Spin power
  SPIN.setVelocity(60, percent);

  //core user input loop
  while (1) {
    //spinner logic

    //resets motor velocities
    d.reset();

    d.horizontal(Controller1.ButtonL2.pressing(), Controller1.ButtonR2.pressing());
    d.stickMove(Controller1.Axis3.position(), Controller1.Axis2.position());

    Drivetrain* f = &d;
    SPINNER(Controller1.ButtonX.pressing(), f);
    Controller1.Screen.newLine();
    Controller1.Screen.print(":D");
    //send drivetrain velocities to motors
    d.drive();
    wait(20, msec);
    }
}

//
// Main will set up the competition functions and callbacks.
//
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


