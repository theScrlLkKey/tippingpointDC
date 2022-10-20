using namespace vex;

extern brain Brain;

using signature = vision::signature;

// VEXcode devices
extern controller Controller1;
extern motor LEFT_FR;
extern motor LEFT_BK;
extern motor RIGHT_FR;
extern motor RIGHT_BK;
extern motor SPIN;
extern motor SPOOL;
extern signature Vision1__RED_V;
extern signature Vision1__BLUE_V;
extern signature Vision1__SIG_3;
extern signature Vision1__SIG_4;
extern signature Vision1__SIG_5;
extern signature Vision1__SIG_6;
extern signature Vision1__SIG_7;
extern vision Vision1;


/**
 * Used to initialize code/tasks/devices added using tools in VEXcode Pro.
 * 
 * This should be called at the start of your int main function.
 */
void  vexcodeInit( void );