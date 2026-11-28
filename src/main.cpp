/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       main.cpp                                                  */
/*    Author:       someone                                                   */
/*    Created:      10/30/2026, 9:17:01 AM                                    */
/*    Description:  IQ2 project                                               */
/*                                                                            */
/*----------------------------------------------------------------------------*/
#include "vex.h"
#include "RobotConfig.h"
#include "Drive.h"
#include "FiringUnit.h"
#include "L4_Action.h"
#include "Intake.h"
#include "ComboCode.h"
#include "AutoCode.h"
#include "PTOAction.h"
using namespace vex;

int TimeLimit()
{
    while (true)
    {
        // if (start)
        // {
        if (Brain.Timer.value() >= 300.0)
        {
            // if(Brain.Timer.value() >= 30.0){
            //     hand.pumpOff();
            // }
            Brain.programStop();
        }
        if (Controller.AxisD.position() > 80)
        {
            Brain.Screen.clearLine(1, 1);
            Brain.Screen.setCursor(1, 1);
            Brain.Screen.print("PWS: %.2f mm", disShoot);
            disShoot += 4;
            MaxWait += 1;
            LED.setColor(black);
            wait(200, msec);
            if (AutoShootRuning)
            {
                LED.setColor(red);
            }
            else
            {
                LED.setColor(green);
            }
        }
        else if (Controller.AxisD.position() < -80)
        {
            Brain.Screen.clearLine(1, 1);
            Brain.Screen.setCursor(1, 1);
            Brain.Screen.print("PWS: %.2f mm", disShoot);
            disShoot -= 4;
            MaxWait -= 1;
            LED.setColor(black);
            wait(200, msec);
            if (AutoShootRuning)
            {
                LED.setColor(red);
            }
            else
            {
                LED.setColor(green);
            }
        }
        // }
        wait(20, msec);
    }
    return 0;
}

int main()
{

    // start config
    vexcodeInit();

    // ============ test PTO ====================
    // PTOArmUp(100, 100);
    // PTOArmDown(100, 100);
    // PTOShoot(100, 100);
    // PTOReload(100, 100);

    // ============= Start robot ================
    speedlimitOn = false;
    intake_Now = false;
    //
    DT_Left.setMaxTorque(100, pct);
    DT_Right.setMaxTorque(100, pct);
    //
    hand.retract(cylinder2);
    Grab = true;
    // hand.pumpOff();

    // ============= Start setup ==============
    PTOArmDown(127, 127);
    wait(1, sec);
    // PTOLeft.setPosition(0.0, deg);

    // reload
    reload_Now = true;
    wait(0.1, sec);

    // key Intake down
    Intake_action_now = true;
    wait(0.1, sec);

    // Intake
    intake_Now = true;
    wait(0.1, sec);

    // L4_down();
    L4_down();
    // Intake_action_now = false;

    // ============= finish ===================
    LED.setColor(green);

    // ============== action ==================
    // event Button
    Controller.ButtonLUp.pressed(L4_Combo);
    Controller.ButtonLDown.pressed(IntakeCheckUp_Down);
    Controller.ButtonFUp.pressed(L4_Check_Up_Down);
    Controller.ButtonFDown.pressed(IntakeBeanBag);
    Controller.ButtonRUp.pressed(Shoot);
    Controller.ButtonRDown.pressed(Auto_shot);
    Controller.ButtonEUp.pressed(shootDm);
    Controller.ButtonEDown.pressed(Intake_L4);
    Controller.ButtonR3.pressed(Start_game);
    Controller.ButtonL3.pressed(TurnRight);

    // task
    vex::task Stage_action_of_PTO(StageActionOfPTO);
    vex::task driveTask(drive);
    vex::task speedlimitTask(speedlimit);
    vex::task timeLimit(TimeLimit);
    //-------------------------------------
    // vex::task Intake_auto(getIntake);
    // vex::task Reload_auto(getReload);
}