using namespace vex;

extern brain Brain;

// VEXcode devices
extern controller Controller1;
extern motor LEFT_FR;
extern motor LEFT_BK;
extern motor RIGHT_FR;
extern motor RIGHT_BK;
extern motor SPIN;

/**
 * Used to initialize code/tasks/devices added using tools in VEXcode Pro.
 * 
 * This should be called at the start of your int main function.
 */
void  vexcodeInit( void );