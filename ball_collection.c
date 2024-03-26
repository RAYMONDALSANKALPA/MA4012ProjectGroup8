int ball_in_collection_range ;
//int enemy_in_range;
int count;
int prev_dist;
int conveyor_speed = 100;
//int ball_collected_limit = 0;

// function to check if ball in collection range for neater code as it will be called multiple times
void check_ball_in_range(){
		if (avg_bl < bottom_detection_value && avg_efd > top_detection_value){ //long sensor in range and short sensor not in range(if both in range means enemy robot)
			ball_in_collection_range = 1;
			writeDebugStreamLine("%s" ,"ball_in_collection_range");
			return;
		}
		//else if (avg_bs < 50 && avg_efd > top_detection_value){
		//	ball_in_collection_range = 1;
		//	writeDebugStreamLine("%s" ,"ball_in_collection_range");
		//	return;
		//}
		//else if ((SensorValue(sharp_sensor1))< 100 && (SensorValue(sharp_sensor2))<100){
		//	enemy_in_range = 1; // run enemy detection code?
		//}
		else{
			ball_in_collection_range =0;
			writeDebugStreamLine("%s" ,"ball_not_in_collection_range");
			return;
		}
}

// Starts conveyer
void conveyor_start()
{
	motor(conveyor_driver) = conveyor_speed;
	writeDebugStreamLine("%s", "Conveyor Started/n");
}

// Conveyor will only reverse if ball has been collected
void conveyor_reverse()
{
		motor(conveyor_driver) = -conveyor_speed;
		writeDebugStreamLine("%s", "Conveyor Reversed/n");
}

// Stops the conveyor after reversing
void conveyor_stop()
{
	motor(conveyor_driver) = 0;
	writeDebugStreamLine("%s", "Conveyor Stopped/n");
}

// Main fucntion that calls everything in this script
void go_to_ball(){
	while(1){
		count = 0;
		check_ball_in_range();
		while (ball_in_collection_range == 1){
			check_ball_in_range();
			motor(left_driver) = 60;
			motor(right_driver) = 60;
			conveyor_start();
			writeDebugStreamLine("%s", "Conveyor Started/n");


			// kinda optional code to optimise by ensuring that we are closing the distance between robot and ball(can increase count for btr comparison)
			// idk how it will work irl, need to test and troubleshoot to see if its viable
			if (count == 0){
				prev_dist = avg_bl;
			}
			if (count == 10){
				// compares distance between 10 counts apart and while the prev dist is bigger than recorded but still ball in range, a sweep will
				// optimise that it will guide itself back to the direction of the ball
				while (prev_dist > avg_bl){
					writeDebugStreamLine("%s", "ball getting further away, initiate short sweep");
					check_ball_in_range();
					motor(left_driver) = 0;
	        motor(right_driver) = 0;
	        sleep(500);
	        motor(left_driver) = -60;
	        motor(right_driver) = 60;
	        sleep(500);
	        motor(left_driver) = 60;
	        motor(right_driver) = -60;
					}
			}
			count ++;
		}

		// insert a delay to allow the collected ball to hit the limit switch if it is collected as after it goes up the ramp and past the sensor
		// there will be a moment b4 the ball hits the limit switch where the distance sensor will not sense anything in front while limit switch is
		// not triggered, causing this script to recognise it as a failed collection.
		delay(1000);

		//ball_collected_limit = SensorValue(ball_limit)
		//// if ball collected
		//if (ball_collected_limit != 1){
		//	writeDebugStreamLine("%s", "ball collected at limit switch!");
		//	conveyor_reverse();
		//	sleep(1000);
		//	conveyor_stop();
		//	return;
		//}
		//// if ball not collected
		//else if (ball_collected_limit == 1){
		//	writeDebugStreamLine("%s", "ball lost! Initate search for ball again...");
		//	return;
		//}
	}
}
