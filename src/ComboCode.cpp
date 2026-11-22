#include "vex.h"
#include "RobotConfig.h"
#include "Drive.h"
#include "FiringUnit.h"
#include "L4_Action.h"
#include "Intake.h"
#include "ComboCode.h"
#include "AutoCode.h"

using namespace vex;

int countBB = 0;
int MaxWait = 32;
double disShoot = 606;
double MAX_JUMP = 36;
bool AutoShootRuning = false;
bool speedlimitOn = false;
bool R_upRuning = false;
bool GoToAutoShoot = false;
bool intake_uplaw = false;
bool firstAutoshoot = false;

void IntakeBeanBag()
{
    Brain.resetTimer();
    intake_Now = true;
    speedlimitOn = false;
    intake_uplaw = true;
}

void Intake_L4()
{
    Brain.resetTimer();
    Drive = false;
    wait(0.1, sec);
    DriveTrainStop_SetStop(brake);
    SetVel_DtLeft_DtRight(50, 50);
    DT_Left.spinFor(forward, 70, degrees, false);
    DT_Right.spinFor(forward, 70, degrees, false);
    wait(0.35, sec);
    Drive = true;
    Grab_Action();
    wait(0.1, sec);
    Intake_up();
}

void Start_game()
{
    Brain.resetTimer();
    Drive = false;
    // แบบที่ 1 -----------------
    // DriveTrainStop_SetStop(brake);
    // SetVel_DtLeft_DtRight(100, 100);
    // DT_Left.spin(reverse);
    // DT_Right.spin(forward);
    // wait(0.25, sec);
    // DriveTrainStop_SetStop(brake);
    // wait(0.1, sec);
    // SetVel_DtLeft_DtRight(50, 50);
    // DT_Left.spin(forward);
    // DT_Right.spin(forward);
    // wait(0.2, sec);
    // แบบที่ 2-----------------
    DriveTrainStop_SetStop(brake);
    SetVel_DtLeft_DtRight(10, 60);
    DT_Left.spin(forward);
    DT_Right.spin(forward);
    wait(0.35, sec);
    SetVel_DtLeft_DtRight(50, 45);
    DT_Left.spin(forward);
    DT_Right.spin(forward);
    // แบบที่ 2-----------------
    while (DT_Left.velocity(pct) > 5 && DT_Right.velocity(pct) > 5)
    {
        /* code */
        wait(20, msec);
    }
    wait(100, msec);
    // start
    // DT_Left.stop();
    // DT_Right.stop();
    // L4_Combo();
    Intake_action_now = true;
    Intake.setStopping(hold);
    wait(0.1, sec);
    intake_Now = true;
    wait(0.2, sec);
    L4_up();
    wait(0.6, sec);
    SetVel_DtLeft_DtRight(100, 100);
    DT_Left.spinFor(reverse, 100, degrees, false);
    Intake_action_now = true;
    L4_down();
    intake_Now = true;
    DT_Right.spinFor(reverse, 100, degrees, true);
    SetVel_DtLeft_DtRight(100, 100);
    DT_Left.spinFor(forward, 50, degrees, false);
    DT_Right.spinFor(reverse, 50, degrees, true);
    hand.pumpOn();
    Drive = true;
}

void L4_Combo()
{
    Brain.resetTimer();
    Drive = false;
    Intake_action_now = true;
    DriveTrainStop_SetStop(hold);
    Intake.setStopping(hold);
    // wait(0.1, sec);
    SetVel_DtLeft_DtRight(100, 100);
    DT_Left.spinFor(forward, 500, degrees, false);
    DT_Right.spinFor(forward, 500, degrees, false);
    // wait(0.15, sec);
    intake_Now = true;
    // Intake_down();
    wait(0.2, sec);
    L4_up();
    wait(0.7, sec);
    SetVel_DtLeft_DtRight(100, 100);
    DT_Left.spinFor(reverse, 220, degrees, false);
    Intake_action_now = true;
    L4_down();
    intake_Now = true;
    DT_Right.spinFor(reverse, 220, degrees, true);
    DriveTrainStop_SetStop(coast);
    wait(0.1, sec);
    Drive = true;
}

