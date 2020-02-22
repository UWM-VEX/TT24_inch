#include "main.h"

using namespace pros;

Intake robotIntake;

Intake::Intake() {};

void Intake::initIntake(int8_t leftIntakePort, int8_t rightIntakePort)
{
  leftIntake = new Motor(std::abs(leftIntakePort), E_MOTOR_GEARSET_36, leftIntakePort < 0, E_MOTOR_ENCODER_DEGREES);
  rightIntake = new Motor(std::abs(rightIntakePort), E_MOTOR_GEARSET_36, rightIntakePort < 0, E_MOTOR_ENCODER_DEGREES);
}

void Intake::move(int speed)
{
  leftIntake->move(speed);
  rightIntake->move(speed);
}
