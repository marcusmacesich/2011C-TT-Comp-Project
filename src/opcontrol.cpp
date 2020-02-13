#include "main.h"

void opcontrol() {


	while (true){

pros::lcd::print(1,"Inertial Sensor: %f degrees\n",inert.get_rotation());
pros::lcd::print(3,"Right Encoder: %d ticks\n",rEnc.get_value());
pros::lcd::print(5,"Left Encoder: %d ticks\n",lEnc.get_value());
	// pros::lcd::print(1,"RF: %f\n",Right_Front_Drive.get_efficiency());
	// pros::lcd::print(2,"RB: %f\n",Right_Back_Drive.get_efficiency());
	// pros::lcd::print(4,"LF: %f\n",Left_Front_Drive.get_efficiency());
	// pros::lcd::print(5,"LB: %f\n",Left_Back_Drive.get_efficiency());

		Left_Front_Drive.set_brake_mode(MOTOR_BRAKE_BRAKE);
		Left_Back_Drive.set_brake_mode(MOTOR_BRAKE_BRAKE);
		Right_Front_Drive.set_brake_mode(MOTOR_BRAKE_BRAKE);
		Right_Back_Drive.set_brake_mode(MOTOR_BRAKE_BRAKE);

		//--------------------------------------------// Drive Train

			Left_Front_Drive.move(master.get_analog(ANALOG_LEFT_Y));
			Left_Back_Drive.move(master.get_analog(ANALOG_LEFT_Y));
			Right_Front_Drive.move(master.get_analog(ANALOG_RIGHT_Y));
			Right_Back_Drive.move(master.get_analog(ANALOG_RIGHT_Y));


		//--------------------------------------------// Angler

		float AngMin = 1500;
		float AngMax = 10;
		float AngVal = Ang_Pot.get_value();
		float MaxAcc = 145;

		float VelocityInterval = ((AngMin-AngMax))/MaxAcc;
		float AnglerVelocity = (-(((AngVal-AngMax))/(VelocityInterval)));

		if (master.get_digital(DIGITAL_X)){
			Angler.set_current_limit(12000);
			Angler.move_voltage((AnglerVelocity*120));
		}
		else if (master.get_digital(DIGITAL_A)){
			Angler.move_voltage(10000);
		}
		else {
			Angler.set_brake_mode(MOTOR_BRAKE_BRAKE);
			Angler.move_velocity(0);
		}

		//--------------------------------------------// Rollers

		if (master.get_digital(DIGITAL_R1)){
			Right_Roller.move_velocity(200);
			Left_Roller.move_velocity(200);
		}
		else if (master.get_digital(DIGITAL_R2)){
			Right_Roller.move_velocity(-200);
			Left_Roller.move_velocity(-200);
		}
		else if (AngVal < 600){
			Right_Roller.set_current_limit(500);
			Left_Roller.set_current_limit(800);
			Right_Roller.set_brake_mode(MOTOR_BRAKE_COAST);
			Left_Roller.set_brake_mode(MOTOR_BRAKE_COAST);
			Right_Roller.move_velocity(-20);
			Left_Roller.move_velocity(-20);
		}
		else {
			Right_Roller.set_current_limit(12000);
			Left_Roller.set_current_limit(12000);
			Right_Roller.set_brake_mode(MOTOR_BRAKE_BRAKE);
			Left_Roller.set_brake_mode(MOTOR_BRAKE_BRAKE);
			Right_Roller.move_velocity(0);
			Left_Roller.move_velocity(0);
		}

		//------------------------------------------// Arms

		if (master.get_digital(DIGITAL_L1)){
			if(AngVal > 1550){
			Angler.move_velocity(-200);
			}
			else if(AngVal < 1550){
			Arm.move_velocity(200);
			}
		}
		else if (master.get_digital(DIGITAL_L2)){
			Arm.move_velocity(-200);
		}
		else {
			Arm.set_brake_mode(MOTOR_BRAKE_BRAKE);
			Arm.move_velocity(0);
			}


		pros::delay(20);  //Cortex Boy Needs a Break
	}
}
