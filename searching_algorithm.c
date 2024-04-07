void sweeping_search()
{
	writeDebugStreamLine("%s", "sweeping searching");
	scan_ball();
	while(1)
	{
		if (ball_found == 1)
		{
			motor_stop();
			scan_ball();
			writeDebugStreamLine("%s", "ball found from sweep search");
			return;
		}
		else
		{
			float rot_spd = 55;

			// using timer T1
			clearTimer(T1);
			while (time1(T1) < 2000 && ball_found == 0)
			{
				// Rotate left
				turn_left(rot_spd);
				scan_ball();
			}
			clearTimer(T1);

			while (time1(T1) < 3000 && ball_found == 0)
			{
				// Rotate right
				turn_right(rot_spd);
				scan_ball();
			}
			clearTimer(T1);

			while (time1(T1) < 1150 && ball_found == 0)
			{
				// Rotate left
				turn_left(rot_spd);
				scan_ball();
			}

			if (ball_found == 0)
			{
				writeDebugStreamLine("%s", "failed to find ball from sweep search");
				return;
			}
		}
	}
}

//void spinning_search()
//{
//	writeDebugStreamLine("%s", "spinning searching");
//	float rot_time = 6000;
//	float rot_spd = 60;

//	// using timer T1
//	clearTimer(T1);

//	// Rotate CW
//	turn_left(rot_spd)
//	while (1)
//	{

//		if (ball_found == 1)
//		{
//			motor_stop();
//			//sleep(1000);
//			scan_ball();
//			writeDebugStreamLine("%s", "ball found from spin search");
//			return;
//		}
//		else
//		{
//			if (time1(T1) > rot_time)
//			{
//				motor(left_driver) = 0;
//				motor(right_driver) = 0;
//				writeDebugStreamLine("%s", "motor stopped");
//				ball_found = 0;
//				return;
//			}
//		}
//	}
//}

void move_forward()
{
	writeDebugStreamLine("%s", "moving forward");
	float motor_spd = 60;
	clearTimer(T3);
	// move forward
	forward(motor_spd);
	while (time1(T3) < 2000)
	{
		// scan ball
		scan_ball();
		if (ball_found == 1)
		{
			motor_stop();
			writeDebugStreamLine("%s", "ball found in moving forward");
			return;
		}
	}
	motor_stop();
	ball_found = 0;
	return;
}
