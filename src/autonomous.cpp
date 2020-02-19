#include "main.h"
#include "functions.hpp"

Timer Auton;
void backRed(){
  unfold(); //Release the Tray
  rollUptake(200); //Start the Intake
  drive("b",5,300,100);
  drive("f",18,2000,40);
  drive("l",15,700,50);
  drive("f",4,1300,50);
  drive("l",39.4,1300,50);
  drive("f",11,2100,50);
  rollUptake(0);
  pros::delay(300);
  rollUptake(-70);
  pros::delay(500);
  rollUptake(-25);
  drive("f",12,600,50);
  stackSet(2500);
  drive("b",10,1000,50);
}

void backBlue(){
  unfold(); //Release the Tray
  rollUptake(200); //Start the Intake
  drive("f",18,1300,40);
  drive("l",90,1000,50);
  drive("f",30,1600,50);
  drive("r",70,1100,60);
  drive("f",28,1600,40);
  drive("r",110,1300,70);
  drive("f",50,1500,50);
}

void frontRed(){
  unfold();           //Release The Tray//
  rollUptake(200);       //Start The Intake//
  drive("f",49,2200,60);    //Drive Forward and Pickup Line//
  drive("r",30,950,60);         //Turn Left With Back Towards Second Line//
  drive("b",50,1600,70);     //Drive Towards Second Line//
  drive("l",30,900,50);   //Line Up With The Cubes//
  drive("f",29,1400,40);    //Pick up Second Line of Cubes//
  drive("r",11,1600,45);       //Turn Towaards Scoring Zone//
  rollUptake(-29);          //Start Moving Bottom Cube Towards Bottom of Tray//
  drive("f",39,1450,60); //Drive Towards Zone //
  stackSet(1800);     //Raise Angler And Set Stack//
  drive("b",10,2000,100);//Drive Away//
}

void frontBlue(){
  unfold();           //Release The Tray//
  rollUptake(200);       //Start The Intake//
  drive("f",49,2200,60);    //Drive Forward and Pickup Line//
  drive("l",30,950,60);         //Turn Left With Back Towards Second Line//
  drive("b",50,1600,70);     //Drive Towards Second Line//
  drive("r",30,900,50);   //Line Up With The Cubes//
  drive("f",31,1400,40);    //Pick up Second Line of Cubes//
  drive("l",115,1600,45);       //Turn Towaards Scoring Zone//
  rollUptake(-30);          //Start Moving Bottom Cube Towards Bottom of Tray//
  drive("f",39,1450,60); //Drive Towards Zone //
  stackSet(1800);     //Raise Angler And Set Stack//
  drive("b",10,2000,100);//Drive Away//
}

void skillsRed(){
  unfold();           //Release The Tray//
  rollUptake(200);       //Start The Intake//
  drive("f",50,2200,60);    //Drive Forward and Pickup Line//
  drive("r",30,950,60);         //Turn Left With Back Towards Second Line//
  drive("b",50,1600,70);     //Drive Towards Second Line//
  drive("l",30,900,50);   //Line Up With The Cubes//
  drive("f",35,1500,60);     //Pick up Second Line of Cubes//
  drive("r",125,1600,50);       //Turn Towaards Scoring Zone//
  rollUptake(-30);          //Start Moving Bottom Cube Towards Bottom of Tray//
  drive("f",45,1700,60); //Drive Towards Zone //
  stackSet(1400);     //Raise Angler And Set Stack//
  drive("b",15,2000,100);//Drive Away//
  rollUptake(0); //Intakes Set To Zero//
  drive("r",60,1100,60);//Turn Towards First Tower//
  rollUptake(100); //Roll Intake Half Speed//
  drive("f",35,2200,60); //Drive And Pickup Cube Under Cup//
  drive("b",5,700,60); //Get Room To Raise Arms//
  rollUptake(-100); //Roll Down To Queue Cube//
  pros::delay(400); //400 Millis//
  rollUptake(0); //Stop The Intakes//
  Arm.move_velocity(200); //Arm Up//
  pros::delay(1000); //1000 Millis//
  Arm.move_velocity(0); //Stop The Arm//
  drive("f",3,600,40); //Drive Towards Tower//
  rollUptake(-120); //Extrude Cube From Intake//
  pros::delay(300); //Wait 300 Millis//
  drive("b",5,500,60); //Drive Back From Tower//
  Arm.move_velocity(-200); //Arm Down//
  pros::delay(1200); //1200 Millis//
  Arm.move_velocity(0); //Stop The Arm//
  drive("b",40,2000,70); //Drive Backwards Aways From Tower//
  drive("r",90,1000,60); //Turn Right Towards Tower//
  rollUptake(100); //Roll Intake Half Speed//
  drive("f",35,2200,60); //Drive And Pickup Cube Under Cup//
  drive("b",5,700,60); //Get Room To Raise Arms//
  rollUptake(-100); //Roll Down To Queue Cube//
  pros::delay(400); //400 Millis//
  rollUptake(0); //Stop The Intakes//
  Arm.move_velocity(200); //Arm Up//
  pros::delay(1000); //1000 Millis//
  Arm.move_velocity(0); //Stop The Arm//
  drive("f",3,600,40); //Drive Towards Tower//
  rollUptake(-120); //Extrude Cube From Intake//
  pros::delay(300); //Wait 300 Millis//
  drive("b",5,500,60); //Drive Back From Tower//
}

void autonomous(){
  // drive("f",10,60000,0);
frontBlue();
// pros::lcd::print(1,"Roll: %f\n",inertRoll);

}
//All these chains of commands, rest in peace to Harriet Tubman
