#ifndef ROLLER_INCLUDED
#define ROLLER_INCLUDED
#include "drivetrain.h"
using namespace vex;

class RollerSpinner {
  //pointers to drivetrain and roller spinning motor
private:
  Drivetrain *drive;
  motor *spinner;

//constructor of roller spinner class
public:
  RollerSpinner(motor *spinner_, double velocity, Drivetrain *drive_) {
    spinner = spinner_;
    spinner->setVelocity(velocity, percent);
    spinner->setStopping(coast);
    drive = drive_;
  }

//spins the wheel either forward or reverse.  If the wheel is spining also slightly drive backwards to apply pressure on the wheel.
  void update(bool fwd, bool rev) {
    if (fwd || rev) {
      drive->setMotorVelocity(Drivetrain::MotorPosition::front_left, -8);
      drive->setMotorVelocity(Drivetrain::MotorPosition::front_right, -2);
      drive->setMotorVelocity(Drivetrain::MotorPosition::back_right, -2);
      drive->setMotorVelocity(Drivetrain::MotorPosition::back_left, -8);
      // dr->fr = -2;
      // dr->br = -2;
      // dr->fl = -8;
      // dr->bl = -8;
      if (fwd) {
        spinner->spin(forward);
      } else if (rev) {
        spinner->spin(reverse);
      }
    } else {
      spinner->stop();
    }
  }
};
#endif
