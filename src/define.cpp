#include "main.h"

/*
Define motors and sensor in this document
Don't forget to add the extern in the main.h file
*/

//prosv5 upload --slot [number]

#define Arm_Port 12
#define Angler_Port 11
#define Right_Front_Port 18
#define Right_Back_Port 13
#define Left_Front_Port 17
#define Left_Back_Port 19
#define Left_Roller_Port 6
#define Right_Roller_Port 2
#define Ang_Pot_Port 'A'
#define lEncP1 'C'
#define lEncP2 'D'
#define rEncP1 'E'
#define rEncP2 'F'
#define Inertial_Port 8
//

pros::Controller master (CONTROLLER_MASTER);
pros::Imu inert (Inertial_Port);
pros::Motor Left_Front_Drive (Left_Front_Port,MOTOR_GEARSET_18,false,MOTOR_ENCODER_DEGREES);
pros::Motor Left_Back_Drive (Left_Back_Port,MOTOR_GEARSET_18,false,MOTOR_ENCODER_DEGREES);
pros::Motor Right_Front_Drive (Right_Front_Port,MOTOR_GEARSET_18,true,MOTOR_ENCODER_DEGREES);
pros::Motor Right_Back_Drive (Right_Back_Port,MOTOR_GEARSET_18,true,MOTOR_ENCODER_DEGREES);
pros::Motor Angler (Angler_Port,MOTOR_GEARSET_36,MOTOR_ENCODER_DEGREES);
pros::Motor Left_Roller (Left_Roller_Port,MOTOR_GEARSET_18,false,MOTOR_ENCODER_DEGREES);
pros::Motor Right_Roller (Right_Roller_Port,MOTOR_GEARSET_18,true,MOTOR_ENCODER_DEGREES);
pros::Motor Arm (Arm_Port,MOTOR_GEARSET_18,false,MOTOR_ENCODER_DEGREES);
pros::ADIAnalogIn Ang_Pot (Ang_Pot_Port);
pros::ADIEncoder rEnc (rEncP1,rEncP2,true);
pros::ADIEncoder lEnc (lEncP1,lEncP2,false);
