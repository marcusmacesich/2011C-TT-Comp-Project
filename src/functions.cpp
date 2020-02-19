#include "main.h"

void resetSensors(){
   Left_Front_Drive.tare_position();
   Left_Back_Drive.tare_position();
   Right_Front_Drive.tare_position();
   Right_Back_Drive.tare_position();
   Right_Roller.tare_position();
   Left_Roller.tare_position();
   Angler.tare_position();
   rEnc.reset();
   lEnc.reset();
}

void resetDriveTrain(){
    Left_Front_Drive.tare_position();
    Left_Back_Drive.tare_position();
    Right_Front_Drive.tare_position();
    Right_Back_Drive.tare_position();
}

void driveBrake(){
   Left_Front_Drive.set_brake_mode(MOTOR_BRAKE_BRAKE);
   Left_Back_Drive.set_brake_mode(MOTOR_BRAKE_BRAKE);
   Right_Front_Drive.set_brake_mode(MOTOR_BRAKE_BRAKE);
   Right_Back_Drive.set_brake_mode(MOTOR_BRAKE_BRAKE);
}

void driveCoast(){
   Left_Front_Drive.set_brake_mode(MOTOR_BRAKE_COAST);
   Left_Back_Drive.set_brake_mode(MOTOR_BRAKE_COAST);
   Right_Front_Drive.set_brake_mode(MOTOR_BRAKE_COAST);
   Right_Back_Drive.set_brake_mode(MOTOR_BRAKE_COAST);
}

void driveHold(){
   Left_Front_Drive.set_brake_mode(MOTOR_BRAKE_HOLD);
   Left_Back_Drive.set_brake_mode(MOTOR_BRAKE_HOLD);
   Right_Front_Drive.set_brake_mode(MOTOR_BRAKE_HOLD);
   Right_Back_Drive.set_brake_mode(MOTOR_BRAKE_HOLD);
}

void moveLeftDriveTrain(int velocity){
   Left_Front_Drive.move_voltage(velocity);
   Left_Back_Drive.move_voltage(velocity);
}

void moveRightDriveTrain(int velocity){
  Right_Front_Drive.move_voltage(velocity);
  Right_Back_Drive.move_voltage(velocity);
}

void moveDriveTrain(int velocity){
  Left_Front_Drive.move_voltage(velocity);
  Left_Back_Drive.move_voltage(velocity);
  Right_Front_Drive.move_voltage(velocity);
  Right_Back_Drive.move_voltage(velocity);
}

void driveStop(){
  Left_Front_Drive.move_velocity(0);
  Left_Back_Drive.move_velocity(0);
  Right_Front_Drive.move_velocity(0);
  Right_Back_Drive.move_velocity(0);
}

//360 for one full wheel rotation
//Reading from 4 encoder values each side averaged
//360 * 2
//One full rotation of 4in omni = 12.566 in traveled (circumference)
//inchToTicks = 360*2/12.566 = 57.296

int inchToTicks (float inch){
  int ticks;
  ticks = inch / .024;
  return ticks;
}

int degreesToTicks (float degrees){
  int ticks;
  ticks = degrees * 100;
  return ticks;
}

float percentToVoltage (float percent){
  int voltage;
  voltage = (percent * 120);
  return voltage;
}



void rollUptake(int velocity){
  Left_Roller.move_velocity(velocity);
  Right_Roller.move_velocity(velocity);
}

void unfold(){
  Arm.move_voltage(12000);
  pros::delay(800);
  Arm.move_voltage(-12000);
  pros::delay(900);
  Arm.move_velocity(0);
  Arm.set_brake_mode(MOTOR_BRAKE_HOLD);
}

float inertRoll;

