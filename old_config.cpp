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
motor SPIN = motor(PORT12, ratio36_1, false);
motor SPOOL = motor(PORT14, ratio18_1, false);
/*vex-vision-config:begin*/
signature Vision1__RED_V = signature (1, 8267, 10923, 9595, -1703, -673, -1188, 3, 0);
signature Vision1__BLUE_V = signature (2, -3077, -1701, -2389, 8815, 14125, 11470, 2.5, 0);
vision Vision1 = vision (PORT1, 50, Vision1__RED_V, Vision1__BLUE_V);
/*vex-vision-config:end*/

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