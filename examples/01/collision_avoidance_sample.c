#include <stdio.h>
#define BASE_SPEED_S 30
#define BASE_SPEED_M 70
#define SENSOR_P 1
#define MIN_DIST 30
#define SLOW_DIST 50

int ANGLE[2] = {-10, 40};
int obsDistance[4] = {255, 255, 255, 255};
int zone[4] = {2, 2, 2, 2};
int motor_speed[2] = {0, 0};

void determineSpeed()
{

    for (int j = 0; j < 4; j++)
    {
        if (obsDistance[j] < MIN_DIST)
        {
            zone[j] = 0;
        }
        else if (obsDistance[j] < SLOW_DIST)
        {
            zone[j] = 1;
        }
        else
            zone[j] = 2;
    }

    if (!zone[0] && !zone[1])
    {

        if (!zone[2] && !zone[3])
        {
            motor_speed[0] = BASE_SPEED_S;
            motor_speed[1] = -BASE_SPEED_S;
        }

        else
        {
            motor_speed[0] = (obsDistance[2] < obsDistance[3]) ? BASE_SPEED_S : -10;
            motor_speed[1] = (obsDistance[2] > obsDistance[3]) ? BASE_SPEED_S : -10;
        }
    }

    else if (!zone[0] && zone[1])
    {
        motor_speed[0] = BASE_SPEED_S;
        motor_speed[1] = -10;
    }

    else if (!zone[1] && zone[0])
    {
        motor_speed[1] = BASE_SPEED_S;
        motor_speed[0] = -10;
    }

    else if (zone[0] == 2 && zone[1] == 2)
    {
        int s = (motor_speed[0] > motor_speed[1]) ? motor_speed[0] : motor_speed[1];
        motor_speed[0] = s;
        motor_speed[1] = s;

        if ((!zone[2] || !zone[3]) && (zone[2] != zone[3]))
        {

            motor_speed[0] = (!zone[2]) ? BASE_SPEED_S : obsDistance[2] - 20;
            motor_speed[1] = (!zone[3]) ? BASE_SPEED_S : obsDistance[3] - 20;
        }

        else
        {
            if (motor_speed[0] < BASE_SPEED_M)
            {
                motor_speed[0] += 0.5 * (BASE_SPEED_M - motor_speed[0]);
                motor_speed[1] += 0.5 * (BASE_SPEED_M - motor_speed[1]);
            }
            else
            {
                motor_speed[0] = BASE_SPEED_M;
                motor_speed[1] = BASE_SPEED_M;
            }
        }
    }
    else
    {

        if (zone[0] == zone[1])
        {
            motor_speed[0] += 0.5 * (BASE_SPEED_S - motor_speed[0]);
            motor_speed[1] += 0.5 * (BASE_SPEED_S - motor_speed[1]);
        }

        else if (zone[1] == 1)
        {
            motor_speed[1] += 3 * (BASE_SPEED_S - motor_speed[1]) / 10;
            motor_speed[0] += 0.5 * (BASE_SPEED_S - motor_speed[0]);
        }

        else
        {
            motor_speed[1] += 0.5 * (BASE_SPEED_S - motor_speed[1]);
            motor_speed[0] += 3 * (BASE_SPEED_S - motor_speed[0]) / 10;
        }
    }
}

int main()
{
    ANGLE[0] = -3;
    ANGLE[1] = 0;
    motor_speed[0] = 85;
    motor_speed[1] = 25;
    obsDistance[0] = 10;
    obsDistance[1] = 24;
    obsDistance[2] = 23;
    obsDistance[3] = 8;
    determineSpeed();

    ANGLE[0] = -3;
    ANGLE[1] = -1;
    motor_speed[0] = 35;
    motor_speed[1] = 25;
    obsDistance[0] = 27;
    obsDistance[1] = 8;
    obsDistance[2] = 90;
    obsDistance[3] = 43;
    determineSpeed();

    ANGLE[0] = 100;
    ANGLE[1] = -2;
    motor_speed[0] = 20;
    motor_speed[1] = 14;
    obsDistance[0] = 4;
    obsDistance[1] = 5;
    obsDistance[2] = 20;
    obsDistance[3] = 30;
    determineSpeed();

    ANGLE[0] = -3;
    ANGLE[1] = 0;
    motor_speed[0] = 35;
    motor_speed[1] = 87;
    obsDistance[0] = 7;
    obsDistance[1] = 48;
    obsDistance[2] = 22;
    obsDistance[3] = 5;
    determineSpeed();

    ANGLE[0] = 27;
    ANGLE[1] = -1;
    motor_speed[0] = 35;
    motor_speed[1] = 87;
    obsDistance[0] = 46;
    obsDistance[1] = 0;
    obsDistance[2] = 9;
    obsDistance[3] = 8;
    determineSpeed();

    ANGLE[0] = -3;
    ANGLE[1] = -1;
    motor_speed[0] = 35;
    motor_speed[1] = 25;
    obsDistance[0] = 63;
    obsDistance[1] = 53;
    obsDistance[2] = 17;
    obsDistance[3] = 38;
    determineSpeed();

    ANGLE[0] = -3;
    ANGLE[1] = -2;
    motor_speed[0] = 20;
    motor_speed[1] = 74;
    obsDistance[0] = 81;
    obsDistance[1] = 87;
    obsDistance[2] = 31;
    obsDistance[3] = 5;
    determineSpeed();

    ANGLE[0] = -3;
    ANGLE[1] = 0;
    motor_speed[0] = 10;
    motor_speed[1] = 20;
    obsDistance[0] = 100;
    obsDistance[1] = 84;
    obsDistance[2] = 16;
    obsDistance[3] = 10;
    determineSpeed();

    ANGLE[0] = -3;
    ANGLE[1] = -1;
    motor_speed[0] = 85;
    motor_speed[1] = 25;
    obsDistance[0] = 98;
    obsDistance[1] = 82;
    obsDistance[2] = 18;
    obsDistance[3] = 22;
    determineSpeed();

    ANGLE[0] = 27;
    ANGLE[1] = 0;
    motor_speed[0] = 85;
    motor_speed[1] = 25;
    obsDistance[0] = 40;
    obsDistance[1] = 48;
    obsDistance[2] = 24;
    obsDistance[3] = 18;
    determineSpeed();

    ANGLE[0] = -3;
    ANGLE[1] = -1;
    motor_speed[0] = 85;
    motor_speed[1] = 25;
    obsDistance[0] = 66;
    obsDistance[1] = 42;
    obsDistance[2] = 14;
    obsDistance[3] = 22;
    determineSpeed();

    ANGLE[0] = 27;
    ANGLE[1] = -1;
    motor_speed[0] = 35;
    motor_speed[1] = 87;
    obsDistance[0] = 34;
    obsDistance[1] = 64;
    obsDistance[2] = 20;
    obsDistance[3] = 8;
    determineSpeed();
}
