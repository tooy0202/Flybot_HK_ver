#include "vex.h"
#include "RobotConfig.h"
#include "L4_Action.h"

using namespace vex;

bool L4_actionNow;

void L4_up()
{
    // L4.setVelocity(35, pct);
    // L4.setMaxTorque(100, pct);
    // L4.setStopping(coast);
    // L4.spin(forward);
    // wait(0.8, sec);
    // while (fabs(L4.velocity(pct)) > 0)
    // {
    //     wait(20, msec);
    // }
    // L4.stop();
    // Intake.setStopping(hold);
    hand.extend(cylinder1);
    L4_actionNow = true;
}

void L4_down()
{
    // L4.setVelocity(80, pct);
    // L4.setMaxTorque(100, pct);
    // L4.setStopping(brake);
    // L4.spin(reverse);
    // wait(1, sec);
    // while (fabs(L4.velocity(pct)) > 0)
    // {
    //     wait(20, msec);
    // }
    // L4.stop();
    // Intake.setStopping(hold);
    hand.retract(cylinder1);
    L4_actionNow = false;
}

void L4_Check_Up_Down()
{
    // It's L4 up now
    Brain.resetTimer();
    if (L4_actionNow)
    {
        L4_down();
    }
    else
    {
        L4_up();
    }
}