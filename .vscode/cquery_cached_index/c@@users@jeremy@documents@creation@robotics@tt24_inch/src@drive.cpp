// #include "main.h"
// #include <cmath>
// using namespace okapi;
//
// Drive robotDrive;
//
// Drive::Drive() {}
//
// void Drive::initDrive(int8_t frontRightPort, int8_t backRightPort, int8_t frontLeftPort, int8_t backLeftPort)
// {
//   frontRight = frontRightPort;
//   backRight = backRightPort;
//
//   frontLeft = frontLeftPort;
//   backLeft = backLeftPort;
// }
//
// okapi::ChassisControllerIntegrated Drive::makeDrive()
// {
//   return ChassisControllerFactory::create(
//     {frontRight, backRight}, {frontLeft, backLeft},
//     AbstractMotor::gearset::green,
//     {4_in, 9_in}
//   );
// }
