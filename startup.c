// parameters for starting
float move_time = 6000; // how long should the robot move forward when starting
float move_spd = 1000; // max speed in competition

void first_move()
{
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

		if (time1(T2) > move_time)
		{
			motor_stop();
			writeDebugStreamLine("%s", "motor stopped");
			ball_found = 0;
			return;
		}
	}
}
