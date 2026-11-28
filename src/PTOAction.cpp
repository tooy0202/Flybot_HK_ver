#include "vex.h"
#include "RobotConfig.h"

using namespace vex;

// ==================================================
// [Function] Set Torque
// ==================================================
void setMaxTorquePTo(double powerleft, double powerright)
{
    PTOLeft.setMaxTorque(powerleft, pct);
    PTORight.setMaxTorque(powerright, pct);
}

// ==================================================
// [Function] Set speed
// ==================================================
void setVelocityPTo(double Leftspeed, double Rightspeed)
{
    PTOLeft.setVelocity(Leftspeed, pct);
    PTORight.setVelocity(Rightspeed, pct);
}

// ==================================================
// [Function] Set stop
// ==================================================
void setStopPTo(vex::brakeType mode, vex::brakeType modee)
{
    PTOLeft.setStopping(mode);
    PTORight.setStopping(modee);
}

// ==================================================
// [Function] Set stop
// ==================================================
void StopPTO(){
    PTOLeft.stop();
    PTORight.stop();
}
// ==================================================
// [Function] Arm Up
// ==================================================
void PTOArmUp(double powerleft, double powerright)
{
    setVelocityPTo(powerleft, powerright);
    PTO_group(forward, reverse);
}

// ==================================================
// [Function] Arm Down
// ==================================================
void PTOArmDown(double powerleft, double powerright)
{
    setVelocityPTo(powerleft, powerright);
    PTO_group(reverse, forward);
}

// ==================================================
// [Function] Shoot
// ==================================================
void PTOShoot(double powerleft, double powerright)
{
    setVelocityPTo(powerleft, powerright);
    PTO_group(reverse, reverse);
}

// ==================================================
// [Function] Reload
// ==================================================
void PTOReload(double powerleft, double powerright)
{
    setVelocityPTo(powerleft, powerright);
    PTO_group(forward, forward);
}