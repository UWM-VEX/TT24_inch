#include "main.h"

using namespace pros;

Grabber robotGrabber;

Grabber::Grabber() {};

void Grabber::initGrabber(int8_t leftGrabberPort, int8_t rightGrabberPort)
{
  leftGrabber = new Motor(std::abs(leftGrabberPort), E_MOTOR_GEARSET_18, leftGrabberPort < 0, E_MOTOR_ENCODER_DEGREES);
  rightGrabber = new Motor(std::abs(rightGrabberPort), E_MOTOR_GEARSET_18, rightGrabberPort < 0, E_MOTOR_ENCODER_DEGREES);

  IN_POS = 0;
  OUT_POS = -105;
}

void Grabber::move(int speed)
{
  leftGrabber->move(speed/2);
  rightGrabber->move(speed/2);
}

void Grabber::in()
{
  leftGrabber->move_absolute(IN_POS, 80);
  rightGrabber->move_absolute(IN_POS, 80);
}

void Grabber::out()
{
  leftGrabber->move_absolute(OUT_POS, 80);
  rightGrabber->move_absolute(OUT_POS, 80);
}
