#ifndef VISION_INCLUDED
#define VISION_INCLUDED
#include "vex.h"
enum TeamColor {
  Red,
  Blue,
};

class Vision {
private:
  vex::vision *vision;
  TeamColor color;

public:
  Vision(vex::vision *vision_, TeamColor color_) {
    vision = vision_;
    color = color_;
  }

  int red_on_top() {
    vision->takeSnapshot(VISION_SENSOR__RED_SIG);
    int red_y = vision->largestObject.centerY;
    vision->takeSnapshot(VISION_SENSOR__BLUE_SIG);
    int blue_y = vision->largestObject.centerY;
    Brain.Screen.clearLine();
    Brain.Screen.print("%d, %d", red_y, blue_y);
    if (red_y == 0 || blue_y == 0) {
      return 0;
    }
    if (red_y > blue_y) {
      return 1;
    }
    else {
      return -1;
    }
  }
};
#endif
