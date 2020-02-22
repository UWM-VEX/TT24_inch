#include "main.h"

using namespace pros;

Mid robotMid;

Mid::Mid(){};

void Mid::initMid(int8_t middlePort)
{
  middle = new Motor(std::abs(middlePort), E_MOTOR_GEARSET_18, middlePort < 0, E_MOTOR_ENCODER_DEGREES);
}

void Mid::move(int speed)
{
  middle->move(speed);
}
