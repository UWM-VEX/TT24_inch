#include "main.h"

using namespace pros;

Lift robotLift;

Lift::Lift() {};

void Lift::initLift(int8_t leftLiftPort, int8_t rightLiftPort)
{
  leftLift = new Motor(std::abs(leftLiftPort), E_MOTOR_GEARSET_36, leftLiftPort < 0, E_MOTOR_ENCODER_DEGREES);
	rightLift = new Motor(std::abs(rightLiftPort), E_MOTOR_GEARSET_36, rightLiftPort < 0, E_MOTOR_ENCODER_DEGREES);


  FORWARD_POS = 140;
  BACK_POS = 0;
}

void Lift::move(int speed)
{
  leftLift->move(speed);
  rightLift->move(speed);
}

void Lift::forward()
{
  leftLift->move_absolute(FORWARD_POS, 127);
  rightLift->move_absolute(FORWARD_POS, 127);
}

void Lift::back()
{
  leftLift->move_absolute(BACK_POS, 127);
  rightLift->move_absolute(BACK_POS, 127);
}

float Lift::liftPos()
{
  return leftLift->get_position();
}