void Shoot()
{
    LED.setColor(yellow);
    Brain.resetTimer();
    R_upRuning = true;
    // FiringUnit.spin(forward);
    // wait(0.2, sec);
    // reload_Now = true;

    int speedAuto = 127;
    // bool GoRpshoot;
    int disOK = 0;
    double powerstop = 5;
    bool shootnow = false;
    speedlimitOn = true;

    if (!intake_uplaw)
    {
        // GoRpshoot = true;
        LED.setColor(blue);
        while (distanceBack.objectDistance(mm) > 190) // no.7 190
        {
            // _ //
            double dis = distanceBack.objectDistance(mm);

            Brain.Screen.clearLine(3, 1);
            Brain.Screen.setCursor(3, 1);
            Brain.Screen.print("Dis: %.2f", dis);

            if (dis <= 180)
            {
                disOK++;
            }
            else
            {
                disOK = 0;
            }
            wait(10, msec);
        }
        // Intake
        Drive = false;
        wait(30, msec);
        DriveTrainStop_SetStop(brake);
        hand.extend(cylinder2);
        speedAuto = -30;
        IntakeBeanBag();
    }
    Drive = false;
    // int count = 0;
    wait(100, msec);
    if (distanceFront.objectDistance(mm) < 15)
    {
        DriveTrainStop_SetStop(coast);
        shootnow = true;
    }
    if (distanceFront.objectDistance(mm) < 500)
    {
        powerstop = 1;
        DT_Left.setMaxTorque(5, pct);
        DT_Right.setMaxTorque(5, pct);
        SetVel_DtLeft_DtRight(80.0, 100.0);
        wait(0.2, seconds);
    }
    else
    {
        SetVel_DtLeft_DtRight(speedAuto, 127);
    }
    // -----Go shoot L3---------
    if (!shootnow)
    {
        DT_Left.spin(reverse);
        DT_Right.spin(reverse);
        wait(0.2, seconds);
    }
    if (speedAuto == -30)
    {
        SetVel_DtLeft_DtRight(100.0, 100.0);
        DT_Left.spin(reverse);
        DT_Right.spin(reverse);
    }
    if (!shootnow)
    {
        while (distanceFront.objectDistance(mm) >= 450)
        {
            printf("I am in\n");
            wait(5, msec);
        }
    }
    DriveTrainStop_SetStop(coast);
    if (!shootnow)
    {
        wait(0.3, seconds);
    }
    DT_Left.setMaxTorque(30, pct);
    DT_Right.setMaxTorque(30, pct);
    SetVel_DtLeft_DtRight(40.0, 60.0);
    DT_Left.spin(reverse);
    DT_Right.spin(reverse);
    if (!shootnow)
    {
        wait(0.3, seconds);
    }
    // DT_Left.setMaxTorque(5, pct);
    // DT_Right.setMaxTorque(5, pct);
    // DT_Left.spin(reverse);
    // DT_Right.spin(reverse);
    while (fabs(DT_Right.velocity(percent)) > powerstop && fabs(DT_Left.velocity(percent)) > powerstop)
    {
        printf("I am in again\n");
        wait(20, msec);
    }
    // wait(1, seconds);
    SetVel_DtLeft_DtRight(5.0, 5.0);
    DT_Left.setMaxTorque(100, pct);
    DT_Right.setMaxTorque(100, pct);
    DT_Left.spin(reverse);
    DT_Right.spin(reverse);
    // DriveTrainStop_SetStop(brake);
    wait(0.08, seconds);
    // --------- shoot --------------
    FiringUnit.spin(forward);
    wait(0.2, seconds);
    // --------- Start Exit ---------
    SetVel_DtLeft_DtRight(100.0, 100.0);
    reload_Now = true;
    DT_Left.spin(forward);
    DT_Right.spin(forward);
    wait(0.2, seconds);
    if (countBB >= 2 && !GoToAutoShoot)
    {
        DT_Left.spin(reverse);
        DT_Right.spin(forward);
        wait(0.2, seconds);
    }
    if (GoToAutoShoot)
    {
        R_upRuning = false;
        Auto_shot();
        GoToAutoShoot = false;
    }
    countBB += 1;
    Drive = true;
    Intake_Already_done = false;
    R_upRuning = false;
    intake_uplaw = false;
    speedlimitOn = false;
    LED.setColor(green);
}

