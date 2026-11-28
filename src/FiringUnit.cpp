#include "vex.h"
#include "RobotConfig.h"
#include "FiringUnit.h"
#include "AutoCode.h"
#include "ComboCode.h"
#include "PTOAction.h"

using namespace vex;

void Reload()
{
    printf("\ngetRR");
    // FiringUnit.setVelocity(127, pct);
    // FiringUnit.setMaxTorque(127, pct);
    setMaxTorquePTo(100, 100);
    setStopPTo(brake, brake);
    // FiringUnit.setStopping(brake);
    PTOReload(127, 127);
    // FiringUnit.spin(reverse);
    wait(0.2, sec);
    while (fabs(PTOLeft.velocity(pct)) > 0 && fabs(PTORight.velocity(pct)) > 0)
    {
        wait(5, msec);
    }
    // wait(100, msec);
    // FiringUnit.stop();
    StopPTO();
    PTOReload(127, 127);
    if (!AutoShootRuning)
    {
        wait(300, msec);
        StopPTO();
    }
}

void shootDm()
{
    Brain.resetTimer();
    // --------- shoot --------------
    // FiringUnit.spin(forward);
    PTOShoot(100, 100);
    wait(1.5, seconds);
    // --------- Start Exit ---------
    reload_Now = true;
}