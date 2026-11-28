#include "vex.h"
#include "RobotConfig.h"
#include "Drive.h"
#include "FiringUnit.h"
#include "L4_Action.h"
#include "Intake.h"
#include "ComboCode.h"
#include "AutoCode.h"

using namespace vex;

bool reload_Now, intake_Now;

int StageActionOfPTO()
{
    while (true)
    {
        if (reload_Now)
        {
            Reload();
            reload_Now = !reload_Now;
        }
        else if (intake_Now)
        {
            if (Intake_action_now)
            {
                Intake_down();
            }
            else
            {
                Grab_Action();
                wait(0.1, sec);
                Intake_up();
                Intake_down();
            }
            intake_Now = !intake_Now;
        }
        wait(20, msec);
    }
    return 0;
}

// int getReload()
// {
//     while (true)
//     {
//         if (reload_Now)
//         {
//             Reload();
//             reload_Now = !reload_Now;
//         }
//         wait(20, msec);
//     }
//     return 0;
// }

// int getIntake()
// {
//     while (true)
//     {
//         if (intake_Now)
//         {
//             if (Intake_action_now)
//             {
//                 Intake_down();
//             }
//             else
//             {
//                 Grab_Action();
//                 wait(0.1, sec);
//                 Intake_up();
//                 Intake_down();
//             }
//             intake_Now = !intake_Now;
//         }
//         wait(20, msec);
//     }
//     return 0;
// }

int speedlimit()
{
    while (true)
    {
        if (speedlimitOn)
        {
            if (distanceBack.objectDistance(mm) <= 180)
            {
                if (L4_actionNow)
                {
                    Maxspeed = 0.2;
                }
            }
            else
            {
                Maxspeed = 1;
            }
        }
        else
        {
            Maxspeed = 1;
        }
        wait(20, msec);
    }
    return 0;
}