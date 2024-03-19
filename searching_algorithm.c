#pragma config(Sensor, in7, sharp_front_top, sensorAnalog)
#pragma config(Sensor, in2, sharp_front_bottom_l, sensorAnalog)
#pragma config(Sensor, in3, sharp_front_bottom_r, sensorAnalog)
#pragma config(Motor, port3, left_driver, tmotorVex393_MC29, openLoop, reversed)
#pragma config(Motor, port8, right_driver, tmotorVex393_MC29, openLoop)

//#pragma config(Sensor, in4, sharp_short, sensorAnalog)
//#pragma config(Sensor, in6, front_l_line, sensorAnalog) // why analog?
//#pragma config(Sensor, dgtl5, front_r_line, sensorDigitalIn)
//#pragma config(Sensor, dgtl11, back_l_line, sensorDigitalIn)
//#pragma config(Sensor, dgtl12, back_r_line, sensorDigitalIn)




#include "sensor.h"

// parameters for starting
float move_time = 4500; // how long should the robot move forward when starting
float move_spd = 60; // max speed in competition

void first_move()
{
    // using sys timer
    // float starting_time = nSysTime;
    // float time_taken = 0;
    // float time_now = 0;

    // using timer T2
    clearTimer(T2);

    writeDebugStreamLine("%s", "starting procedure...");

    // loop
    while (1)
    {
        // move forward
        motor(left_driver) = move_spd;
        motor(right_driver) = -move_spd;
        scan_ball();
        if (ball_found == 1)
        {
            writeDebugStreamLine("%s", "ball found from starting procedure");
            motor(left_driver) = 0;
            motor(right_driver) = 0;
            writeDebugStreamLine("%s", "motor stopped");
            return;
        }

        // Scan for boundaries
        // scan_boundary();
        // if (line_sensor_status != NO_BOUNDARY_DETECTED)
        // {
        //     avoid_boundaries(line_sensor_status);
        //     total_boundary_time += 1500;
        // }
        // avoid_front_opponent();

        // time_now = nSysTime;
        // time_taken = time_now - starting_time;
        // writeDebugStreamLine("%d", time_taken);
        if (time1(T2) > move_time)
        {
            motor(left_driver) = 0;
            motor(right_driver) = 0;
            writeDebugStreamLine("%s", "motor stopped");
            ball_found = 0;
            return;
        }
    }
}

void move_forward()
{
    writeDebugStreamLine("%s", "moving forward");
    clearTimer(T3);
    // move forward
    motor(left_driver) = 100;
    motor(right_driver) = 100;
    while (time1(T3) < 4000)
    {
        // scan ball
        scan_ball();
        if (ball_found == 1)
        {
            motor(left_driver) = 0;
            motor(right_driver) = 0;
            writeDebugStreamLine("%s", "ball found in moving forward");
            return;
        }

        // scan boundaries
        // scan_boundary();
        // if (line_sensor_status != NO_BOUNDARY_DETECTED)
        // {
        //     avoid_boundaries(line_sensor_status);
        // }
        // avoid_front_opponent();
    }
    motor(left_driver) = 0;
    motor(right_driver) = 0;
    ball_found = 0;
    return;
}

void spinning_search()
{
		writeDebugStreamLine("%s", "spinning searching");
    float rot_time = 4500;
    float rot_spd = 60;

    // using sys timer
    // float start_time = nSysTime;
    // float time_taken = 0;

    // using timer T1
    clearTimer(T1);

    // // update compass status & set goal compass status
    // // +2 is used because of the shaking compass
    // // read_compass();
    // goal_compass_status = compass_status + 2;
    // if (goal_compass_status == 6)
    // {
    //     goal_compass_status = 1;
    // }
    // if (goal_compass_status == 7)
    // {
    //     goal_compass_status = 2;
    // }

    // Rotate CW
    motor(left_driver) = rot_spd;
    motor(right_driver) = -rot_spd;
    while (1)
    {
        // Scan for ball
        scan_ball();
        if (ball_found == 1)
        {
            writeDebugStreamLine("%s", "ball found... from spin search");
            return;
        }
        else
        {
            // Scan for boundaries
            //scan_boundary();
            //if (line_sensor_status != NO_BOUNDARY_DETECTED)
            //{
            //    avoid_boundaries(line_sensor_status);
            //}

            //avoid_opponent();

            // turning for 360
            // read_compass();
            // if (compass_status == goal_compass_status)
            // {
            //     stop_motor();
            //     ball_found = 0;
            //     return;
            // }

            // using sys timer
            // float time_now = nSysTime;
            // time_taken = time_now - start_time;
            if (time1(T1) > rot_time)
            {
                motor(left_driver) = 0;
                motor(right_driver) = 0;
                writeDebugStreamLine("%s", "motor stopped");
                ball_found = 0;
                return;
            }
        }
    }
}

task main()
{
    first_move();
    sleep(1000);
    while(1)
        {
            if (ball_found == 1)
            {
                writeDebugStreamLine("%s", "searching program ends");
                return;
                // ball collecion mechanism activate here
            }
            else if (ball_found == 0)
            {

                spinning_search();
                if (ball_found == 0)
                {
                    writeDebugStreamLine("%s", "ball not found, move forward and repeat search");
                    move_forward();
                }
            }
        }


}
