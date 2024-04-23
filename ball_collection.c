int ball_in_collection_range ;
int conveyor_speed = 1000;
int ball_collected_limit = SensorValue(ball_limit);

// function to check if ball in collection range for neater code as it will be called multiple times
void check_ball_in_range(){
	if (avg_bl < bottom_detection_value){ //long sensor in range and short sensor not in range(if both in range means enemy robot)
		ball_in_collection_range = 1;
		//writeDebugStreamLine("%s" ,"ball_in_collection_range");
		return;
	}
	else{
		ball_in_collection_range = 0;
		//writeDebugStreamLine("%s" ,"ball_not_in_collection_range");
		return;
	}
}

void ball_collected(){
	// if ball collected
	writeDebugStreamLine("%s", "ball collected at limit switch!");
	ball_found = 1;
	ball_collected_limit = 0;
	motor_stop();
	conveyor_reverse(conveyor_speed);
	sleep(500);
	conveyor_stop();
}

void ball_not_collected(){
	// if ball not collected
	writeDebugStreamLine("%s", "ball lost! Initate search for ball again...");
	ball_found = 0;
	motor_stop();
	conveyor_reverse(conveyor_speed);
	sleep(800);
	conveyor_stop();
}

// Main function that calls everything in this script
void go_to_ball(){

	check_ball_in_range();
	clearTimer(T3);
	while (ball_in_collection_range == 1 && SensorValue(ball_limit) == 1)	{
		check_ball_in_range();
		conveyor_start(conveyor_speed);
		forward(1000);
		if (time1(T3) > 6000)	{
			writeDebugStreamLine("%s", "ball collection timeout! turning away and return to search");
			ball_found = 0;
			motor_stop();
			sleep(400);
			backward_time(100, 2000);
			turn_right_time(80, 2000);
			conveyor_reverse(conveyor_speed);
			sleep(800);
			conveyor_stop();
			return;
		}
	}

	// insert a delay to allow the collected ball to hit the limit switch if it is collected as after it goes up the ramp and past the sensor
	// there will be a moment b4 the ball hits the limit switch where the distance sensor will not sense anything in front while limit switch is
	// not triggered, causing this script to recognise it as a failed collection.
	clearTimer(T3);
	while (time1(T3) < 4000){
		stop_motor();
		if (SensorValue(ball_limit) != 1){
			ball_collected();
			return;
		}
	}

	ball_not_collected();
	return;
}
