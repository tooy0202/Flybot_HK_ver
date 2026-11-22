#pragma once

extern bool Drive, I_want_to_drive;
extern double Maxspeed;

void DriveTrainStop_SetStop(vex::brakeType mode);
void SetVel_DtLeft_DtRight(double LeftVel, double RightVel);
int drive();