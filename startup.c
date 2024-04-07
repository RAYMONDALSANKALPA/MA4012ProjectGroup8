// parameters for starting
float move_time = 4500; // how long should the robot move forward when starting
float move_spd = 50; // max speed in competition

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
    		scan_ball();
        // move forward
       	forward(move_spd);

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
            motor_stop();
            writeDebugStreamLine("%s", "motor stopped");
            ball_found = 0;
            return;
        }
    }
}
