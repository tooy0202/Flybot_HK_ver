#include "vex.h"
#include "RobotConfig.h"
#include "FiringUnit.h"
#include "AutoCode.h"
#include "ComboCode.h"

using namespace vex;

void Reload()
{
    printf("\ngetRR");
    FiringUnit.setVelocity(127, pct);
    FiringUnit.setMaxTorque(127, pct);
    FiringUnit.setStopping(brake);
    FiringUnit.spin(reverse);
    wait(0.2, sec);
    while (fabs(FiringUnit.velocity(pct)) > 0)
    {
        wait(5, msec);
    }
    // wait(100, msec);
    FiringUnit.stop();
    FiringUnit.spin(reverse);
    if (!AutoShootRuning)
    {
        wait(300, msec);
        FiringUnit.stop();
    }
}

void shootDm()
{
    Brain.resetTimer();
    // --------- shoot --------------
    FiringUnit.spin(forward);
    wait(1.5, seconds);
    // --------- Start Exit ---------
    reload_Now = true;
}