#ifndef _LIFT_HPP_
#define _LIFT_HPP_

#include "main.h"

class Lift{
private:
  pros::Motor* leftLift;
  pros::Motor* rightLift;
  int FORWARD_POS;
  int BACK_POS;
public:
  Lift();
  void initLift(int8_t leftLiftPort, int8_t rightLiftPort);
  void move(int speed);
  void forward();
  void back();
  float liftPos();
};

extern Lift robotLift;

#endif
