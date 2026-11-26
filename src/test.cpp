// // void Shoot()
// // {
// //     // ==================================================
// //     // [1] INITIALIZE : เตรียมระบบก่อนเริ่มยิง
// //     // ==================================================
// //     LED.setColor(yellow);
// //     Brain.resetTimer();

// //     R_upRuning = true;
// //     speedlimitOn = true;

// //     int speedAuto = 127;
// //     int disOK = 0;

// //     double powerstop = 5;

// //     bool shootnow = false;
// //     bool shootSmooth = false;

// //     // ==================================================
// //     // [2] INTAKE DETECTION : ตรวจจับระยะและรับลูกบอล
// //     // ==================================================
// //     if (!intake_uplaw)
// //     {
// //         LED.setColor(blue);

// //         // รอจนกว่าจะเข้าใกล้ระยะ 180 mm
// //         while (distanceBack.objectDistance(mm) > 180)
// //         {
// //             double dis = distanceBack.objectDistance(mm);

// //             Brain.Screen.clearLine(3, 1);
// //             Brain.Screen.setCursor(3, 1);
// //             Brain.Screen.print("Dis: %.2f", dis);

// //             if (dis <= 180)
// //                 disOK++;
// //             else
// //                 disOK = 0;

// //             wait(10, msec);
// //         }

// //         // หยุดระบบขับเคลื่อนก่อนรับลูกบอล
// //         Drive = false;

// //         DriveTrainStop_SetStop(coast);
// //         wait(30, msec);
// //         DriveTrainStop_SetStop(brake);

// //         // สั่งกลไกจับลูกบอล
// //         hand.extend(cylinder2);

// //         // เปลี่ยนความเร็วสำหรับกรณี Intake
// //         speedAuto = -30;

// //         IntakeBeanBag();
// //     }

// //     Drive = false;

// //     wait(100, msec);
// //     if (distanceFront.objectDistance(mm) < 15)
// //     {
// //         DriveTrainStop_SetStop(coast);
// //         shootnow = true;
// //     }
// //     else if (distanceFront.objectDistance(mm) < 500)
// //     {
// //         powerstop = 1;

// //         const double startDis = 500.0;
// //         const double stopDis = 50.0;

// //         const double minSpeed = 5.0;
// //         const double maxSpeed = 100.0;

// //         DT_Left.setMaxTorque(100, pct);
// //         DT_Right.setMaxTorque(100, pct);

// //         // // กำหนดทิศทางถอยหลังก่อน
// //         SetVel_DtLeft_DtRight(100, 100);
// //         DT_Left.spin(forward);
// //         DT_Right.spin(reverse);
// //         wait(70, msec);
// //         DriveTrainStop_SetStop(coast);

// //         while (true)
// //         {
// //             double dis = distanceFront.objectDistance(mm);

// //             if (dis <= stopDis)
// //                 break;

// //             double t = (dis - stopDis) / (startDis - stopDis);

// //             if (t > 1.0)
// //                 t = 1.0;
// //             if (t < 0.0)
// //                 t = 0.0;

// //             // Smoothstep
// //             double smooth = t * t * (3.0 - 2.0 * t);

// //             // ความเร็วหลัก
// //             double currentSpeed =
// //                 minSpeed + (maxSpeed - minSpeed) * smooth;

// //             // ปรับความเร็วซ้ายและขวา
// //             double leftSpeed = currentSpeed * 0.9;
// //             double rightSpeed = currentSpeed;

// //             // จำกัดความเร็ว
// //             if (leftSpeed < 0)
// //                 leftSpeed = 0;
// //             if (rightSpeed > 127)
// //                 rightSpeed = 127;

// //             SetVel_DtLeft_DtRight(leftSpeed, rightSpeed);

// //             DT_Left.spin(reverse);
// //             DT_Right.spin(reverse);

