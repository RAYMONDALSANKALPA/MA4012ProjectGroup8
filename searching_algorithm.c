// ball status
int prev_status = 0;

void normal_sweep()
{
			writeDebugStreamLine("%s", "normal sweep");
			float rot_spd = 35;

			// using timer T1
			clearTimer(T3);
			while (time1(T3) < 1500 && ball_found == 0)
			{
				// Rotate left
				turn_right(rot_spd);
				scan_ball();
			}
			clearTimer(T3);
			while (time1(T3) < 3000 && ball_found == 0)
			{
				// Rotate right
				turn_left(rot_spd);
				scan_ball();
			}
			clearTimer(T3);
			while (time1(T3) < 1500 && ball_found == 0)
			{
				// Rotate left
				turn_right(rot_spd);
				scan_ball();
			}
			return;
}

void mini_sweep()
{
			writeDebugStreamLine("%s", "mini sweep");
			float rot_spd = 25;

			// using timer T1
			clearTimer(T3);
			while (time1(T3) < 1000 && ball_found == 0)
			{
				// Rotate left
				turn_left(rot_spd);
				scan_ball();
			}
			clearTimer(T3);
			while (time1(T3) < 2000 && ball_found == 0)
			{
				// Rotate right
				turn_right(rot_spd);
				scan_ball();
			}
			clearTimer(T3);
			while (time1(T3) < 1000 && ball_found == 0)
			{
				// Rotate left
				turn_left(rot_spd);
				scan_ball();
			}
			return;
}

void move_forward()
{
	writeDebugStreamLine("%s", "ball not found, move forward and repeat search");
	float motor_spd = 1000;

	clearTimer(T3);
	while (time1(T3) < 2000 && ball_found == 0)
	{
		// move forward
		forward(motor_spd);
		scan_ball();
		if (ball_found == 1)
		{
			motor_stop();
			writeDebugStreamLine("%s", "ball found in moving forward");
			return;
		}
	}
}

void sweeping_search() {

	normal_sweep();
	prev_status = ball_found;
	wait1Msec(300);
	scan_ball();

	if (ball_found == 1) {
		return;
	}
	else {

		if (prev_status == 1) {
			mini_sweep();
			wait1Msec(200);
			scan_ball();

			if (ball_found == 1) {
				return;
			}
		}
		move_forward();
	}
}
