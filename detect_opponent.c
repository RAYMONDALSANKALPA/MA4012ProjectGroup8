int scan_opponent ()
{
	int frontOpponent = 0;
	int backOpponent = 0;

	//Detect front enemy disabled, to enable ball_limit == 1
	//if (avg_efd < 35 && SensorValue(ball_limit) == 1) {
	//	frontOpponent = 1;
	//}
	if (avg_ebd < 35 && SensorValue(ball_limit) == 0) {
		backOpponent = 2;
	}

	return frontOpponent+backOpponent;
}

void avoid_opponent (int opponent_range)
{
	if (opponent_range != 0) {
		writeDebugStreamLine("%d", opponent_range);

		int move[] = {0, -300, 300};
		int rotate_left[] = {-100, 100, -100, 100};
		int rotate_right[] = {100, -100, 100, -100};
		int direction = random(3);
		writeDebugStreamLine("%d", direction);

		clearTimer(T1);
		while (time1(T1) < 1200)
		{
			control_motor(move[opponent_range], move[opponent_range]);
		}
		clearTimer(T1);
		while (time1(T1) < 900)
		{
			control_motor(rotate_left[direction], rotate_right[direction]);
		}
		clearTimer(T1);
		while (time1(T1) < 1200)
		{
			control_motor(move[opponent_range], move[opponent_range]);
		}
		clearTimer(T1);
		while (time1(T1) < 900)
		{
			control_motor(rotate_right[direction], rotate_left[direction]);
		}
		stop_motor();
	}
}

task detect_opponent()
{
	while (true) {
		int opponent_range = scan_opponent();
		avoid_opponent(opponent_range);
	}
}