// //             wait(10, msec);
// //         }
// //         shootSmooth = true;
// //         // DriveTrainStop_SetStop(coast);
// //         // wait(30, msec);
// //     }
// //     else
// //     {
// //         SetVel_DtLeft_DtRight(speedAuto, 127);
// //     }
// //     // -----Go shoot L3---------
// //     if (!shootnow && !shootSmooth)
// //     {
// //         DT_Left.spin(reverse);
// //         DT_Right.spin(reverse);
// //         wait(0.2, seconds);
// //     }
// //     if (speedAuto == -30 && !shootnow && !shootSmooth)
// //     {
// //         SetVel_DtLeft_DtRight(100.0, 100.0);
// //         DT_Left.spin(reverse);
// //         DT_Right.spin(reverse);
// //     }
// //     if (!shootnow && !shootSmooth)
// //     {
// //         while (distanceFront.objectDistance(mm) >= 450)
// //         {
// //             printf("I am in\n");
// //             wait(5, msec);
// //         }
// //     }
// //     DriveTrainStop_SetStop(coast);
// //     if (!shootnow)
// //     {
// //         wait(0.3, seconds);
// //     }
// //     DT_Left.setMaxTorque(30, pct);
// //     DT_Right.setMaxTorque(30, pct);
// //     SetVel_DtLeft_DtRight(40.0, 60.0);
// //     DT_Left.spin(reverse);
// //     DT_Right.spin(reverse);
// //     if (!shootnow)
// //     {
// //         wait(0.3, seconds);
// //     }
// //     // DT_Left.setMaxTorque(5, pct);
// //     // DT_Right.setMaxTorque(5, pct);
// //     // DT_Left.spin(reverse);
// //     // DT_Right.spin(reverse);
// //     while (fabs(DT_Right.velocity(percent)) > powerstop && fabs(DT_Left.velocity(percent)) > powerstop)
// //     {
// //         printf("I am in again\n");
// //         wait(20, msec);
// //     }
// //     // wait(1, seconds);
// //     SetVel_DtLeft_DtRight(5.0, 5.0);
// //     DT_Left.setMaxTorque(100, pct);
// //     DT_Right.setMaxTorque(100, pct);
// //     DT_Left.spin(reverse);
// //     DT_Right.spin(reverse);
// //     // DriveTrainStop_SetStop(brake);
// //     FiringUnit.spin(reverse);
// //     wait(0.08, seconds);
// //     // --------- shoot --------------
// //     FiringUnit.spin(forward);
// //     wait(0.2, seconds);
// //     // --------- Start Exit ---------
// //     SetVel_DtLeft_DtRight(100.0, 100.0);
// //     reload_Now = true;
// //     DT_Left.spin(forward);
// //     DT_Right.spin(forward);
// //     wait(0.2, seconds);
// //     if (countBB >= 2 && !GoToAutoShoot)
// //     {
// //         DT_Left.spin(reverse);
// //         DT_Right.spin(forward);
// //         wait(0.2, seconds);
// //     }
// //     if (GoToAutoShoot)
// //     {
// //         R_upRuning = false;
// //         Auto_shot();
// //         GoToAutoShoot = false;
// //     }
// //     countBB += 1;
// //     Drive = true;
// //     Intake_Already_done = false;
// //     R_upRuning = false;
// //     intake_uplaw = false;
// //     speedlimitOn = false;
// //     LED.setColor(green);
// // }

