#include "vex.h"
#include "RobotConfig.h"
#include "Intake.h"
#include "ComboCode.h"
#include "L4_Action.h"

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

    Intake.setVelocity(127, percent);
    Intake.setMaxTorque(100, percent);
    Intake.spin(reverse);

    wait(0.2, sec);

    while (fabs(Intake.position(degrees)) < 150)
    {
        wait(20, msec);
    }

    waitTime = 0;
    double intakeWaitTime = 400;
    // on.8 = 400
    // no.8 = 380
    if (AutoShootRuning)
    {
        intakeWaitTime = 320;
    }
    while (fabs(Intake.velocity(pct)) > 5 &&
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
    Intake.setVelocity(127, percent);
    Intake.setMaxTorque(100, percent);
    Intake.spin(forward);

    waitTime = 0;

    wait(0.2, sec);

    while (fabs(Intake.position(degrees)) > 40)
    {
        wait(20, msec);
        waitTime += 20;
    }

    waitTime = 0;
    Intake_action_now = false;
    
    while (fabs(Intake.velocity(pct)) > 5 &&
           waitTime < 1200)
    {
        wait(20, msec);
        waitTime += 20;
    }
    if (AutoShootRuning || !L4_actionNow)
    {
        Intake.setVelocity(10, percent);
        Intake.spin(forward);
    }
    else
    {
        Intake.setMaxTorque(10, percent);
        wait(50, msec);
        Intake.stop();
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