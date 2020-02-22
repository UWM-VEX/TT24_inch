#ifndef _GRABBER_HPP_
#define _GRABBER_HPP_

#include "main.h"

class Grabber{
private:
  pros::Motor* leftGrabber;
  pros::Motor* rightGrabber;
  int IN_POS;
  int OUT_POS;
public:
  Grabber();
  void initGrabber(int8_t leftGrabberPort, int8_t rightGrabberPort);
  void move(int speed);
  void in();
  void out();
};

extern Grabber robotGrabber;

#endif
