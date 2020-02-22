#ifndef _MIDDRIVE_HPP_
#define _MIDDRIVE_HPP_

#include "main.h"

class Mid{
private:
  pros::Motor* middle;
public:
  Mid();
  void initMid(int8_t middlePort);
  void move(int speed);
};

extern Mid robotMid;

#endif
