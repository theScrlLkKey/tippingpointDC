#include "vex.h"

using namespace vex;
using signature = vision::signature;
using code = vision::code;

// A global instance of brain used for printing to the V5 Brain screen
brain  Brain;

// VEXcode device constructors
controller Controller1 = controller(primary);
motor LEFT_FR = motor(PORT9, ratio18_1, false);
motor LEFT_BK = motor(PORT19, ratio18_1, false);
motor RIGHT_FR = motor(PORT10, ratio18_1, false);
motor RIGHT_BK = motor(PORT18, ratio18_1, false);
motor SPIN = motor(PORT12, ratio18_1, false);
motor SPOOL = motor(PORT14, ratio18_1, false);

// VEXcode generated functions
// define variable for remote controller enable/disable
bool RemoteControlCodeEnabled = true;

/**
 * Used to initialize code/tasks/devices added using tools in VEXcode Pro.
 * 
 * This should be called at the start of your int main function.
 */
void vexcodeInit( void ) {
  // nothing to initialize
}