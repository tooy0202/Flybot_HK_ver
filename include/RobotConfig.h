#pragma once
#include "vex.h"

extern vex::brain Brain;

extern vex::inertial BrainInertial;
extern vex::controller Controller;

extern vex::motor_group DT_Left;
extern vex::motor_group DT_Right;
extern vex::motor FiringUnit;
extern vex::motor Intake;
extern vex::pneumatic hand;
extern vex::touchled LED;
extern vex::distance distanceFront;
extern vex::distance distanceBack;

void vexcodeInit();