#include "vex.h"
#include "RobotConfig.h"
#include "Drive.h"

using namespace vex;

double PowerTurn = 0;
double MaxTurn = 1.0;
double Maxspeed = 1.0;
bool Drive = true;
bool I_want_to_drive = true;

void DriveTrainStop_SetStop(vex::brakeType mode)
{
    DT_Left.setStopping(mode);
    DT_Right.setStopping(mode);
    DT_Left.stop();
    DT_Right.stop();
}

void SetVel_DtLeft_DtRight(double LeftVel, double RightVel)
{ // SetDrivetrainVelocity Left Right
    DT_Left.setVelocity(LeftVel, percent);
    DT_Right.setVelocity(RightVel, percent);
}

// int drive()
// {
//     while (true)
//     {
//         if (abs(Controller.AxisA.position()) >= 50 ||
//             abs(Controller.AxisB.position()) >= 50)
//         {
//             I_want_to_drive = true;
//         }

//         if (Drive)
//         {
//             // if (abs(Controller.AxisB.position()) > 50)
//             //     MaxTurn = ((Controller.AxisB.position() * Controller.AxisB.position()) *
//             //             (Controller.AxisB.position() * 0.0001)) *
//             //            0.45;
//             // else
//             // {
//             PowerTurn = ((Controller.AxisB.position() * Controller.AxisB.position()) *
//                          (Controller.AxisB.position() * 0.0001)) *
//                         MaxTurn;
//             // }

//             double speedLeft = (((Controller.AxisA.position() * Controller.AxisA.position()) *
//                                  (Controller.AxisA.position() * 0.0001)) +
//                                 PowerTurn) *
//                                Maxspeed;
//             double speedRight = (((Controller.AxisA.position() * Controller.AxisA.position()) *
//                                   (Controller.AxisA.position() * 0.0001)) -
//                                  PowerTurn) *
//                                 Maxspeed;

//             if (abs(Controller.AxisA.position()) >= 5 ||
//                 abs(Controller.AxisB.position()) >= 5)
//             {
//                 DT_Left.spin(forward, speedLeft, pct);
//                 DT_Right.spin(forward, speedRight, pct);
//             }
//             else
//             {
//                 DT_Left.setStopping(coast);
//                 DT_Right.setStopping(coast);
//                 DT_Left.stop();
//                 DT_Right.stop();
//             }
//         }
//         task::sleep(10);
//     }
//     return 0;
// }


void LaneChange(int direction)
{
    // direction = 1  เลี้ยวขวา
    // direction = -1 เลี้ยวซ้าย

    double turnSpeed = 80;
    int turnTime = 240;

    DT_Left.spin(forward, direction * turnSpeed, pct);
    DT_Right.spin(forward, -direction * turnSpeed, pct);
    wait(turnTime, msec);

    DT_Left.spin(forward, -direction * turnSpeed, pct);
    DT_Right.spin(forward, direction * turnSpeed, pct);
    wait(turnTime, msec);

    DT_Left.stop(coast);
    DT_Right.stop(coast);
}

int drive()
{
    while (true)
    {
        if (abs(Controller.AxisA.position()) >= 50 ||
            abs(Controller.AxisB.position()) >= 50 ||
            abs(Controller.AxisC.position()) >= 50)
        {
            I_want_to_drive = true;
        }

        if (Drive)
        {
            // =========================
            // AxisC : สะบัดหัวหุ่นยนต์
            // =========================
            int flick = Controller.AxisC.position();

            if (abs(flick) >= 90)
            {
                double turnSpeed = flick * 1.0;

                LaneChange(turnSpeed);
            }
            else
            {
                // =========================
                // AxisA + AxisB : ขับปกติ
                // =========================
                PowerTurn = ((Controller.AxisB.position() *
                              Controller.AxisB.position()) *
                             (Controller.AxisB.position() * 0.0001)) *
                            MaxTurn;

                double speedLeft =
                    (((Controller.AxisA.position() *
                       Controller.AxisA.position()) *
                      (Controller.AxisA.position() * 0.0001)) +
                     PowerTurn) * Maxspeed;

                double speedRight =
                    (((Controller.AxisA.position() *
                       Controller.AxisA.position()) *
                      (Controller.AxisA.position() * 0.0001)) -
                     PowerTurn) * Maxspeed;

                if (abs(Controller.AxisA.position()) >= 5 ||
                    abs(Controller.AxisB.position()) >= 5)
                {
                    DT_Left.spin(forward, speedLeft, pct);
                    DT_Right.spin(forward, speedRight, pct);
                }
                else
                {
                    DT_Left.setStopping(coast);
                    DT_Right.setStopping(coast);
                    DT_Left.stop();
                    DT_Right.stop();
                }
            }
        }

        task::sleep(10);
    }

    return 0;
}