void drive(std::string direction, float target, int timeOut, int maxVelocity){
  resetSensors();
  //Constants//
  float kP = 20;
  float kP_t = 6;
  float kI = 0.01;
  float kI_t = 0.01;
  float kD = 5;
  float kD_t = 30;
  float kD_d = 300;
  float kP_d = 500;
  //Error var declarations//
  float error;
  float error_drift;
  float lastError;
  float lastError_d;
  float roll;
  //Calc var declarations//
  float proportion;
  float proportion_drift;
  float intergral;
  float derivative;
  float derivative_d;
  ////////////////////////
  float intergralActive = inchToTicks(3);
  float intergralActive_t = degreesToTicks(5);
  float intergralLimit = (maxVelocity/kI)/50;
  float intergralLimit_t = (maxVelocity/kI_t)/50;
  //Motor output var declarations//
  float targetVolt;
  float finalVolt;
  float finalPct;
  //Timeout var declarations
  long eTime = pros::millis() + timeOut;

  //Loop continues until time out is reached
  while(pros::millis() < eTime){
//PID calculation when the direction desired is forward/ backwards
if(direction == "f" || direction == "b"){

    //Error reestablished at the start of the loop
    error = inchToTicks(target) - (fabs(rEnc.get_value() + lEnc.get_value())/2);
      //Proportion stores the error until it can be multiplied by the constant
      proportion = error;
        //Intergral takes area under the error and is useful for major adjustment
          if(fabs(error) < intergralActive){
            intergral = intergral + error;
          }
          else{
            intergral = 0;
          }
            //Set intergral output to limit
            if(intergral > intergralLimit){
              intergral = intergralLimit;
            }
            else if(intergral < intergralLimit){
              intergral = -intergralLimit;
            }

        //Derivative finds difference between current error and last recrded to recieve ROC, good for fine adjustment
        derivative = error - lastError;
        lastError = error;
          //Sets var equal to zero if no adjustment is needed
          if(error == 0){
            derivative = 0;
          }

          //Convert target velocity to voltage
          targetVolt = percentToVoltage(maxVelocity);

            //Final output of drive alg that applies constants to the PID factors
            finalVolt = kP*proportion + kI*intergral + kD*derivative;
            //Sets final output so that its proportional to the target
            // finalPct = 100*(1 - (fabs(finalVolt) / targetVolt));
            // finalPct = finalPct / maxVelocity;
            // finalVolt = percentToVoltage(finalPct);
              //Declaring the final output as the target if it exceeds
              if(finalVolt > targetVolt){
                finalVolt = targetVolt;
              }
              else if(finalVolt < -targetVolt){
                finalVolt = -targetVolt;
              }

                //Establishes the initial error simply as the value of the IMU since its supposed to be 0
                error_drift = inert.get_rotation() - (inertRoll)/100;
                //Derivative finds difference between current error and last recrded to recieve ROC, good for fine adjustment
                derivative = error_drift - lastError_d;
                lastError_d = inert.get_rotation();

                proportion_drift = error_drift * kP_d;

                if(direction == "f"){
                  moveRightDriveTrain(finalVolt+proportion_drift);
                  moveLeftDriveTrain(finalVolt-proportion_drift);
                }
                else if(direction == "b"){
                  moveRightDriveTrain(-finalVolt);
                  moveLeftDriveTrain(-finalVolt);
                }

}

//PID Calculation when the direction desired is turn center
else if(direction == "r" || direction == "l"){

  //Rotational Value around z-axis
  roll = degreesToTicks(inert.get_rotation()) - inertRoll;

    //Error reestablished at the start of the loop
    error = degreesToTicks(target) - fabs(roll);
      //Proportion stores the error until it can be multiplied by the constant
      proportion = error;
        //Intergral takes area under the error and is useful for major adjustment
          if(fabs(error) < intergralActive_t){
            intergral = intergral + error;
          }
          else{
            intergral = 0;
          }
            //Set intergral output to limit
            if(intergral > intergralLimit_t){
              intergral = intergralLimit_t;
            }
            else if(intergral < intergralLimit_t){
              intergral = -intergralLimit_t;
            }

        //Derivative finds difference between current error and last recrded to recieve ROC, good for fine adjustment
        derivative = error - lastError;
        lastError = error;
          //Sets var equal to zero if no adjustment is needed
          if(error == 0){
            derivative = 0;
          }

          //Convert target velocity to voltage
          targetVolt = percentToVoltage(maxVelocity);

            //Final output of drive alg that applies constants to the PID factors
            finalVolt = kP_t*proportion + kI_t*intergral + kD_t*derivative;
            //Sets final output so that its proportional to the target
            // finalPct = 100*(1 - (fabs(finalVolt) / targetVolt));
            // finalPct = finalPct / maxVelocity;
            // finalVolt = percentToVoltage(finalPct);
              //Declaring the final output as the target if it exceeds
              if(finalVolt > targetVolt){
                finalVolt = targetVolt;
              }
              else if(finalVolt < -targetVolt){
                finalVolt = -targetVolt;
              }

                if(direction == "r"){
                  moveRightDriveTrain(-finalVolt);
                  moveLeftDriveTrain(finalVolt);
                }
                else if(direction == "l"){
                  moveRightDriveTrain(finalVolt);
                  moveLeftDriveTrain(-finalVolt);
                }
                pros::delay(20);
}

  }
  driveBrake();
  driveStop();
  resetSensors();
  inertRoll = inertRoll + roll;
  pros::delay(20);
}

void stackSet(float TimeOut){
  float AngMin = 1500;
  float AngMax = 10;
  float AngVal = Ang_Pot.get_value();
  float MaxAcc = 145;
  float AnglerVelocity;
  float VelocityInterval;

  long  EndTime;
  EndTime = pros::millis() + TimeOut;
  while(pros::millis() < EndTime){
  AngVal = Ang_Pot.get_value();
  VelocityInterval = ((AngMin-AngMax))/MaxAcc;
  AnglerVelocity = (-(((AngVal-AngMax))/(VelocityInterval)));
  Angler.move_velocity(AnglerVelocity);
}
  Angler.move_velocity(0);
  drive("f",4,400,30);
}
// void setRake(int target,int timeOut,int velocity){
//   int rakeError = 0;
//   float rakeLast;
//   float rake_Kp = 0.0001;
//   float rakeAdjus;
//   float rakePos;
//   long endTime;
//   endTime = pros::millis() + timeOut;
//   while (pros::millis() < endTime){
//   rakePos = pros::c::adi_analog_read('D');
//   rakeError = target - rakePos;
//   if (pros::c::adi_analog_read('C') > 2780){
//     Catapult.move_velocity(100);
//   }
//   else {
//     Catapult.set_brake_mode(MOTOR_BRAKE_COAST);
//     Catapult.move_velocity(0);
//   }
//   if (target > (rakePos + 200)){
//     Rake.move_velocity(-velocity);
//   }
//   else if (target < (rakePos - 200)){
//     Rake.move_velocity(velocity);
//   }
//   else{
//     if(target > (rakePos + rakeError)){
//       rakeAdjus = rakeError * rake_Kp;
//       Rake.move_velocity(rakeAdjus);
//     }
//     else if(target < (rakePos - rakeError)){
//       rakeAdjus = rakeError * rake_Kp;
//       Rake.move_velocity(-rakeAdjus);
//     }
//     else{
//       Rake.set_brake_mode(MOTOR_BRAKE_COAST);
//       Rake.move_velocity(0);
//       }
//     }
//   }
//   pros::delay(20);
//   gyro.reset();
// }
