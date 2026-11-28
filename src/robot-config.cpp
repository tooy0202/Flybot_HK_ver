#include "vex.h"
#include "RobotConfig.h"

using namespace vex;

vex::brain Brain;

inertial BrainInertial = inertial();
controller Controller = controller();

motor DT_Left1 = motor(PORT6, false);
motor DT_Left2 = motor(PORT1, false);
motor_group DT_Left = motor_group(
    DT_Left1,
    DT_Left2
);

motor DT_Right1 = motor(PORT12, true);
motor DT_Right2 = motor(PORT7, true);
motor_group DT_Right = motor_group(
    DT_Right1,
    DT_Right2
);

motor PTOLeft = motor(PORT3, false);

motor PTORight = motor(PORT10, true);

pneumatic hand = pneumatic(PORT2);
//cy 2 คือ Intake
//cy 1 คือ L4

touchled LED = touchled(PORT8);

distance distanceFront = distance(PORT4);

distance distanceBack = distance(PORT9);

void initializeRandomSeed()
{
    wait(100, msec);

    double xAxis = BrainInertial.acceleration(xaxis) * 1000;
    double yAxis = BrainInertial.acceleration(yaxis) * 1000;
    double zAxis = BrainInertial.acceleration(zaxis) * 1000;

    int seed = int(xAxis + yAxis + zAxis);

    srand(seed);
}

void vexcodeInit()
{
    initializeRandomSeed();
}

void PTO_group(vex::directionType dirleft, vex::directionType dirright){
    PTOLeft.spin(dirleft);
    PTORight.spin(dirright);
}