void Auto_shot()
{
    Brain.resetTimer();
    if (R_upRuning)
    {
        GoToAutoShoot = true;
        LED.setColor(red);
    }
    else
    {
        Drive = false;
        AutoShootRuning = true;
        Intake_action_now = true;
        intake_Now = true;
        wait(0.1, sec);
        I_want_to_drive = false;
        LED.setColor(red);
        while (true)
        {
            // int disOK = 0;
            int count = 0;
            DT_Left.setMaxTorque(100, pct);
            DT_Right.setMaxTorque(100, pct);
            if (firstAutoshoot)
            {
                SetVel_DtLeft_DtRight(10.0, 100.0);
                DT_Left.spin(forward);
                DT_Right.spin(forward);
                wait(0.22, sec);
            }
            else
            {
                SetVel_DtLeft_DtRight(10.0, 100.0);
                DT_Left.spin(forward);
                DT_Right.spin(forward);
                wait(0.15, sec);
            }

            firstAutoshoot = true;
            SetVel_DtLeft_DtRight(65.0, 65.0);
            DT_Left.spin(forward);
            DT_Right.spin(forward);
            LED.setColor(red);
            // wait(0.4, sec);
            while (true)
            {
                // _ //
                // wait(20, msec);
                if (distanceBack.objectDistance(mm) <= 180)
                {
                    count++;
                    if (count == 3)
                    {
                        break;
                    }
                }
                wait(10, msec);
            }
            // SetVel_DtLeft_DtRight(35.0, 35.0);
            // DT_Left.spin(forward);
            // DT_Right.spin(forward);
            // wait(0.1, sec);
            // while (distanceBack.objectDistance(mm) > 170)
            // {
            //     // _ //
            //     // wait(10, msec);
            // }
            // Intake
            DriveTrainStop_SetStop(coast);
            wait(50, msec);
            Intake.setVelocity(127, percent);
            Intake.setMaxTorque(100, percent);
            Intake.spin(forward);
            // hand.extend(cylinder2);
            IntakeBeanBag();
            // DriveTrainStop_SetStop(brake);
            //----
            wait(450, msec);
            // IntakeBeanBag();
            //---
            // DT_Left.setMaxTorque(100, pct);
            // DT_Right.setMaxTorque(100, pct);
            // SetVel_DtLeft_DtRight(0, 100.0);
            // DT_Left.stop();
            // DT_Right.spin(reverse);
            // wait(200, msec);
            // DT_Right.stop();
            // go shoot
            SetVel_DtLeft_DtRight(20.0, 30.0);
            DT_Left.spin(reverse);
            DT_Right.spin(reverse);
            wait(200, msec);
            SetVel_DtLeft_DtRight(60.0, 70.0);
            DT_Left.spin(reverse);
            DT_Right.spin(reverse);
            // ---- wait shoot ----
            int i = 0;
            int disOK = 0;
            double lastDis = 0;
            while (i <= MaxWait)
            {
                double dis = distanceBack.objectDistance(mm);
                int disInt = dis;
                int diff = dis - lastDis;

                Brain.Screen.clearLine(3, 1);
                Brain.Screen.setCursor(3, 1);
                Brain.Screen.print("Dis: %.2f", dis);

                if (dis >= disShoot &&
                    diff < MAX_JUMP)
                {
                    disOK++;
                }
                else
                {
                    disOK = 0;
                }

                printf("\n%d | Dis = %d | Diff = %d | OK = %d",
                       i,
                       disInt,
                       diff,
                       disOK);

                lastDis = dis;
                i += 1;

                if (disOK == 1)
                {
                    if (i > 28)
                    {
                        break;
                    }
                }
                wait(20, msec);
            }
            printf("\n ============== End =================");
            Brain.Screen.clearLine(3, 1);
            Brain.Screen.setCursor(3, 1);
            Brain.Screen.print("Dis: %.2f", distanceBack.objectDistance(mm));
            int exit = distanceBack.objectDistance(mm);
            printf("\n%d", exit);
            // Touchled8.setColor(yellow);
            // -------------------
            // SetVel_DtLeft_DtRight(100, 100.0);
            // // DT_Left.spin(forward);
            // DT_Right.spin(reverse);
            // DT_Left.stop();
            // wait(100, msec);
            // --------- shoot --------------
            FiringUnit.setStopping(coast);
            FiringUnit.stop();
            FiringUnit.spin(forward);
            wait(0.2, seconds);
            // --------- Start Exit ---------
            reload_Now = true;
            // }
            DriveTrainStop_SetStop(brake);
            wait(0.3, sec);
            // --------------------
            // Pneumatic10.pumpOn();
            // SetVel_DtLeft_DtRight(100.0, 100.0);
            // DT_Left.spin(reverse);
            // DT_Right.spin(forward);
            // wait(0.3, sec);
            //----------------------
            // wait(0.3, sec);
            if (I_want_to_drive)
            {
                break;
            }
        }
        LED.setColor(green);
        AutoShootRuning = false;
        Drive = true;
    }
}