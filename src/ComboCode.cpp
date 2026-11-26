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
int countturn = 0;
int MaxWait = 32;
double disShoot = 606;
double MAX_JUMP = 36;
bool AutoShootRuning = false;
bool speedlimitOn = false;
bool R_upRuning = false;
bool GoToAutoShoot = false;
bool intake_uplaw = false;
bool firstAutoshoot = false;
bool TurnRightNow = false;

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
    // ==================================================
    // [1] INITIALIZE : เตรียมระบบก่อนเริ่มยิง
    // ==================================================
    LED.setColor(yellow);
    Brain.resetTimer();

    R_upRuning = true;
    speedlimitOn = true;

    int speedAuto = 127;
    int disOK = 0;

    double powerstop = 5;

    bool shootnow = false;
    bool shootSmooth = false;

    // ==================================================
    // [2] INTAKE DETECTION : ตรวจจับระยะและรับลูก
    // ==================================================
    if (!intake_uplaw)
    {
        LED.setColor(blue);

        // รอจนกว่าจะเข้าใกล้ระยะ 180 mm
        while (distanceBack.objectDistance(mm) > 180)
        {
            double dis = distanceBack.objectDistance(mm);

            Brain.Screen.clearLine(3, 1);
            Brain.Screen.setCursor(3, 1);
            Brain.Screen.print("Dis: %.2f", dis);

            if (dis <= 180)
                disOK++;
            else
                disOK = 0;

            wait(10, msec);
        }

        // หยุดระบบขับเคลื่อนก่อนรับลูกบอล
        Drive = false;

        DriveTrainStop_SetStop(coast);
        wait(30, msec);
        DriveTrainStop_SetStop(brake);

        // สั่งกลไกจับลูกบอล
        hand.extend(cylinder2);

        // เปลี่ยนความเร็วสำหรับกรณี Intake
        speedAuto = -30;

        IntakeBeanBag();
    }

    // ==================================================
    // [3] FRONT DISTANCE CHECK : ตรวจสอบระยะด้านหน้า
    // ==================================================
    Drive = false;

    wait(100, msec);

    double frontDis = distanceFront.objectDistance(mm);

    // กรณีอยู่ชิดแนวยิงอยู่แล้ว
    if (frontDis < 15)
    {
        DriveTrainStop_SetStop(coast);
        shootnow = true;
    }

    // ==================================================
    // [4] SMOOTH DECELERATION : ลดความเร็วตามระยะ
    // ==================================================
    else if (frontDis < 500)
    {
        powerstop = 1;

        const double startDis = 500.0;
        const double stopDis = 38.0;

        const double minSpeed = 10.0;
        const double maxSpeed = 100.0;

        // ตั้งค่าแรงบิดเริ่มต้น
        DT_Left.setMaxTorque(100, pct);
        DT_Right.setMaxTorque(100, pct);

        // ปรับแนวเริ่มต้นตามค่าที่ใช้อยู่เดิม
        SetVel_DtLeft_DtRight(100, 100);

        DT_Left.spin(forward);
        DT_Right.spin(reverse);

        wait(50, msec);

        DriveTrainStop_SetStop(coast);

        // ----------------------------------------------
        // Smoothstep Loop
        // ----------------------------------------------
        while (true)
        {
            double dis = distanceFront.objectDistance(mm);

            // ถึงระยะเป้าหมายแล้วออกจาก Loop
            if (dis <= stopDis)
                break;

            // Normalize ระยะ
            double t = (dis - stopDis) /
                       (startDis - stopDis);

            if (t > 1.0)
                t = 1.0;

            if (t < 0.0)
                t = 0.0;

            // Smoothstep
            double smooth = t * t * (3.0 - 2.0 * t);

            // คำนวณความเร็วหลัก
            double currentSpeed =
                minSpeed + (maxSpeed - minSpeed) * smooth;

            // ปรับความเร็วซ้ายและขวา
            double leftSpeed = currentSpeed * 0.9;
            double rightSpeed = currentSpeed;

            // จำกัดความเร็ว
            if (leftSpeed < 0)
                leftSpeed = 0;

            if (rightSpeed > 127)
                rightSpeed = 127;

            // สั่งความเร็ว
            SetVel_DtLeft_DtRight(leftSpeed, rightSpeed);

            // สั่งถอยหลัง
            DT_Left.spin(reverse);
            DT_Right.spin(reverse);

            wait(10, msec);
        }

        // แจ้งว่าผ่านระบบ Smooth แล้ว
        shootSmooth = true;
    }

    // ==================================================
    // [5] NORMAL APPROACH : เคลื่อนที่เข้าหากำแพงแบบปกติ
    // ==================================================
    else
    {
        SetVel_DtLeft_DtRight(speedAuto, 127);
    }

    // ----------------------------------------------
    // กรณีที่ไม่ได้ใช้ Smooth และไม่ได้ชิดแนวยิงแล้ว
    // ----------------------------------------------
    if (!shootnow && !shootSmooth)
    {
        DT_Left.spin(reverse);
        DT_Right.spin(reverse);

        wait(0.2, seconds);
    }

    // กรณี Intake ต้องกำหนดความเร็วใหม่
    if (speedAuto == -30 && !shootnow && !shootSmooth)
    {
        SetVel_DtLeft_DtRight(100.0, 100.0);

        DT_Left.spin(reverse);
        DT_Right.spin(reverse);
    }

    // รอจนเข้าเขตระยะ 450 mm
    if (!shootnow && !shootSmooth)
    {
        while (distanceFront.objectDistance(mm) >= 450)
        {
            printf("I am in\n");
            wait(5, msec);
        }
    }

    // ==================================================
    // [6] WALL ALIGNMENT : ปรับแนวเข้าชิดกำแพง
    // ==================================================

    // หยุดแบบ Coast ก่อนปรับแนว
    DriveTrainStop_SetStop(coast);

    if (!shootnow && !shootSmooth)
    {
        wait(0.3, seconds);
    }

    // ลด Torque เพื่อให้การปรับแนวไม่รุนแรง
    DT_Left.setMaxTorque(30, pct);
    DT_Right.setMaxTorque(30, pct);

    // ปรับความเร็วซ้ายและขวาไม่เท่ากัน
    SetVel_DtLeft_DtRight(40.0, 60.0);

    DT_Left.spin(reverse);
    DT_Right.spin(reverse);

    if (!shootnow)
    {
        wait(0.3, seconds);
    }

    // ==================================================
    // [7] STOP DETECTION : รอให้มอเตอร์ลดความเร็ว
    // ==================================================

    while (
        fabs(DT_Right.velocity(percent)) > powerstop &&
        fabs(DT_Left.velocity(percent)) > powerstop)
    {
        wait(20, msec);
    }

    // กำหนดความเร็วต่ำก่อนยิง
    SetVel_DtLeft_DtRight(5.0, 5.0);

    // คืน Torque สำหรับระบบยิง
    DT_Left.setMaxTorque(100, pct);
    DT_Right.setMaxTorque(100, pct);

    DT_Left.spin(reverse);
    DT_Right.spin(reverse);

    // ==================================================
    // [8] FIRE : ระบบยิง
    // ==================================================

    FiringUnit.spin(reverse);
    wait(0.08, seconds);

    // ยิง
    FiringUnit.spin(forward);
    wait(0.2, seconds);

    // ==================================================
    // [9] EXIT : เคลื่อนที่ออกจากจุดยิง
    // ==================================================

    SetVel_DtLeft_DtRight(100.0, 100.0);

    reload_Now = true;

    DT_Left.spin(forward);
    DT_Right.spin(forward);

    wait(0.2, seconds);

    // หมุนปรับทิศทางหลังยิงลูกที่ 2
    if (countBB >= 2 && !GoToAutoShoot)
    {
        DT_Left.spin(reverse);
        DT_Right.spin(forward);

        wait(0.2, seconds);
    }

    // ==================================================
    // [10] AUTO SHOOT : ยิงต่ออัตโนมัติ
    // ==================================================

    if (GoToAutoShoot)
    {
        R_upRuning = false;

        Auto_shot();

        GoToAutoShoot = false;
    }

    // ==================================================
    // [11] RESET : คืนค่าสถานะระบบ
    // ==================================================

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
    // ==================================================
    // [1] INITIALIZE : เตรียมระบบ Auto Shoot
    // ==================================================
    Brain.resetTimer();

    // ตรวจสอบว่า Shoot หลักกำลังทำงานอยู่หรือไม่
    if (R_upRuning)
    {
        // แจ้งว่าต้องการเรียก Auto Shoot
        // แต่ยังไม่เริ่มทำงานทันที
        GoToAutoShoot = true;

        LED.setColor(red);
    }

    // ==================================================
    // [2] START AUTO SHOOT : เริ่มระบบยิงอัตโนมัติ
    // ==================================================
    else
    {
        // ปิดการควบคุม Drive จากระบบหลัก
        Drive = false;

        // แจ้งสถานะว่า Auto Shoot กำลังทำงาน
        AutoShootRuning = true;

        // เปิดสถานะการทำงานของ Intake
        Intake_action_now = true;
        intake_Now = true;

        wait(0.1, sec);

        // ปิดความต้องการให้ระบบอื่นควบคุมการเคลื่อนที่
        I_want_to_drive = false;

        LED.setColor(red);

        // ==================================================
        // [3] AUTO SHOOT LOOP : วนทำงาน Auto Shoot
        // ==================================================
        while (true)
        {
            // ตัวนับจำนวนครั้งที่ตรวจพบระยะ Intake
            int count = 0;

            // กำหนด Torque ของมอเตอร์ขับเคลื่อน
            DT_Left.setMaxTorque(100, pct);
            DT_Right.setMaxTorque(100, pct);

            // ==================================================
            // [4] MOVEMENT & POSITIONING : จัดตำแหน่งหุ่นยนต์
            // ==================================================

            // ----------------------------------------------
            // กรณีการเคลื่อนที่ครั้งแรก
            // ----------------------------------------------
            if (firstAutoshoot)
            {
                SetVel_DtLeft_DtRight(10.0, 100.0);

                DT_Left.spin(forward);
                DT_Right.spin(forward);

                wait(0.22, sec);
            }

            // ----------------------------------------------
            // กรณีการเคลื่อนที่ครั้งถัดไป
            // ----------------------------------------------
            else
            {
                // หมุนปรับทิศทาง
                SetVel_DtLeft_DtRight(100.0, 100.0);

                DT_Left.spin(reverse);
                DT_Right.spin(forward);

                wait(0.05, sec);

                // เคลื่อนที่ไปข้างหน้า
                SetVel_DtLeft_DtRight(10.0, 100.0);

                DT_Left.spin(forward);
                DT_Right.spin(forward);

                wait(0.15, sec);
            }

            // เปลี่ยนสถานะหลังจากเคลื่อนที่ครั้งแรก
            firstAutoshoot = true;

            // ==================================================
            // [5] INTAKE DETECTION : ตรวจจับระยะรับลูกบอล
            // ==================================================

            // กำหนดความเร็วสำหรับการเคลื่อนที่เข้าหาจุดรับลูก
            SetVel_DtLeft_DtRight(65.0, 65.0);

            DT_Left.spin(forward);
            DT_Right.spin(forward);

            LED.setColor(red);

            // รอจนกว่า Distance Back จะตรวจพบระยะ 180 mm
            while (true)
            {
                if (distanceBack.objectDistance(mm) <= 180)
                {
                    count++;

                    // ต้องตรวจพบครบ 3 ครั้งจึงออกจาก Loop
                    if (count == 3)
                    {
                        break;
                    }
                }

                wait(10, msec);
            }

            // ==================================================
            // [6] INTAKE ACTION : หยุดและรับลูกบอล
            // ==================================================

            // หยุดระบบขับเคลื่อนแบบ Coast
            DriveTrainStop_SetStop(coast);

            wait(40, msec);

            // ตั้งค่ามอเตอร์ Intake
            Intake.setVelocity(127, percent);
            Intake.setMaxTorque(100, percent);

            // เริ่มรับลูกบอล
            Intake.spin(forward);

            IntakeBeanBag();

            // รอให้ระบบ Intake ทำงาน
            wait(450, msec);

            // ==================================================
            // [7] GO TO SHOOT POSITION : เข้าตำแหน่งยิง
            // ==================================================

            // เคลื่อนที่ด้วยความเร็วต่ำ
            SetVel_DtLeft_DtRight(20.0, 30.0);

            DT_Left.spin(reverse);
            DT_Right.spin(reverse);

            wait(200, msec);

            // เพิ่มความเร็วเพื่อเคลื่อนที่ต่อ
            SetVel_DtLeft_DtRight(60.0, 70.0);

            DT_Left.spin(reverse);
            DT_Right.spin(reverse);

            // ==================================================
            // [8] SHOOT DISTANCE DETECTION : ตรวจจับระยะยิง
            // ==================================================

            int i = 0;
            int disOK = 0;

            double lastDis = 0;

            // รอจนกว่าจะพบระยะที่ต้องการ หรือครบ MaxWait
            while (i <= MaxWait)
            {
                double dis = distanceBack.objectDistance(mm);

                int disInt = dis;
                int diff = dis - lastDis;

                // แสดงระยะบน Brain Screen
                Brain.Screen.clearLine(3, 1);
                Brain.Screen.setCursor(3, 1);

                Brain.Screen.print("Dis: %.2f", dis);

                // ------------------------------------------
                // ตรวจสอบระยะและการเปลี่ยนแปลงของระยะ
                // ------------------------------------------
                if (dis >= disShoot &&
                    diff < MAX_JUMP)
                {
                    disOK++;
                }
                else
                {
                    disOK = 0;
                }

                // แสดงข้อมูล Debug
                printf(
                    "\n%d | Dis = %d | Diff = %d | OK = %d",
                    i,
                    disInt,
                    diff,
                    disOK);

                // เก็บค่าระยะล่าสุด
                lastDis = dis;

                i += 1;

                // ------------------------------------------
                // เงื่อนไขออกจากการตรวจจับระยะ
                // ------------------------------------------
                if (disOK == 1)
                {
                    if (i > 28)
                    {
                        break;
                    }
                }

                wait(20, msec);
            }

            // ==================================================
            // [9] SHOOT DISTANCE DEBUG : แสดงผลระยะสุดท้าย
            // ==================================================

            printf("\n ============== End =================");

            Brain.Screen.clearLine(3, 1);
            Brain.Screen.setCursor(3, 1);

            Brain.Screen.print(
                "Dis: %.2f",
                distanceBack.objectDistance(mm));

            int exit = distanceBack.objectDistance(mm);

            printf("\n%d", exit);

            // ==================================================
            // [10] FIRE : สั่งยิง
            // ==================================================

            FiringUnit.setStopping(coast);
            FiringUnit.stop();

            FiringUnit.spin(forward);

            wait(0.2, seconds);

            // ==================================================
            // [11] RELOAD : แจ้งสถานะการ Reload
            // ==================================================

            reload_Now = true;

            // ==================================================
            // [12] STOP : หยุดระบบขับเคลื่อนหลังยิง
            // ==================================================

            DriveTrainStop_SetStop(brake);

            wait(0.3, sec);

            // ==================================================
            // [13] EXIT CONDITION : ตรวจสอบเงื่อนไขออกจาก Loop
            // ==================================================

            // ถ้าระบบภายนอกต้องการให้หุ่นยนต์กลับไปขับเคลื่อน
            // ให้ออกจาก Auto Shoot Loop
            if (I_want_to_drive)
            {
                break;
            }
        }

        // ==================================================
        // [14] RESET : คืนสถานะหลังจบ Auto Shoot
        // ==================================================

        LED.setColor(green);

        AutoShootRuning = false;

        if (TurnRightNow)
        {
            TurnRight();
        }

        Drive = true;
    }
}

