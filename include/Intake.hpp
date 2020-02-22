#ifndef _INTAKE_HPP_
#define _INTAKE_HPP_

#include "main.h"

class Intake{
private:
  pros::Motor* leftIntake;
  pros::Motor* rightIntake;
public:
  Intake();
  void initIntake(int8_t leftIntakePort, int8_t rightIntakePort);
  void move(int speed);
};

extern Intake robotIntake;

#endif
