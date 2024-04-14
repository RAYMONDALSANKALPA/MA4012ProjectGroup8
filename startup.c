// parameters for starting
float move_time = 5000; // how long should the robot move forward when starting
float move_spd = 1000; // max speed in competition

void first_move()
{
	clearTimer(T3);
	writeDebugStreamLine("%s", "starting procedure...");

	// loop
	while (time1(T3) < move_time)
	{
		scan_ball();
		// move forward
		forward(move_spd);
		if (ball_found == 1)	{
			wait1Msec(300)
			scan_ball()

			if (ball_found == 1)	{
				writeDebugStreamLine("%s", "ball found from starting procedure");
				return;
			}
		}
	}
}
