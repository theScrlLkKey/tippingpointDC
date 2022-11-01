using namespace vex;

extern brain Brain;

using signature = vision::signature;

// VEXcode devices
extern controller Controller1;
extern motor FRONT_LEFT;
extern motor FRONT_RIGHT;
extern motor BACK_LEFT;
extern motor BACK_RIGHT;
extern motor ROLLER_SPINNER;
extern motor SPOOL;
extern signature VISION_SENSOR__RED_SIG;
extern signature VISION_SENSOR__BLUE_SIG;
extern signature VISION_SENSOR__SIG_3;
extern signature VISION_SENSOR__SIG_4;
extern signature VISION_SENSOR__SIG_5;
extern signature VISION_SENSOR__SIG_6;
extern signature VISION_SENSOR__SIG_7;
extern vision VISION_SENSOR;

/**
 * Used to initialize code/tasks/devices added using tools in VEXcode Pro.
 * 
 * This should be called at the start of your int main function.
 */
void  vexcodeInit( void );