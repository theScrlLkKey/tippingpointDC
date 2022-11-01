#include "vex.h"

using namespace vex;
using signature = vision::signature;
using code = vision::code;

// A global instance of brain used for printing to the V5 Brain screen
brain  Brain;

// VEXcode device constructors
controller Controller1 = controller(primary);
motor FRONT_LEFT = motor(PORT9, ratio18_1, false);
motor FRONT_RIGHT = motor(PORT10, ratio18_1, true);
motor BACK_LEFT = motor(PORT19, ratio18_1, false);
motor BACK_RIGHT = motor(PORT18, ratio18_1, true);
motor ROLLER_SPINNER = motor(PORT12, ratio36_1, false);
motor SPOOL = motor(PORT14, ratio18_1, false);
/*vex-vision-config:begin*/
signature VISION_SENSOR__RED_SIG = signature (1, 9605, 10241, 9923, -1537, -1171, -1354, 7.7, 0);
signature VISION_SENSOR__BLUE_SIG = signature (2, -3205, -2897, -3051, 7793, 8415, 8104, 8.3, 0);
signature VISION_SENSOR__SIG_3 = signature (3, 0, 0, 0, 0, 0, 0, 3, 0);
signature VISION_SENSOR__SIG_4 = signature (4, 0, 0, 0, 0, 0, 0, 3, 0);
signature VISION_SENSOR__SIG_5 = signature (5, 0, 0, 0, 0, 0, 0, 3, 0);
signature VISION_SENSOR__SIG_6 = signature (6, 0, 0, 0, 0, 0, 0, 3, 0);
signature VISION_SENSOR__SIG_7 = signature (7, 0, 0, 0, 0, 0, 0, 3, 0);
vision VISION_SENSOR = vision (PORT6, 50, VISION_SENSOR__RED_SIG, VISION_SENSOR__BLUE_SIG, VISION_SENSOR__SIG_3, VISION_SENSOR__SIG_4, VISION_SENSOR__SIG_5, VISION_SENSOR__SIG_6, VISION_SENSOR__SIG_7);
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