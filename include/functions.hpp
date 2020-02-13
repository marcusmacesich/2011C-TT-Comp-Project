#include "main.h"

#ifndef FUNCTIONS_HPP
#define FUNCTIONS_HPP

void resetSensors(void);
void resetDriveTrain(void);
void driveTrainBreaking(void);
void driveTrainCoasting(void);
void driveTrainHolding(void);
void moveLeftDriveTrain(int velocity);
void moveRightDriveTrain(int velocity);
void moveDriveTrain(int velocity);
int degreesToTickLeft(float inch);
int degreesToTicksRight(float inch);
int inchToTicks(float inch);
float percentToVoltage(float percent);
void driveForwardsPID(float target,int timeOut,int maxVelocity);
void driveBackwardsPID(float target,int timeOut,int maxVelocity);
void rollUptake(int velocity);
void TurnRightPID(float Target,int TimeOut,int MaxVelocity);
void TurnLeftPID(float Target,int TimeOut,int MaxVelocity);
void unfold(void);
void drive(std::string direction, float target, int timeOut, int maxVelocity);
void stackSet(float TimeOut);
//


#endif