// void Auto_shot()
// {
//     Brain.resetTimer();
//     if (R_upRuning)
//     {
//         GoToAutoShoot = true;
//         LED.setColor(red);
//     }
//     else
//     {
//         Drive = false;
//         AutoShootRuning = true;
//         Intake_action_now = true;
//         intake_Now = true;
//         wait(0.1, sec);
//         I_want_to_drive = false;
//         LED.setColor(red);
//         while (true)
//         {
//             // int disOK = 0;
//             int count = 0;
//             DT_Left.setMaxTorque(100, pct);
//             DT_Right.setMaxTorque(100, pct);
//             if (firstAutoshoot)
//             {
//                 SetVel_DtLeft_DtRight(10.0, 100.0);
//                 DT_Left.spin(forward);
//                 DT_Right.spin(forward);
//                 wait(0.22, sec);
//             }
//             else
//             {
//                 SetVel_DtLeft_DtRight(100.0, 100.0);
//                 DT_Left.spin(reverse);
//                 DT_Right.spin(forward);
//                 wait(0.05, sec);
//                 SetVel_DtLeft_DtRight(10.0, 100.0);
//                 DT_Left.spin(forward);
//                 DT_Right.spin(forward);
//                 wait(0.15, sec);
//             }
//             firstAutoshoot = true;
//             SetVel_DtLeft_DtRight(65.0, 65.0);
//             DT_Left.spin(forward);
//             DT_Right.spin(forward);
//             LED.setColor(red);
//             // wait(0.4, sec);
//             while (true)
//             {
//                 // _ //
//                 // wait(20, msec);
//                 if (distanceBack.objectDistance(mm) <= 180)
//                 {
//                     count++;
//                     if (count == 3)
//                     {
//                         break;
//                     }
//                 }
//                 wait(10, msec);
//             }
//             // SetVel_DtLeft_DtRight(35.0, 35.0);
//             // DT_Left.spin(forward);
//             // DT_Right.spin(forward);
//             // wait(0.1, sec);
//             // while (distanceBack.objectDistance(mm) > 170)
//             // {
//             //     // _ //
//             //     // wait(10, msec);
//             // }
//             // Intake
//             DriveTrainStop_SetStop(coast);
//             wait(40, msec);
//             Intake.setVelocity(127, percent);
//             Intake.setMaxTorque(100, percent);
//             Intake.spin(forward);
//             // hand.extend(cylinder2);
//             IntakeBeanBag();
//             // DriveTrainStop_SetStop(brake);
//             //----
//             wait(450, msec);
//             // IntakeBeanBag();
//             //---
//             // DT_Left.setMaxTorque(100, pct);
//             // DT_Right.setMaxTorque(100, pct);
//             // SetVel_DtLeft_DtRight(0, 100.0);
//             // DT_Left.stop();
//             // DT_Right.spin(reverse);
//             // wait(200, msec);
//             // DT_Right.stop();
//             // go shoot
//             SetVel_DtLeft_DtRight(20.0, 30.0);
//             DT_Left.spin(reverse);
//             DT_Right.spin(reverse);
//             wait(200, msec);
//             SetVel_DtLeft_DtRight(60.0, 70.0);
//             DT_Left.spin(reverse);
//             DT_Right.spin(reverse);
//             // ---- wait shoot ----
//             int i = 0;
//             int disOK = 0;
//             double lastDis = 0;
//             while (i <= MaxWait)
//             {
//                 double dis = distanceBack.objectDistance(mm);
//                 int disInt = dis;
//                 int diff = dis - lastDis;

//                 Brain.Screen.clearLine(3, 1);
//                 Brain.Screen.setCursor(3, 1);
//                 Brain.Screen.print("Dis: %.2f", dis);

//                 if (dis >= disShoot &&
//                     diff < MAX_JUMP)
//                 {
//                     disOK++;
//                 }
//                 else
//                 {
//                     disOK = 0;
//                 }

//                 printf("\n%d | Dis = %d | Diff = %d | OK = %d",
//                        i,
//                        disInt,
//                        diff,
//                        disOK);

//                 lastDis = dis;
//                 i += 1;

//                 if (disOK == 1)
//                 {
//                     if (i > 28)
//                     {
//                         break;
//                     }
//                 }
//                 wait(20, msec);
//             }
//             printf("\n ============== End =================");
//             Brain.Screen.clearLine(3, 1);
//             Brain.Screen.setCursor(3, 1);
//             Brain.Screen.print("Dis: %.2f", distanceBack.objectDistance(mm));
//             int exit = distanceBack.objectDistance(mm);
//             printf("\n%d", exit);
//             // Touchled8.setColor(yellow);
//             // -------------------
//             // SetVel_DtLeft_DtRight(100, 100.0);
//             // // DT_Left.spin(forward);
//             // DT_Right.spin(reverse);
//             // DT_Left.stop();
//             // wait(100, msec);
//             // --------- shoot --------------
//             FiringUnit.setStopping(coast);
//             FiringUnit.stop();
//             FiringUnit.spin(forward);
//             wait(0.2, seconds);
//             // --------- Start Exit ---------
//             reload_Now = true;
//             // }
//             DriveTrainStop_SetStop(brake);
//             wait(0.3, sec);
//             // --------------------
//             // Pneumatic10.pumpOn();
//             // SetVel_DtLeft_DtRight(100.0, 100.0);
//             // DT_Left.spin(reverse);
//             // DT_Right.spin(forward);
//             // wait(0.3, sec);
//             //----------------------
//             // wait(0.3, sec);
//             if (I_want_to_drive)
//             {
//                 break;
//             }
//         }
//         LED.setColor(green);
//         AutoShootRuning = false;
//         Drive = true;
//     }
// }