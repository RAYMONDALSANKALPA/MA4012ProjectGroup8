void spinning_search()
{
		writeDebugStreamLine("%s", "spinning searching");
    float rot_time = 6000;
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
    motor(left_driver) = -rot_spd;
    motor(right_driver) = rot_spd;
    while (1)
    {
        // Scan for ball
        scan_ball();
        if (ball_found == 1)
        {
        		motor(left_driver) = 0;
            motor(right_driver) = 0;
            sleep(500);
            scan_ball();
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

void move_forward()
{
    writeDebugStreamLine("%s", "moving forward");
    float motor_spd = 60;
    clearTimer(T3);
    // move forward
    motor(left_driver) = motor_spd;
    motor(right_driver) = motor_spd;
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
