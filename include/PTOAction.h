#pragma once

void setMaxTorquePTo(double powerleft, double powerright);
// void setVelocityPTo(double Leftspeed, double Rightspeed);
void setStopPTo(vex::brakeType mode, vex::brakeType modee);
void StopPTO();
void PTOArmUp(double powerleft, double powerright);
void PTOArmDown(double powerleft, double powerright);
void PTOShoot(double powerleft, double powerright);
void PTOReload(double powerleft, double powerright);