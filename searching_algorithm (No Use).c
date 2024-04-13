// parameters for movement
// int normal_sweep_rot_speed = 70;

int normal_sweep_rot_speed = 32;
int mini_sweep_rot_speed = 25;
int forward_search_speed = 127;
int normal_sweep_rot_time = 3000;

// ball status
int prev_status = 0;

void wait_while_sweep(){
	// wait1Msec(100);
	// motor_stop()
	// wait1Msec(200);
	writeDebugStreamLine("%s %f %s %d", "distance ", avg_bl, "ball found: ", ball_found );

}

void normal_sweep()
{
			writeDebugStreamLine("%s", "normal sweep");
			float rot_spd = normal_sweep_rot_speed;

			// using timer T1
			clearTimer(T3);
			while (time1(T3) < normal_sweep_rot_time && ball_found == 0)
			{
				// Rotate left
				writeDebugStreamLine("%s", "turn right");
				turn_right(rot_spd);
				wait_while_sweep();
				scan_ball();
			}
			clearTimer(T3);
			while (time1(T3) < 2*normal_sweep_rot_time && ball_found == 0)
			{
				// Rotate right
				writeDebugStreamLine("%s", "turn left");
				turn_left(rot_spd);
				wait_while_sweep();
				scan_ball();
			}
			clearTimer(T3);
			while (time1(T3) < normal_sweep_rot_time && ball_found == 0)
			{
				// Rotate left
				writeDebugStreamLine("%s", "turn right 2");
				turn_right(rot_spd);
				wait_while_sweep();
				scan_ball();
			}
			return;
}

void mini_sweep()
{
			writeDebugStreamLine("%s", "mini sweep");
			float rot_spd = mini_sweep_rot_speed;

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
	float motor_spd = forward_search_speed;

	clearTimer(T3);
	while (time1(T3) < 2000 && ball_found == 0)
	{
		// move forward
		forward(motor_spd);
		scan_ball();
		if (ball_found == 1)
		{
			// motor_stop(); // removing this for now for smoother
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
