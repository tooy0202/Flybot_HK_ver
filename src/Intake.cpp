#include "vex.h"
#include "RobotConfig.h"
#include "Intake.h"
#include "ComboCode.h"
#include "L4_Action.h"
#include "PTOAction.h"

using namespace vex;

bool Grab, Intake_action_now, Intake_Already_done;

int waitTime = 0;

void Grab_Action()
{
    if (Grab)
    {
        hand.extend(cylinder2);
    }
    else
    {
        hand.retract(cylinder2);
    }
    Grab = !Grab;
}

void Intake_up()
{

    // Intake.setVelocity(127, percent);
    // Intake.setMaxTorque(100, percent);
    setMaxTorquePTo(100, 100);
    PTOArmUp(127, 127);
    // Intake.spin(reverse);

    wait(0.9, sec);

    // while (fabs(PTOLeft.position(degrees)) < 50)
    // {
    //     wait(20, msec);
    // }

    waitTime = 0;
    double intakeWaitTime = 600;
    // on.8 = 400
    // no.8 = 380
    if (AutoShootRuning)
    {
        intakeWaitTime = 320;
    }
    while ((fabs(PTOLeft.velocity(pct)) > 0 && fabs(PTORight.velocity(pct)) > 0) &&
           waitTime < intakeWaitTime)
    {
        wait(20, msec);
        waitTime += 20;
    }
    // wait(100, msec);
    Intake_action_now = true;
    Intake_Already_done = true;
    Grab_Action();
    // Intake.stop();
}

void Intake_down()
{
    wait(0.1, sec);
    setMaxTorquePTo(100, 100);
    PTOArmDown(127, 127);

    waitTime = 0;

    wait(0.2, sec);

    // while (fabs(PTOLeft.position(degrees)) > 40)
    // {
    //     wait(20, msec);
    //     waitTime += 20;
    // }

    waitTime = 0;
    Intake_action_now = false;
    
    while ((fabs(PTOLeft.velocity(pct)) > 0 && fabs(PTORight.velocity(pct)) > 0) &&
           waitTime < 1200)
    {
        wait(20, msec);
        waitTime += 20;
    }
    if (AutoShootRuning || !L4_actionNow)
    {
        setMaxTorquePTo(5, 5);
        PTOArmDown(3, 3);
    }
    else
    {
        setStopPTo(brake, brake);
        StopPTO();
    }
    
}

void IntakeCheckUp_Down()
{
    Brain.resetTimer();
    // It's Intake up now
    if (Intake_action_now)
    {
        Intake_down();
    }
    else
    {
        Intake_up();
        Grab_Action();
    }
}