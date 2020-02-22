#include "main.h"

using namespace okapi;

int8_t frontLeft = 16;
int8_t backLeft = 14;
int8_t frontRight = 12;
int8_t backRight = 13;

void opcontrol() {
	pros::Controller master(pros::E_CONTROLLER_MASTER);
	pros::Controller partner(pros::E_CONTROLLER_PARTNER);
	auto myChassis = okapi::ChassisControllerBuilder().withMotors({frontLeft, backLeft}, {(std::int8_t)-frontRight, (std::int8_t)-backRight}).withDimensions(
	okapi::AbstractMotor::gearset::green, {{4_in, 9_in}, imev5GreenTPR}).build();
//	okapi::ChassisControllerIntegrated opcontrolDrive = robotDrive.makeDrive();

int zone = 0;//Dead-zone value

float mult = 1; //Speed Multiplier
float max = 127 * mult;
float min = -127 * mult;
float off = 0;

float pmult = 1;
float pmax = 127 * mult;
float pmin = -127 * mult;
	while (true) {
	// 	pros::lcd::print(0, "%d %d %d", (pros::lcd::read_buttons() & LCD_BTN_LEFT) >> 2,
	// 	                 (pros::lcd::read_buttons() & LCD_BTN_CENTER) >> 1,
	// 	                 (pros::lcd::read_buttons() & LCD_BTN_RIGHT) >> 0);
	// 	int left = master.get_analog(ANALOG_LEFT_Y);
	// 	int right = master.get_analog(ANALOG_RIGHT_Y);
	//
	// 	left_mtr = left;
	// 	right_mtr = right;
	// 	pros::delay(20);

	if(partner.is_connected()){
//Multiplier
		if(partner.get_digital(pros::E_CONTROLLER_DIGITAL_UP)){
			static bool up = false;
			up = !up;
			if(up){
				mult = 1;
			}
		}
		else if(master.get_digital(pros::E_CONTROLLER_DIGITAL_LEFT)){
			static bool med = false;
			med = !med;
			if(med){
				mult = .5;
			}
		}
		else if(master.get_digital(pros::E_CONTROLLER_DIGITAL_DOWN)){
			static bool down = false;
			down = !down;
			if(down){
				mult = .25;
			}
		}
		if(partner.get_digital(pros::E_CONTROLLER_DIGITAL_LEFT)){
			static bool pup = false;
			pup = !pup;
			if(pup){
				pmult = 1;
			}
		}
		else if(master.get_digital(pros::E_CONTROLLER_DIGITAL_RIGHT)){
			static bool pmed = false;
			pmed = !pmed;
			if(pmed){
				pmult = .5;
			}
		}
		else if(master.get_digital(pros::E_CONTROLLER_DIGITAL_Y)){
			static bool pdown = false;
			pdown = !pdown;
			if(pdown){
				pmult = .25;
			}
		}
//DRIVE
		uint driveSelect = 1;
		if(master.get_digital(pros::E_CONTROLLER_DIGITAL_A)){
			static bool pressed = false;
			pressed = !pressed;
			pros::lcd::clear();
			if(pressed && driveSelect<4){
				driveSelect ++;
			}
			else if(pressed && driveSelect>4){
					driveSelect = 1;
			}
		}
		switch(driveSelect)
		{
		case 1:
		// pros::lcd::clear();
		// pros::lcd::set_text(0, "Tank Drive");
		// pros::lcd::set_text(1, "Strafe Bumpers");
			if((std::abs(master.get_analog(ANALOG_LEFT_Y))>zone) || ((std::abs(master.get_analog(ANALOG_RIGHT_Y))>zone))){
				myChassis->model().tank((((master.get_analog(ANALOG_LEFT_Y))/127.0)*mult), ((master.get_analog(ANALOG_RIGHT_Y))/127.0)*mult);
			}
			else{
				myChassis->model().tank(off,off);
			}
			if(master.get_digital(pros::E_CONTROLLER_DIGITAL_R1)){
				robotMid.move(max);
			}
			else if(master.get_digital(pros::E_CONTROLLER_DIGITAL_L1)){
				robotMid.move(min);
			}
			else{
				robotMid.move(off);
			}
		break;
		case 2:
		// pros::lcd::clear();
		// pros::lcd::set_text(0, "Tank Drive");
		// pros::lcd::set_text(1, "Strafe Right Joystick X");
				if((std::abs(master.get_analog(ANALOG_LEFT_Y))>zone) || ((std::abs(master.get_analog(ANALOG_RIGHT_Y))>zone))){
					myChassis->model().tank((((master.get_analog(ANALOG_LEFT_Y))/127.0)*mult), ((master.get_analog(ANALOG_RIGHT_Y))/127.0)*mult);
				}
				else{
					myChassis->model().tank(off,off);
				}
				if((master.get_analog(ANALOG_RIGHT_X))>zone){
					robotMid.move((master.get_analog(ANALOG_RIGHT_X))*mult);
				}
				else{
					robotMid.move(off);
				}
		break;
	}

//LIFT and GRABBER
		if(robotLift.liftPos() < 160){
			if((partner.get_analog(ANALOG_RIGHT_Y))>zone){
				robotLift.move(partner.get_analog(ANALOG_RIGHT_Y));
				robotGrabber.in();
			}
			else if((partner.get_analog(ANALOG_RIGHT_Y))< -zone){
				robotLift.move(partner.get_analog(ANALOG_RIGHT_Y));
				robotGrabber.in();
			}
			else if(partner.get_digital(pros::E_CONTROLLER_DIGITAL_R2)){
				robotLift.move(pmax);
				robotGrabber.out();
			}
			else if(partner.get_digital(pros::E_CONTROLLER_DIGITAL_R1)){
				robotLift.move(pmin);
				robotGrabber.in();
			}
			else if(partner.get_digital(pros::E_CONTROLLER_DIGITAL_X)){
				robotLift.move(pmax);
				robotGrabber.out();
			}
			else if(partner.get_digital(pros::E_CONTROLLER_DIGITAL_B)){
				robotLift.move(pmin);
				robotGrabber.in();
			}
			else{
				robotLift.move(off);
				robotGrabber.move(off);
			}

		}
		else if(robotLift.liftPos() > 160){
			if((partner.get_analog(ANALOG_RIGHT_Y))>zone){
				robotGrabber.out();
			}
			else if((partner.get_analog(ANALOG_RIGHT_Y)< -zone)){
				robotLift.move(partner.get_analog(ANALOG_RIGHT_Y));
				robotGrabber.in();
			}
			else if(partner.get_digital(pros::E_CONTROLLER_DIGITAL_R2)){
				robotGrabber.out();
			}
			else if(partner.get_digital(pros::E_CONTROLLER_DIGITAL_R1)){
				robotLift.move(pmin);
				robotGrabber.in();
			}
			else if(partner.get_digital(pros::E_CONTROLLER_DIGITAL_X)){
				robotGrabber.out();
			}
			else if(partner.get_digital(pros::E_CONTROLLER_DIGITAL_B)){
				robotLift.move(pmin);
				robotGrabber.in();
			}
			else{
				robotLift.move(off);
				robotGrabber.move(off);
			}
		}

//INTAKE
		if(std::abs(partner.get_analog(ANALOG_LEFT_Y))>zone){
			robotIntake.move(partner.get_analog(ANALOG_LEFT_Y));
		}
		else if(partner.get_digital(pros::E_CONTROLLER_DIGITAL_L2)){
			robotIntake.move(pmax);
		}
		else if(partner.get_digital(pros::E_CONTROLLER_DIGITAL_L1)){
			robotIntake.move(pmin);
		}
		else if(partner.get_digital(pros::E_CONTROLLER_DIGITAL_UP)){
			robotIntake.move(pmax);
		}
		else if(partner.get_digital(pros::E_CONTROLLER_DIGITAL_DOWN)){
			robotIntake.move(pmin);
		}
		else{
			robotIntake.move(off);
		}

	}
	else if(!(partner.is_connected())){
		myChassis->model().tank(master.get_analog(ANALOG_LEFT_Y), master.get_analog(ANALOG_RIGHT_Y));
		robotMid.move(master.get_analog(ANALOG_RIGHT_X));
		if(master.get_digital(pros::E_CONTROLLER_DIGITAL_UP)){
			robotLift.move(max);
		}
		else if(master.get_digital(pros::E_CONTROLLER_DIGITAL_DOWN)){
			robotLift.move(min);
		}
		if(master.get_digital(pros::E_CONTROLLER_DIGITAL_L2)){
			robotIntake.move(max);
		}
		else if(master.get_digital(pros::E_CONTROLLER_DIGITAL_L1)){
			robotIntake.move(min);
		}
		else{
			robotLift.move(off);
			robotIntake.move(off);
		}
		if(master.get_digital(pros::E_CONTROLLER_DIGITAL_X)){
			robotGrabber.out();
		}
		else if(master.get_digital(pros::E_CONTROLLER_DIGITAL_B)){
			robotGrabber.in();
		}
	}
}
}