void TurnRight()
{
    if (!I_want_to_drive)
    {
        I_want_to_drive = true;
        TurnRightNow = true;
    }
    else
    {
        Drive = false;
        if (countturn == 0)
        {
            SetVel_DtLeft_DtRight(100.0, 100.0);
            DT_Left.spin(forward);
            DT_Right.spin(forward);
            wait(0.4, sec);
            SetVel_DtLeft_DtRight(100.0, 5.0);
            DT_Left.spin(forward);
            DT_Right.spin(forward);
            wait(0.3, sec);
            SetVel_DtLeft_DtRight(100.0, 100.0);
            DT_Left.spin(forward);
            DT_Right.spin(forward);
            wait(0.4, sec);
        }
        else
        {
            wait(0.15, sec);
            SetVel_DtLeft_DtRight(100.0, 100.0);
            DT_Left.spin(forward);
            DT_Right.spin(reverse);
            wait(0.3, sec);
            DriveTrainStop_SetStop(brake);
            wait(0.1, sec);
            SetVel_DtLeft_DtRight(100.0, 100.0);
            DT_Left.spin(forward);
            DT_Right.spin(forward);
            wait(0.38, sec);
            SetVel_DtLeft_DtRight(100.0, 5.0);
            DT_Left.spin(forward);
            DT_Right.spin(forward);
            wait(0.33, sec);
            DriveTrainStop_SetStop(brake);
            // wait(0.1, sec);
            SetVel_DtLeft_DtRight(100.0, 100.0);
            DT_Left.spin(forward);
            DT_Right.spin(forward);
            wait(0.27, sec);
        }
        DriveTrainStop_SetStop(brake);
        wait(0.1, sec);
        countturn++;
        Drive = true;
    }
}