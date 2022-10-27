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
// Vision1              vision        6              
// ---- END VEXCODE CONFIGURED DEVICES ----

#include "vex.h"
#include<math.h>

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
  int fr;
  int bl;
  int br;
  bool sidewaysPressed;
  bool slowed = false;





  enum Horizontal {
    Left,
    Right,
  };

  bool ToggleSlow(){
    slowed=!slowed;
    return slowed;
  }

  public: void horizontal(bool left, bool right){
 //move left
    if (left){
      sidewaysPressed=true;
      fr =  horizontalVelocity;
      br = -horizontalVelocity;

      fl = -horizontalVelocity;
      bl =  horizontalVelocity;

      //move right
    } else if (right){
      sidewaysPressed=true;
      fr = -horizontalVelocity;
      br =  horizontalVelocity;

      fl =  horizontalVelocity;
      bl = -horizontalVelocity;

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

  public: void AutonomousDrive(float left, float right, double t){
      this->reset();
      fl = left;
      bl = left;

      br = right;
      fr = right;
      this->drive();
      wait(t, sec);
      reset();
      this->drive();
      
  }
  public: void AutonomousHorizontal(Horizontal dir, double t){
      this->reset();
      this->horizontal(dir == Horizontal::Left, dir == Horizontal::Right);
      this->drive();
      wait(t, sec);
  }
  
  //spin drivetrain motors based of internal power variables
  public: void drive(){

      if (slowed) {
        fr*=0.5;
        br*=0.5;
    
        fl*=0.5;
        bl*=0.5;
      }
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

void SPINNER(bool rotate, directionType dir, Drivetrain *dr) {
    if(rotate) {
      //drive backwords to apply force
      dr->fr = -2;
      dr->br = -2;

      dr->fl = -8;
      dr->bl = -8;
      SPIN.spin(dir);
    }
}
enum SpoolState{
  Stopped,
  Unspooling,
  Spooling,
};

class Spool {
  SpoolState spinning = Stopped;
  directionType dir = forward;
  public: Drivetrain *d;

  public: void unwind(bool unwind){
    if (unwind)
    {
      spinning = Unspooling;
      dir = forward;
    }
  }

  public: void wind(bool wind){
    if (wind){
      spinning = Spooling;
      SPOOL.spin(reverse);
    } else if (spinning == Spooling) {
      spinning = Stopped;
    }
  }
  public: void update(){
    if (spinning == Unspooling) {
      SPOOL.spin(dir);
      d->fr = d->fr/3;
      d->br = d->br/3;
      d->fl = d->fl/3;
      d->bl = d->bl/3;
    } else if (spinning == Stopped) {
      SPOOL.stop();
    }
  }

};

void pre_auton(void) {
  // Initializing Robot Configuration. DO NOT REMOVE!
  vexcodeInit();




  // All activities that occur before the competition starts
  // Example: clearing encoders, setting servo positions, ...
}

// bool blueOnTop() {
//   Vision1.takeSnapshot(Vision1__BLUE_V);
//   Vision1.
//   return true;
// }

//drives forward then suddely reverse to dump disks sitting on the front of the motor
void dumpy(Drivetrain* d) {
  d->AutonomousDrive(100, 100, 2);
  d->AutonomousDrive(-100, -100, 2);


}

void autonomous(void) {
  SPIN.setVelocity(40, percent);
  Drivetrain d;
  d.reset();
  dumpy(&d);
  d.reset();
  d.drive();
}

void usercontrol(void) {
  //create a drivetrain labeled as "d" and set velocities to 0.  This is used to call drivetrain movement later
  Drivetrain d;
  d.reset();
  //set Spin power for the rollers slow so mother doesnt slip
  SPIN.setVelocity(40, percent);
  //max the string release velocity so we release string as fast as possible
  SPOOL.setVelocity(100, percent);
  //create a spool object we call to later spin the upper wheel
  Spool spool;
  spool.d = &d;

  //core user input loop
  while (1) {
    //stop spinner
    SPIN.stop();
    //resets motor velocities
    d.reset();

    //strafe if a trigger is pressed
    d.horizontal(Controller1.ButtonL2.pressing(), Controller1.ButtonR2.pressing());
    //control left or right wheels based of respective sticks
    d.stickMove(Controller1.Axis3.position(), Controller1.Axis2.position());
  
    //stop unwinding and wind the spool while the "b" button is pressed
    spool.wind(Controller1.ButtonB.pressing());
    //start continuously unwiding the spool if a is pressed
    spool.unwind(Controller1.ButtonA.pressing());
    //run whatever code the spool is set to do
    spool.update();

    //basic print statement for debugging
    // Brain.Screen.clearLine();
    // Brain.Screen.print(spool.spinning);

    //spin if a bumper is pressed
    SPINNER(Controller1.ButtonL1.pressing(), forward, &d);
    SPINNER(Controller1.ButtonR1.pressing(), reverse, &d);

    //toggle speed between slow or fast if button down is pressed
    if (Controller1.ButtonDown.pressing()){
      d.ToggleSlow();
    }
      //causes the drivetrain to execute the movement which was set above
      d.drive();
    //freeze coude for 20ms every loop to prevent the robot from overheating(motors still work, just no input)
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


